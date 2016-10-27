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


// See this for adding connections between actors:
// http://ironthighs.com/unreal-engine-4/coding/2015/04/18/
*/

ABoxActor::ABoxActor() {
	root = CreateDefaultSubobject<UBoxComponent>(TEXT("RootComponent"));
	RootComponent = root;
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

	// Updates the positions of the beams
	FVector OldLocation = GetActorLocation();

	FVector NewLocation = GetActorLocation();
	float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));
	NewLocation.Z += DeltaHeight * 20.0f;       //Scale our height by a factor of 20
	RunningTime += DeltaTime;
	SetActorLocation(NewLocation);

	// Updates the positions of the beams. Very resource intensive. 
	FVector diff = NewLocation - OldLocation;

	for (UParticleSystemComponent *beam : beams) {
		FVector source;
		FVector target;

		beam->GetBeamSourcePoint(0, 0, source);
		beam->GetBeamEndPoint(0, target);

		beam->SetBeamSourcePoint(0, source + diff, 0);
		beam->SetBeamEndPoint(0, target + diff);
	}
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
