// Fill out your copyright notice in the Description page of Project Settings.

#include "ProckFPS.h"
#include "BaseGameMode.h"
#include "Nodes/ProckNodeSubclasses.h"

#include "Glue/Ghost.h"
#include "Glue/Scope.h"

ABaseGameMode::ABaseGameMode() {
	static ConstructorHelpers::FClassFinder<ABoxActor> boxBPFinder(TEXT("Blueprint'/Game/Blueprints/BoxActorBP'"));
	if (boxBPFinder.Class != NULL) {
		ProckNode::boxBPClass = boxBPFinder.Class;
	}

	static ConstructorHelpers::FClassFinder<AGhostActor> ghostBPFinder(TEXT("Blueprint'/Game/Blueprints/GhostActorBP'"));
	if (ghostBPFinder.Class != NULL) {
		ProckNode::ghostBPClass = ghostBPFinder.Class;
	}

	static ConstructorHelpers::FClassFinder<ALineActor> lineBPFinder(TEXT("Blueprint'/Game/Blueprints/LineActorBP'"));
	if (lineBPFinder.Class != NULL) {
		ProckNode::lineBPClass = lineBPFinder.Class;
	}

	ProckNode::world = GetWorld();	
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

		//for (Ghost *g : root->Scope->ghosts) {
		//	UE_LOG(LogProck, Log, TEXT("%s"), UTF8_TO_TCHAR(g->name));
		//}

		// Spawn ghosts
		root->Scope->Spawn(root);

		// Make connections
	}
}