// Fill out your copyright notice in the Description page of Project Settings.

#include "ProckFPS.h"
#include "BaseGameMode.h"

#include "Nodes/ProckNodeSubclasses.h"

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

	peter->RunPython();

	return;

	if (root) {
		// The first box is already placed, assign it as the root's box
		root->box = room;
		root->Spawn(nullptr, FVector());
	}
}

void ABaseGameMode::Run() {
	// Load the code, move it to the background
	
	/*
	Running: 

	Scope			collection of variables. Can be created during a run cycle
	Run Cycle		one step of the runner, corresponding to the execution of a single line of code

	Tick:			windup animation
	Turnover:		step debugger and update values instantaneously
	Tock:			winddown animation
	*/
}