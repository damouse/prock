// Fill out your copyright notice in the Description page of Project Settings.

#include "ProckFPS.h"
#include "BoxActor.h"
#include <stdio.h>

/*
// See this for adding connections between actors:
// http://ironthighs.com/unreal-engine-4/coding/2015/04/18/

Possible answer: setting the particle locations
https://answers.unrealengine.com/questions/140298/attaching-particle-to-socket-of-skeletal-mesh-runt.html


*/

ABoxActor::ABoxActor() {
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SplinePipeAsset(TEXT("StaticMesh'/Game/Geometry/Meshes/S_Pipe_Spline.S_Pipe_Spline'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> cubeStaticMesh(TEXT("StaticMesh'/Game/Geometry/Meshes/1M_Cube.1M_Cube'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> beamClassFinder(TEXT("ParticleSystem'/Game/Particles/P_Beam.P_Beam'"));

	PrimaryActorTick.bCanEverTick = true;

	root = CreateDefaultSubobject<UBoxComponent>(TEXT("RootComponent"));
	RootComponent = root;
	RootComponent->SetMobility(EComponentMobility::Movable);
	//root->SetCollisionProfileName(TEXT("Pawn"));s

	UStaticMeshComponent* cube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualRepresentation"));
	cube->SetupAttachment(RootComponent);
	cube->SetMobility(EComponentMobility::Movable);

	// Set the preloaded assets
	if (cubeStaticMesh.Succeeded()) {
		cube->SetStaticMesh(cubeStaticMesh.Object);
	}

	if (beamClassFinder.Succeeded()) {
		particleBeamComponent = beamClassFinder.Object;
	}

	if (SplinePipeAsset.Succeeded()) {
		splineStaticMesh = SplinePipeAsset.Object;
	}
}

void ABoxActor::BeginPlay() {
	Super::BeginPlay();

	// Draw the lines
	AddEdge(FVector(-50, -50, -50), FVector(50, -50, -50));
	AddEdge(FVector(-50, -50, -50), FVector(-50, 50, -50));
	AddEdge(FVector(-50, 50, -50), FVector(50, 50, -50));
	AddEdge(FVector(50, -50, -50), FVector(50, 50, -50));

	AddEdge(FVector(-50, -50, 50), FVector(50, -50, 50));
	AddEdge(FVector(-50, -50, 50), FVector(-50, 50, 50));
	AddEdge(FVector(-50, 50, 50), FVector(50, 50, 50));
	AddEdge(FVector(50, -50, 50), FVector(50, 50, 50));

	AddEdge(FVector(-50, -50, -50), FVector(-50, -50, 50));
	AddEdge(FVector(-50, 50, -50), FVector(-50, 50, 50));
	AddEdge(FVector(50, 50, -50), FVector(50, 50, 50));
	AddEdge(FVector(50, -50, -50), FVector(50, -50, 50));
}

void ABoxActor::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	// Animate the box for testing purposes
	FVector NewLocation = GetActorLocation();
	float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));
	NewLocation.Z += DeltaHeight * 20.0f;       //Scale our height by a factor of 20
	RunningTime += DeltaTime;
	SetActorLocation(NewLocation);

	// Update the beam to match the spline
	// So help you god if the number of beams doesnt equal the number of splines
	for (int i = 0; i < beams.size(); i++) {
		beams[i]->SetBeamSourcePoint(0, splines[i]->GetStartPosition() + NewLocation, 0);
		beams[i]->SetBeamEndPoint(0, splines[i]->GetEndPosition() + NewLocation);
	}
}


// Draw a line (which must have already been instantiated in the constructor) at the given positions
void ABoxActor::AddEdge(FVector start, FVector end) {
	// Make a unique name for this beam and spline
	char buffer[10];
	sprintf(buffer, "Spline%d\0", (int)beams.size());
	FString name = FString(ANSI_TO_TCHAR(buffer));

	// Create the spline
	USplineMeshComponent *spline = NewObject<USplineMeshComponent>(this, FName(*(name)));
	spline->SetMobility(EComponentMobility::Movable);
	spline->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);
	spline->RegisterComponent();

	spline->ForwardAxis = ESplineMeshAxis::Z;
	spline->SetMobility(EComponentMobility::Movable);
	spline->SetStartAndEnd(start, FVector(0, 0, 0), end, FVector(0, 0, 0));
	spline->SetStartScale(FVector2D(0.1, 0.1));
	spline->SetEndScale(FVector2D(0.1, 0.1));

	// Comment this back in to make the spline 
	//spline->SetStaticMesh(splineStaticMesh); // turn this on to 

	// Create and initialize the beam
	sprintf(buffer, "Beam%d\0", (int)beams.size());
	name = FString(ANSI_TO_TCHAR(buffer));

	UParticleSystemComponent *beam = NewObject<UParticleSystemComponent>(this, FName(*(name)));
	beam->AttachToComponent(RootComponent, FAttachmentTransformRules(EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, true));
	beam->RegisterComponent();
	beam->SetTemplate(particleBeamComponent);

	// Set intial position for this beam
	beam->SetBeamSourcePoint(0, start + GetActorLocation(), 0);
	beam->SetBeamEndPoint(0, end + GetActorLocation());

	// Store the beam and the spline
	splines.push_back(spline);
	beams.push_back(beam);
}
