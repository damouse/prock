// Fill out your copyright notice in the Description page of Project Settings.

#include "ProckFPS.h"
#include "BaseGameMode.h"
#include "ProckNode.h"
#include "BoxActor.h"

ABaseGameMode::ABaseGameMode() {
	UE_LOG(LogProck, Error, TEXT("Fuck you UE4"));

	// I'm not entirely sure this is needed, but the blueprint this was taken from had physical manipulation already set up and running
	static ConstructorHelpers::FClassFinder<APlayerController> playerBPFinder(TEXT("Blueprint'/Game/Blueprints/BasePlayerController'"));
	if (playerBPFinder.Class != NULL) {
		PlayerControllerClass = playerBPFinder.Class;
	}

	static ConstructorHelpers::FClassFinder<ABoxActor> boxBPFinder(TEXT("Blueprint'/Game/Blueprints/BoxActorBP'"));
	if (boxBPFinder.Class != NULL) {
		boxBPClass = boxBPFinder.Class;
	}
}

void ABaseGameMode::InitGameState() {
	peter = new Peter();
	ProckNode *root = peter->LoadPython();

	if (root) {
		Spawn(GetWorld(), boxBPClass, root, FVector(0, 0, 50));
	}

	//ABoxActor* box = GetWorld()->SpawnActor<ABoxActor>(boxBPClass, FVector(100, 100, 100), FRotator::ZeroRotator);
	//ABoxActor* boo = GetWorld()->SpawnActor<ABoxActor>(boxBPClass, FVector(300, 100, 100), FRotator::ZeroRotator);

	//box->SetText("Hello\0");
	//boo->SetText("Goodbye\0");
}