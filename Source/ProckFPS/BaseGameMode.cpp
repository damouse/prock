// Fill out your copyright notice in the Description page of Project Settings.

#include "ProckFPS.h"
#include "BaseGameMode.h"
#include "ProckNode.h"
#include "BoxActor.h"

ABaseGameMode::ABaseGameMode() {
	// I'm not entirely sure this is needed, but the blueprint this was taken from had physical manipulation already set up and running
	static ConstructorHelpers::FClassFinder<APlayerController> playerBPFinder(TEXT("Blueprint'/Game/BasePlayerController'"));
	if (playerBPFinder.Class != NULL) {
		PlayerControllerClass = playerBPFinder.Class;
	}

}
void ABaseGameMode::InitGameState() {
	peter = new Peter();
	ProckNode *root = peter->LoadPython();
	Spawn(GetWorld(), root, FVector(0, 0, 150));
}