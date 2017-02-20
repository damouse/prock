// Fill out your copyright notice in the Description page of Project Settings.

#include "ProckFPS.h"
#include "BaseGameMode.h"


#include "Nodes/ProckNodeSubclasses.h"

#include "Utils/Config.h"


ABaseGameMode::ABaseGameMode() {
	UConfig::world = GetWorld();	
}

void ABaseGameMode::BeginPlay() {
	// Loads the static boxes-- boxes placed in fixed positions in the editor before Prock loads
	for (TActorIterator<ABoxActor> ActorItr(GetWorld()); ActorItr; ++ActorItr) {
		if (ActorItr->GetName().Equals("Room")) {
			room = *ActorItr;
		}

		if (ActorItr->GetName().Equals("Table")) {
			table = *ActorItr;
		}
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

	// Should be hooked up to a menu. Menus have not yet been implemented.
	Run();
}

// I'm not super happy with the encapsulation here, but not 100% sure how the architecture is going to fall out of this one.
// Playing it by ear for now, excuse the lack of encapsulation.
void ABaseGameMode::Run() {
	if (!table) {
		UE_LOG(LogProck, Error, TEXT("Table doesnt exist, can't run"));
		return;
	}

	PyObject *pyRunner = peter->pyBindings->LoadRunner();
	if (!pyRunner) {
		UE_LOG(LogProck, Error, TEXT("Peter could not load native runner"));
		return;
	}

	// Can I really not create my own constructor? That can't be right, I must be doing something stupid.
	runtime = NewObject<URuntime>(URuntime::StaticClass());
	runtime->root = peter->prockRootNode;
	runtime->runner = pyRunner;
	runtime->table = table;

	// Set the value for the timer in Config
	runtime->StartTimed(RUNNING_STEP_TIME);
}
