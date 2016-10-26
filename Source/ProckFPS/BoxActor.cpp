// Fill out your copyright notice in the Description page of Project Settings.

#include "ProckFPS.h"
#include "BoxActor.h"
#include <stdio.h>

/*
Possible solutions to spawning components at runtime
https://answers.unrealengine.com/questions/160501/how-do-i-properly-procedurally-add-components-in-c.html
https://forums.unrealengine.com/showthread.php?52410-What-is-the-correct-way-to-create-and-add-components-at-runtime
*/

ABoxActor::ABoxActor() {
	//beams = {};

	USphereComponent* SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	RootComponent = SphereComponent;

	ConstructorHelpers::FObjectFinder<UParticleSystem> beamClassFinder(TEXT("ParticleSystem'/Game/Particles/P_Beam.P_Beam'"));

	// For now createDefaultSubobject only works during construction time. This is obviously going to limit usability, but 
	// if we can move this then making it dynamic should be relatively simple
	 for (int i = 0; i < 12; i++) {
		char buffer[10];
		sprintf(buffer, "Beam%d\0", i);
		FString name = FString(ANSI_TO_TCHAR(buffer));

	 	UParticleSystemComponent *newBeam = CreateDefaultSubobject<UParticleSystemComponent>(FName(*(name)));
	 	newBeam->SetTemplate(beamClassFinder.Object);
	 	beams.push_back(newBeam);
	 }
}

void ABoxActor::BeginPlay() {
	Super::BeginPlay();

	// Draw the lines
	AddEdge(FVector(0, 0, 200), FVector(100, 0, 200), 0);
	AddEdge(FVector(0, 0, 200), FVector(0, 100, 200), 1);
	AddEdge(FVector(0, 100, 200), FVector(100, 100, 200), 2);
	AddEdge(FVector(100, 0, 200), FVector(100, 100, 200), 3);

	AddEdge(FVector(0, 0, 300), FVector(100, 0, 300), 4);
	AddEdge(FVector(0, 0, 300), FVector(0, 100, 300), 5);
	AddEdge(FVector(0, 100, 300), FVector(100, 100, 300), 6);
	AddEdge(FVector(100, 0, 300), FVector(100, 100, 300), 7);

	AddEdge(FVector(0, 0, 200), FVector(0, 0, 300), 8);
	AddEdge(FVector(0, 100, 200), FVector(0, 100, 300), 9);
	AddEdge(FVector(100, 100, 200), FVector(100, 100, 300), 10);
	AddEdge(FVector(100, 0, 200), FVector(100, 0, 300), 11);
}

// Draw a line (which must have already been instantiated in the constructor) at the given positions
void ABoxActor::AddEdge(FVector start, FVector end, int i) {
	beams[i]->SetBeamSourcePoint(0, start, 0);
	beams[i]->SetBeamEndPoint(0, end);
	beams[i]->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);
}