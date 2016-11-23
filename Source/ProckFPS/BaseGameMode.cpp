// Fill out your copyright notice in the Description page of Project Settings.

#include "ProckFPS.h"
#include "BaseGameMode.h"

#include "Nodes/ProckNodeSubclasses.h"
#include "Glue/Ghost.h"
#include "Glue/Scope.h"
#include "Utils/Config.h"


ABaseGameMode::ABaseGameMode() {
	UConfig::world = GetWorld();	
}

void ABaseGameMode::BeginPlay() {
	// Load the room instance which starts the game in the map
	for (TActorIterator<ABoxActor> ActorItr(GetWorld()); ActorItr; ++ActorItr) {
		room = *ActorItr;
	}

	if (!room) {
		UE_LOG(LogProck, Error, TEXT("Room doesnt exist, can't load"));
		return;
	}

	peter = new Peter();
	ProckNode *root = peter->LoadPython();

	if (root) {
		// The first box is already placed, assign it as the root's box
		root->box = room;
		root->Spawn(nullptr, FVector());
	}
}