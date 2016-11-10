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

	static ConstructorHelpers::FClassFinder<ABoxActor> boxBPFinder(TEXT("Blueprint'/Game/BoxActorBP'"));
	if (boxBPFinder.Class != NULL) {
		boxBPClass = boxBPFinder.Class;
	}
}

void ABaseGameMode::InitGameState() {
	peter = new Peter();
	ProckNode *root = peter->LoadPython();
	//Spawn(GetWorld(), root, FVector(0, 0, 150));

	ABoxActor* box = GetWorld()->SpawnActor<ABoxActor>(boxBPClass, FVector(200, 0, 0), FRotator::ZeroRotator);
	GetWorld()->SpawnActor<ABoxActor>(boxBPClass, FVector(200, 200, 0), FRotator::ZeroRotator);

	box->SetText("Hello\0");
}