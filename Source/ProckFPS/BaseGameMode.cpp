// Fill out your copyright notice in the Description page of Project Settings.

#include "ProckFPS.h"
#include "BaseGameMode.h"
#include "ProckNode.h"
#include "BoxActor.h"

ABaseGameMode::ABaseGameMode() {
	static ConstructorHelpers::FClassFinder<ABoxActor> boxBPFinder(TEXT("Blueprint'/Game/Blueprints/BoxActorBP'"));
	if (boxBPFinder.Class != NULL) {
		boxBPClass = boxBPFinder.Class;
	}
}

void ABaseGameMode::BeginPlay() {
	// Load the room instance which was statically placed in the world
	for (TActorIterator<ABoxActor> ActorItr(GetWorld()); ActorItr; ++ActorItr) {
		UE_LOG(LogProck, Log, TEXT("Loaded room"));
		room = *ActorItr;
	}

	peter = new Peter();
	ProckNode *root = peter->LoadPython();

	root->box = GetWorld()->SpawnActor<ABoxActor>(boxBPClass);
	root->box->SetText("A");
	root->box->SizeFitContents();

	root->box->AttachToComponent(room->GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);
	root->box->SetActorScale3D(FVector(0.2f, 0.2f, 0.2f));

	//root->box->AttachToActor(room, FAttachmentTransformRules::SnapToTargetIncludingScale);
	//root->box->SetActorRelativeTransform(FTransform());
	//root->box->SetActorRelativeLocation(FVector());

	//// Spawn a nested box in the coordinate space of its parent (for nesting boxes)
	//ABoxTest *child = (ABoxTest *)GetWorld()->SpawnActor<AActor>(boxBPClass);
	//child->AttachToComponent(box->GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);
	//child->SetActorScale3D(FVector(0.5f, 0.5f, 0.5f));

	//if (root) {
	//	Spawn(GetWorld(), boxBPClass, root, FVector(-120, -60, 45));
	//}

	// Here we can spawn the box, remove its coloring, and resize it to fit the room

	/*
	Spawn the box, remove its coloring, resize it to a "Room"

	Then in c++ trigger the draw for all children.
		ProckNode->SpawnInternal()

	This: 
		- Triggers a scope collection
		- Draws a box for each PNode with relative positioning, collecting offset data
		- Connects the lines

	Note that the drawing and the scaling 
	*/
}