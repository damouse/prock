// Fill out your copyright notice in the Description page of Project Settings.

#include "ProckFPS.h"
#include "BoxActor.h"
#include <stdio.h>
#include <math.h>  

/*
// See this for adding connections between actors:
// http://ironthighs.com/unreal-engine-4/coding/2015/04/18/

Possible answer: setting the particle locations
https://answers.unrealengine.com/questions/140298/attaching-particle-to-socket-of-skeletal-mesh-runt.html
*/

ABoxActor::ABoxActor() {
	//static ConstructorHelpers::FObjectFinder<UStaticMesh> SplinePipeAsset(TEXT("StaticMesh'/Game/Geometry/Meshes/S_Pipe_Spline.S_Pipe_Spline'"));
	//static ConstructorHelpers::FObjectFinder<UStaticMesh> cubeStaticMesh(TEXT("StaticMesh'/Game/Geometry/Meshes/Cube.Cube'"));
	//static ConstructorHelpers::FObjectFinder<UParticleSystem> beamClassFinder(TEXT("ParticleSystem'/Game/Particles/P_Beam.P_Beam'"));
	//static ConstructorHelpers::FObjectFinder<UParticleSystem> beamActorClassFinder(TEXT("ParticleSystem'/Game/Particles/P_Beam_Actor.P_Beam_Actor'"));
	//static ConstructorHelpers::FObjectFinder<UFont> fontAssetFinder(TEXT("Font'/Game/Inconsolata.Inconsolata'"));
	//static ConstructorHelpers::FObjectFinder<UMaterial> fontMaterialFinder(TEXT("Material'/Game/M_Label.M_Label'"));

	//PrimaryActorTick.bCanEverTick = true;

	// The invisible root component
	//UBoxComponent* root = CreateDefaultSubobject<UBoxComponent>(TEXT("RootComponent"));
	//root->SetMobility(EComponentMobility::Movable);
	//root->SetSimulatePhysics(true);
	//root->SetEnableGravity(false);
	//root->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	//RootComponent = root;

	//// Visible translucent body
	//cube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualRepresentation"));
	//cube->SetupAttachment(RootComponent);

	//// Centered label
	//mainLabel = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Label"));
	//mainLabel->SetTextRenderColor(FColor::White);
	//mainLabel->SetText(FText::FromString(TEXT("MainLabel")));
	//mainLabel->SetupAttachment(RootComponent);
	//mainLabel->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f)); // Rotate so text faces the positive y direction

	//// Set the preloaded assets
	//if (cubeStaticMesh.Succeeded()) {
	//	cube->SetStaticMesh(cubeStaticMesh.Object);
	//}

	//if (beamClassFinder.Succeeded()) {
	//	particleBeamComponent = beamClassFinder.Object;
	//}

	//if (beamActorClassFinder.Succeeded()) {
	//	particleBeamActorComponent = beamActorClassFinder.Object;
	//}

	//if (SplinePipeAsset.Succeeded()) {
	//	splineStaticMesh = SplinePipeAsset.Object;
	//}

	//if (fontAssetFinder.Succeeded()) {
	//	mainLabel->SetFont(fontAssetFinder.Object);
	//}

	//if (fontMaterialFinder.Succeeded()) {
	//	mainLabel->SetTextMaterial(fontMaterialFinder.Object);
	//}

	// Create the lines
	//AddEdge(FVector(0, 0, 0), FVector(100, 0, 0));
	//AddEdge(FVector(0, 0, 0), FVector(0, 100, 0));
	//AddEdge(FVector(0, 100, 0), FVector(100, 100, 0));
	//AddEdge(FVector(100, 0, 0), FVector(100, 100, 0));

	//AddEdge(FVector(0, 0, 100), FVector(100, 0, 100));
	//AddEdge(FVector(0, 0, 100), FVector(0, 100, 100));
	//AddEdge(FVector(0, 100, 100), FVector(100, 100, 100));
	//AddEdge(FVector(100, 0, 100), FVector(100, 100, 100));

	//AddEdge(FVector(0, 0, 0), FVector(0, 0, 100));
	//AddEdge(FVector(0, 100, 0), FVector(0, 100, 100));
	//AddEdge(FVector(100, 100, 0), FVector(100, 100, 100));
	//AddEdge(FVector(100, 0, 0), FVector(100, 0, 100));
}

/*
This method resolves the size of its internal contents (somewhat) and resizes
the translucent portion of the box to match them. 

It should be looking at nested nodes to do this resolution. Right now its just checking the size of its text
*/
FVector ABoxActor::SizeFitContents() {
	return FVector();

	// Get the target size of the label and calculate a new size 
	FVector labelSize = mainLabel->GetTextLocalSize();
	FVector newSize;

	newSize.Y = BOX_DEPTH;
	newSize.Z = labelSize.Z + LABEL_MARGIN * 2;
	newSize.X = labelSize.Y + LABEL_MARGIN * 2;

	// Update the volume. The div(100) is for the base size of the box mesh
	FVector scale(newSize.X / 100, newSize.Y / 100, newSize.Z / 100);
	cube->SetRelativeScale3D(scale);

	// Center the label by halving its dimensions
	mainLabel->SetRelativeLocation(FVector(-newSize.X / 2 + LABEL_MARGIN, 0, -newSize.Z / 2 + LABEL_MARGIN));

	return newSize;
}

void ABoxActor::SetText(char *text) {
	//UE_LOG(LogProck, Log, TEXT("Setting label to: %s"), UTF8_TO_TCHAR(text));
	SetMainLabelText(FText::FromString(FString(UTF8_TO_TCHAR(text))));
	
}

// DEPRECATED
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
	return;

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

//// Spawn a nested box in the coordinate space of its parent (for nesting boxes)
//ABoxTest *child = (ABoxTest *)GetWorld()->SpawnActor<AActor>(boxBPClass);
//child->AttachToComponent(box->GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);
//child->SetActorScale3D(FVector(0.5f, 0.5f, 0.5f));

//void ABoxActor::CursorOver() {
//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Overlap started"));
//}