// Fill out your copyright notice in the Description page of Project Settings.

#include "ProckFPS.h"
#include "BaseGameMode.h"
#include "ProckNode.h"
#include "BoxActor.h"

ABaseGameMode::ABaseGameMode() {
	// Do we need this twice? No, likely not.
	ProckNode::world = GetWorld();

	static ConstructorHelpers::FClassFinder<ABoxActor> boxBPFinder(TEXT("Blueprint'/Game/Blueprints/BoxActorBP'"));
	if (boxBPFinder.Class != NULL) {
		ProckNode::boxBPClass = boxBPFinder.Class;
	}
}

void ABaseGameMode::BeginPlay() {
	// Load the room instance which starts the game in the map
	for (TActorIterator<ABoxActor> ActorItr(GetWorld()); ActorItr; ++ActorItr) {
		UE_LOG(LogProck, Log, TEXT("Loaded room"));
		room = *ActorItr;
	}

	peter = new Peter();
	ProckNode *root = peter->LoadPython();

	if (!room) {
		UE_LOG(LogProck, Log, TEXT("Room doesnt exist, can't load"));
		return;
	}

	if (root) {
		// The first box is already placed, assign it as the root's box
		root->box = room;
		root->Spawn(nullptr, FVector());
	}
}