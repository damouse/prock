// Fill out your copyright notice in the Description page of Project Settings.

#include "ProckFPS.h"

#include "Actors/BoxActor.h"
#include "Actors/LineActor.h"

#include "Utils/Config.h"

#include <stdio.h>
#include <math.h> 


void ABoxActor::BeginPlay() {
	Super::BeginPlay();
	PrimaryActorTick.bCanEverTick = true;

	p = FVector(0, 0, 0);
	v = FVector(0, 0, 0);
	f = FVector(0, 0, 0);
	m = 0.1;
}

void ABoxActor::SetText(char *text) {
  if (mainLabel) {
    mainLabel->SetText(FString(ANSI_TO_TCHAR(text)));
  }
}

void ABoxActor::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);

	// Fetch directly nested boxes and lines
	TArray<ABoxActor*> boxes;
	TArray<ALineActor*> lines;
	TArray<AActor*> actors;

	GetAttachedActors(actors);

	for (auto child : actors) {
		ABoxActor *box = Cast<ABoxActor>(child);
		if (box != nullptr) {
			 boxes.Add(box);
		}

		ALineActor *line = Cast<ALineActor>(child);
		if (line != nullptr) {
			lines.Add(line);
		}
	}

	UpdateForces(boxes, lines);
	UpdatePositions(boxes, lines, DeltaSeconds);
}

// The rest of this file is physics calculations. It should be compartmentalized in its own file, 
// but I got tired reading through the holy wars on multiple-inheritance mixins vs base 
// classes vs composed, more functional approaches. I had a crtp solution, but the idea that 
// I should triple implementation LOC for the sake of some tenously defined sense of "correctness" hurts me. 
void ABoxActor::UpdateForces(TArray<ABoxActor*> boxes, TArray<ALineActor*> lines) {
	for (ABoxActor *p : boxes) {
		p->p = p->GetActorLocation();
		p->f = (p->m * GRAVITY) - (p->v * VISCOUS_DRAG);
	}

	for (ALineActor *s : lines) {
		FVector dp = s->From->p - s->To->p;
		FVector dv = s->From->v - s->To->v;
		float len = dp.Size();

		FVector nf = dv * (dp / len) * s->dampingconstant + (s->springconstant  * (len - s->restlength) * (-dp / len));

		if (!s->From->fixed) {
			s->From->f += nf;
		}

		if (!s->To->fixed) {
			s->To->f -= nf;
		}
	}
}

void ABoxActor::UpdatePositions(TArray<ABoxActor*> boxes, TArray<ALineActor*> lines, double dt) {
	for (ABoxActor *p : boxes) {
		FVector dpdt = p->v;
		FVector dvdt = p->f / p->m;

		p->p += dpdt * dt;
		p->v += dvdt * dt;
		p->SetActorLocation(p->p);
	}
}
