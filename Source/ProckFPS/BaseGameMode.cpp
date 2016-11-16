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
		ABoxActor *room = *ActorItr;
	}

	peter = new Peter();
	ProckNode *root = peter->LoadPython();

	root->box = GetWorld()->SpawnActor<ABoxActor>(boxBPClass, FVector(), FRotator::ZeroRotator);
	root->box->SetText("A");
	root->box->SizeFitContents();

	root->box->AttachToActor(room, FAttachmentTransformRules::SnapToTargetIncludingScale);
	root->box->SetActorRelativeTransform(FTransform());

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