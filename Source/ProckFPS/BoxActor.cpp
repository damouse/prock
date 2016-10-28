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
	root->SetMobility(EComponentMobility::Movable);

	// Box valls through if the cube doesn't have its static mesh turned on
	root->SetSimulatePhysics(true);
	root->SetEnableGravity(false);
	root->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	// The purpose of this is to get the shape to hold its origin at 0,0.
	// Unfortunatly, that messes with the collision boxes and causes all sorts of problems. 
	// There may not be a lot of sense to committing to keeping things at 0, 0. 
	// We're going to need programmatic dimensions anyway, might as well set 0, 0 as the center
	//root->SetRelativeLocation(FVector(50, 50, 50));

	RootComponent = root;

	UStaticMeshComponent* cube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualRepresentation"));
	cube->SetupAttachment(RootComponent);
	cube->SetMobility(EComponentMobility::Movable);
	cube->SetRelativeLocation(FVector(50, 50, 50));

	// Set up our text render
	mainLabel = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Label"));
	mainLabel->SetTextRenderColor(FColor::White);
	mainLabel->SetText(FText::FromString(TEXT("Var")));
	mainLabel->SetupAttachment(RootComponent);

	// Try to center the text as much as possible. Todo: actually center the text
	mainLabel->SetRelativeLocation(FVector(35, 50, 35));
	mainLabel->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f)); // Rotate so text faces the positive y direction

	//mainLabel->SetWorldSize(500);
	//Text->SetRelativeLocation(FVector(-282.f, 100, 100.f));
	//mainLabel->SetTextRenderColor(FColor::Red);
	
	// Set the preloaded assets
	if (cubeStaticMesh.Succeeded()) {
		// We actually do get collisions without the mesh, that comes from Root above
		// This is just for visualization
		//cube->SetStaticMesh(cubeStaticMesh.Object);
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
	// The way this is written now 
	AddEdge(FVector(0, 0, 0), FVector(100, 0, 0));
	AddEdge(FVector(0, 0, 0), FVector(0, 100, 0));
	AddEdge(FVector(0, 100, 0), FVector(100, 100, 0));
	AddEdge(FVector(100, 0, 0), FVector(100, 100, 0));

	AddEdge(FVector(0, 0, 100), FVector(100, 0, 100));
	AddEdge(FVector(0, 0, 100), FVector(0, 100, 100));
	AddEdge(FVector(0, 100, 100), FVector(100, 100, 100));
	AddEdge(FVector(100, 0, 100), FVector(100, 100, 100));

	AddEdge(FVector(0, 0, 0), FVector(0, 0, 100));
	AddEdge(FVector(0, 100, 0), FVector(0, 100, 100));
	AddEdge(FVector(100, 100, 0), FVector(100, 100, 100));
	AddEdge(FVector(100, 0, 0), FVector(100, 0, 100));
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

		// Rotation is not covered here
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
