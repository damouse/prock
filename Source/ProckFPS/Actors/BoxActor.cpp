// Fill out your copyright notice in the Description page of Project Settings.

#include "ProckFPS.h"

#include "Actors/BoxActor.h"
#include "Actors/LineActor.h"

#include "Utils/Config.h"

#include <stdio.h>
#include <math.h> 

// Used in physics calculations below
const FVector VEC_DOWN(0, 0, -1);
const FVector VEC_ZERO();


void ABoxActor::BeginPlay() {
	PrimaryActorTick.bCanEverTick = true;
}

void ABoxActor::SetText(char *text) {
  if (mainLabel) {
    mainLabel->SetText(FString(ANSI_TO_TCHAR(text)));
  }
}

void ABoxActor::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);
	dt += DeltaSeconds;

	// Trying to roll over dt to avoid instability issues with euler's method. Seems to work? 
	// I think the time issues with euler present themselves in long-running simulations. Since we update 
	// "instantaneously," I'm hoping the problem is just solved?
	if (dt > 1) {
		dt = 0;	
	}

	// Fetch directly nested boxes and lines
	TArray<ABoxActor*> boxes;
	TArray<ALineActor*> lines;

	for (auto child : Children) {
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
	UpdatePositions(boxes, lines);
}

// The rest of this file is physics calculations. It should be compartmentalized in its own file, 
// but I got tired reading through the holy wars on multiple-inheritance mixins vs base 
// classes vs composed, more functional approaches. So its here.
void ABoxActor::UpdateForces(TArray<ABoxActor*> boxes, TArray<ALineActor*> lines) {
	for (ABoxActor *p : boxes) {
		p->p = p->GetActorLocation();
		p->f = (GRAVITY * p->m * VEC_DOWN) - (VISCOUS_DRAG * p->v);
	}

	for (ALineActor *s : lines) {
		FVector d = s->From->p - s->To->p;
		float len = d.Size();
		FVector nf;

		nf.X = s->springconstant  * (len - s->restlength);
		nf.X += s->dampingconstant * (s->From->v.X - s->To->v.X) * d.X / len;
		nf.X *= -d.X / len;

		nf.Y = s->springconstant  * (len - s->restlength);
		nf.Y += s->dampingconstant * (s->From->v.Y - s->To->v.Y) * d.Y / len;
		nf.Y *= -d.Y / len;

		nf.Z = s->springconstant  * (len - s->restlength);
		nf.Z += s->dampingconstant * (s->From->v.Z - s->To->v.Z) * d.Z / len;
		nf.Z *= -d.Z / len;

		if (!s->From->fixed) {
			s->From->f += nf;
		}

		if (!s->To->fixed) {
			s->To->f -= nf;
		}
	}
}

void ABoxActor::UpdatePositions(TArray<ABoxActor*> boxes, TArray<ALineActor*> lines) {

}

// /*
// Perform one step of the solver
// */
// void UpdateParticles(PARTICLE *p, int np, PARTICLEPHYS phys, PARTICLESPRING *s, int ns, double dt, int method) {
// 	int i;
// 	PARTICLEDERIVATIVES *deriv;
// 	PARTICLE *ptmp;
// 	deriv = (PARTICLEDERIVATIVES *)malloc(np * sizeof(PARTICLEDERIVATIVES));

// 	CalculateForces(p, np, phys, s, ns);
// 	CalculateDerivatives(p, np, deriv);
// 	ptmp = (PARTICLE *)malloc(np * sizeof(PARTICLE));

// 	for (i = 0; i<np; i++) {
// 		ptmp[i] = p[i];
// 		ptmp[i].p->X += deriv[i].dpdt.X * dt / 2;
// 		ptmp[i].p->Y += deriv[i].dpdt.Y * dt / 2;
// 		ptmp[i].p->Z += deriv[i].dpdt.Z * dt / 2;

// 		ptmp[i].p->X += deriv[i].dvdt.X * dt / 2;
// 		ptmp[i].p->Y += deriv[i].dvdt.Y * dt / 2;
// 		ptmp[i].p->Z += deriv[i].dvdt.Z * dt / 2;
// 	}

// 	CalculateForces(ptmp, np, phys, s, ns);
// 	CalculateDerivatives(ptmp, np, deriv);

// 	for (i = 0; i<np; i++) {
// 		p[i].p->X += deriv[i].dpdt.X * dt;
// 		p[i].p->Y += deriv[i].dpdt.Y * dt;
// 		p[i].p->Z += deriv[i].dpdt.Z * dt;
// 		p[i].v.X += deriv[i].dvdt.X * dt;
// 		p[i].v.Y += deriv[i].dvdt.Y * dt;
// 		p[i].v.Z += deriv[i].dvdt.Z * dt;
// 	}

// 	free(ptmp);
// 	free(deriv);
// }

// void CalculateDerivatives(PARTICLE *p, int np, PARTICLEDERIVATIVES *deriv) {
// 	int i;

// 	for (i = 0; i<np; i++) {
// 		deriv[i].dpdt.X = p[i].v.X;
// 		deriv[i].dpdt.Y = p[i].v.Y;
// 		deriv[i].dpdt.Z = p[i].v.Z;
// 		deriv[i].dvdt.X = p[i].f.X / p[i].m;
// 		deriv[i].dvdt.Y = p[i].f.Y / p[i].m;
// 		deriv[i].dvdt.Z = p[i].f.Z / p[i].m;
// 	}
// }
