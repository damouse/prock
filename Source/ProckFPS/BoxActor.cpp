// Fill out your copyright notice in the Description page of Project Settings.

#include "ProckFPS.h"
#include "BoxActor.h"
#include <stdio.h>

/*
Possible solutions to spawning components at runtime
https://answers.unrealengine.com/questions/160501/how-do-i-properly-procedurally-add-components-in-c.html
https://forums.unrealengine.com/showthread.php?52410-What-is-the-correct-way-to-create-and-add-components-at-runtime

UObject* something = StaticLoadObject(UObject::StaticClass(), nullptr, TEXT("ParticleSystem'/Game/Particles/P_Beam.P_Beam'"));
UBlueprint* bp = Cast<UBlueprint>(something);
TSubclassOf<class UObject> MyItemBlueprint;
MyItemBlueprint = (UClass*)bp->GeneratedClass;

This is the code from the first one. Doesn't work because its not a blueprint
*/

ABoxActor::ABoxActor() {
	USphereComponent* SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	RootComponent = SphereComponent;

	// Load the particle beam and store the resulting object
	static ConstructorHelpers::FObjectFinder<UParticleSystem> beamClassFinder(TEXT("ParticleSystem'/Game/Particles/P_Beam.P_Beam'"));
	particleBeamComponent = beamClassFinder.Object;
}

void ABoxActor::BeginPlay() {
	Super::BeginPlay();

	// Draw the lines
	AddEdge(FVector(0, 0, 200), FVector(100, 0, 200));
	AddEdge(FVector(0, 0, 200), FVector(0, 100, 200));
	AddEdge(FVector(0, 100, 200), FVector(100, 100, 200));
	AddEdge(FVector(100, 0, 200), FVector(100, 100, 200));

	AddEdge(FVector(0, 0, 300), FVector(100, 0, 300));
	AddEdge(FVector(0, 0, 300), FVector(0, 100, 300));
	AddEdge(FVector(0, 100, 300), FVector(100, 100, 300));
	AddEdge(FVector(100, 0, 300), FVector(100, 100, 300));

	AddEdge(FVector(0, 0, 200), FVector(0, 0, 300));
	AddEdge(FVector(0, 100, 200), FVector(0, 100, 300));
	AddEdge(FVector(100, 100, 200), FVector(100, 100, 300));
	AddEdge(FVector(100, 0, 200), FVector(100, 0, 300));
}

// Draw a line (which must have already been instantiated in the constructor) at the given positions
void ABoxActor::AddEdge(FVector start, FVector end) {
	// Make a unique name for this beam
	char buffer[10];
	sprintf(buffer, "Beam%d\0", (int)beams.size());
	FString name = FString(ANSI_TO_TCHAR(buffer));

	// Create and initialize the beam
	UParticleSystemComponent *beam = NewObject<UParticleSystemComponent>(this, FName(*(name)));
	beam->RegisterComponent();
	beam->SetTemplate(particleBeamComponent);

	beam->SetBeamSourcePoint(0, start, 0);
	beam->SetBeamEndPoint(0, end);
	beam->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);

	// Store the beam
	beams.push_back(beam);
}

// Can we draw the lines here?

//UParticleSystem* newComp = ConstructObject<UParticleSystem>(comp->GetClass());

//newBeam = NewObject<UParticleSystemComponent>(this, UParticleSystemComponent::StaticClass());
//newBeam->RegisterComponent();

//newBeam->SetTemplate(comp);
//newBeam->SetBeamSourcePoint(0, FVector(100, 0, 200), 0);
//newBeam->SetBeamEndPoint(0, FVector(100, 100, 200));
//newBeam->SetActive(true);
//newBeam->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);