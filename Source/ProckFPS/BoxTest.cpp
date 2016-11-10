// Fill out your copyright notice in the Description page of Project Settings.

#include "ProckFPS.h"
#include "BoxTest.h"


// Sets default values
ABoxTest::ABoxTest() {
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//ConstructorHelpers::FObjectFinder<UParticleSystem> beamClassFinder(TEXT("ParticleSystem'/Game/Particles/P_Beam.P_Beam'"));
	//beam = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Bae"));
	//beam->SetTemplate(beamClassFinder.Object);
}

// Called when the game starts or when spawned
void ABoxTest::BeginPlay() {
	Super::BeginPlay();	

	// This works for creating the dimensions of the boxes. It might be ok to set them up with particle systems
	// for now; should be able to replace the particles with something else point by point

	//beam->SetBeamSourcePoint(0, FVector(0, 0, 400), 0);
	//beam->SetBeamEndPoint(0, FVector(0, 100, 400));
	//beam->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);
}

void ABoxTest::CursorOver() {
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Overlap started"));
}
