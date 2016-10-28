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
	static ConstructorHelpers::FObjectFinder<UParticleSystem> beamActorClassFinder(TEXT("ParticleSystem'/Game/Particles/P_Beam_Actor.P_Beam_Actor'"));

	PrimaryActorTick.bCanEverTick = true;

	UBoxComponent* root = CreateDefaultSubobject<UBoxComponent>(TEXT("RootComponent"));
	root->SetMobility(EComponentMobility::Movable);
	root->SetSimulatePhysics(true);
	root->SetEnableGravity(false);
	root->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
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
	mainLabel->SetRelativeLocation(FVector(35, 50, 35)); 	// Try to center the text as much as possible. Todo: actually center the text
	mainLabel->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f)); // Rotate so text faces the positive y direction

	// Set the preloaded assets
	if (cubeStaticMesh.Succeeded()) {
		// This is just for visualization
		//cube->SetStaticMesh(cubeStaticMesh.Object);
	}

	if (beamClassFinder.Succeeded()) {
		particleBeamComponent = beamClassFinder.Object;
	}
	
	if (beamActorClassFinder.Succeeded()) {
		particleBeamActorComponent = beamActorClassFinder.Object;
	}

	if (SplinePipeAsset.Succeeded()) {
		splineStaticMesh = SplinePipeAsset.Object;
	}

	// Create the lines
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

void ABoxActor::BeginPlay() {
	Super::BeginPlay();
}

void ABoxActor::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	// Update the beam to match the spline. TODO: rotation
	for (int i = 0; i < beams.size(); i++) {
		beams[i]->SetBeamSourcePoint(0, splines[i]->GetStartPosition()* GetActorScale() + GetActorLocation(), 0);
		beams[i]->SetBeamEndPoint(0, splines[i]->GetEndPosition()* GetActorScale() + GetActorLocation());
	}

	// Animate the box for testing purposes
	//FVector NewLocation = GetActorLocation();
	//float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));
	//NewLocation.Z += DeltaHeight * 20.0f;       //Scale our height by a factor of 20
	//RunningTime += DeltaTime;
	//SetActorLocation(NewLocation);
}

// Draw a line (which must have already been instantiated in the constructor) at the given positions
// All the commented out areas here are to allow adding lines at runtime. Currently disabled
void ABoxActor::AddEdge(FVector start, FVector end) {
	// Make a unique name for this beam and spline
	char buffer[10];
	sprintf(buffer, "Spline%d\0", (int)beams.size());
	FString name = FString(ANSI_TO_TCHAR(buffer));

	// Create the spline
	USplineMeshComponent* spline = CreateDefaultSubobject<USplineMeshComponent>(FName(*(name)));
	spline->SetMobility(EComponentMobility::Movable);
	spline->SetupAttachment(RootComponent);

	spline->ForwardAxis = ESplineMeshAxis::Z;
	spline->SetMobility(EComponentMobility::Movable);
	spline->SetStartAndEnd(start, FVector(0, 0, 0), end, FVector(0, 0, 0));
	spline->SetStartScale(FVector2D(0.1, 0.1));
	spline->SetEndScale(FVector2D(0.1, 0.1));

	// Comment this on to set a mesh instead of a beam 
	//spline->SetStaticMesh(splineStaticMesh);

	// Create and initialize the beam
	sprintf(buffer, "Beam%d\0", (int)beams.size());
	name = FString(ANSI_TO_TCHAR(buffer));

	//UParticleSystemComponent *beam = NewObject<UParticleSystemComponent>(this, FName(*(name)));
	UParticleSystemComponent* beam = CreateDefaultSubobject<UParticleSystemComponent>(FName(*(name)));
	beam->SetTemplate(particleBeamComponent);
	beam->RegisterComponent();

	// Store the beam and the spline
	splines.push_back(spline);
	beams.push_back(beam);
}

// Create a beam attached to each actor 
void ABoxActor::ConnectToBox(ABoxActor* other) {
	char buffer[10];
	sprintf(buffer, "Connection%d\0", (int)connections.size());
	FString name = FString(ANSI_TO_TCHAR(buffer));

	UParticleSystemComponent *beam = NewObject<UParticleSystemComponent>(this, (FName(*(name))));
	beam->RegisterComponent();
	beam->SetTemplate(particleBeamActorComponent);
	beam->SetActorParameter(TEXT("BeamSource"), this);
	beam->SetActorParameter(TEXT("BeamTarget"), other);

	connections.push_back(beam);
}

void ABoxActor::SetText(char *text) {
	mainLabel->SetText(FString(ANSI_TO_TCHAR(text)));
}