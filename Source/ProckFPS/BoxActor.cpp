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
	root = CreateDefaultSubobject<UBoxComponent>(TEXT("RootComponent"));
	RootComponent = root;
	RootComponent->SetMobility(EComponentMobility::Movable);
	//root->SetCollisionProfileName(TEXT("Pawn"));

	UStaticMeshComponent* SphereVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualRepresentation"));
	SphereVisual->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("StaticMesh'/Game/Geometry/Meshes/1M_Cube.1M_Cube'"));

	if (SphereVisualAsset.Succeeded()) {
		SphereVisual->SetStaticMesh(SphereVisualAsset.Object);
	}

	// Load the particle beam and store the resulting object
	static ConstructorHelpers::FObjectFinder<UParticleSystem> beamClassFinder(TEXT("ParticleSystem'/Game/Particles/P_Beam.P_Beam'"));
	particleBeamComponent = beamClassFinder.Object;

	PrimaryActorTick.bCanEverTick = true;

	// So this works. The mesh currently being used is not terribly useful, however
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SplinePipeAsset(TEXT("StaticMesh'/Game/Geometry/Meshes/S_Pipe_Spline.S_Pipe_Spline'"));
	spline = CreateDefaultSubobject<USplineMeshComponent>(TEXT("SplineTest"));
	
	spline->ForwardAxis = ESplineMeshAxis::Z;
	spline->SetMobility(EComponentMobility::Movable);
	spline->SetStaticMesh(SplinePipeAsset.Object);
	spline->SetupAttachment(RootComponent);

	FVector start(0, 0, 100);
	FVector end(100, 100, 100);

	spline->SetStartAndEnd(start, FVector(0, 0, 0), end, FVector(0, 0, 0));
	spline->SetStartScale(FVector2D(0.1, 0.1));
	spline->SetEndScale(FVector2D(0.1, 0.1));
}

void ABoxActor::BeginPlay() {
	Super::BeginPlay();

	//spline->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);

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

	// Updates the positions of the beams
	FVector OldLocation = GetActorLocation();

	FVector NewLocation = GetActorLocation();
	float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));
	NewLocation.Z += DeltaHeight * 20.0f;       //Scale our height by a factor of 20
	RunningTime += DeltaTime;
	SetActorLocation(NewLocation);

	// Updates the positions of the beams. Likely to very resource intensive, but I can't get them to connect any other way 
	//FVector diff = NewLocation - OldLocation;

	//for (UParticleSystemComponent *beam : beams) {
	//	FVector source;
	//	FVector target;

	//	beam->GetBeamSourcePoint(0, 0, source);
	//	beam->GetBeamEndPoint(0, target);

	//	beam->SetBeamSourcePoint(0, source + diff, 0);
	//	beam->SetBeamEndPoint(0, target + diff);
	//}
}


// Draw a line (which must have already been instantiated in the constructor) at the given positions
void ABoxActor::AddEdge(FVector start, FVector end) {
	// Make a unique name for this beam
	char buffer[10];
	sprintf(buffer, "Beam%d\0", (int)beams.size());
	FString name = FString(ANSI_TO_TCHAR(buffer));

	// Create and initialize the beam
	UParticleSystemComponent *beam = NewObject<UParticleSystemComponent>(this, FName(*(name)));
	beam->SetAutoAttachmentParameters(RootComponent, TEXT("Whatissocket"), EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative);
	beam->AttachToComponent(RootComponent, FAttachmentTransformRules(EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, true));
	beam->RegisterComponent();

	//particleBeamComponent->Emitt
	beam->SetTemplate(particleBeamComponent);

	// Works except that we don't want to connect to actors...
	//beam->SetActorParameter("BeamSource", this);
	//beam->SetActorParameter("BeamTarget", this);

	// note that we're specifying the relatives here because I can't get the formal attachment to work. 
	beam->SetBeamSourcePoint(0, start + GetActorLocation(), 0);
	beam->SetBeamEndPoint(0, end + GetActorLocation());

	// Really should get them to work, its pointless overhead updating the beams
	//beam->SetBeamSourcePoint(0, start, 0);
	//beam->SetBeamEndPoint(0, end);

	// Store the beam
	beams.push_back(beam);
}
