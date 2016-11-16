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
	for (TActorIterator<ARoom> ActorItr(GetWorld()); ActorItr; ++ActorItr) {
		UE_LOG(LogProck, Log, TEXT("Loaded room"));
		room = *ActorItr;
	}

	peter = new Peter();
	ProckNode *root = peter->LoadPython();

	if (root) {
		Spawn(GetWorld(), boxBPClass, root, FVector(-120, -60, 45));
	}

	//ABoxActor* box = GetWorld()->SpawnActor<ABoxActor>(boxBPClass, FVector(100, 100, 100), FRotator::ZeroRotator);
	//ABoxActor* boo = GetWorld()->SpawnActor<ABoxActor>(boxBPClass, FVector(300, 100, 100), FRotator::ZeroRotator);

	//box->SetText("Hello\0");
	//boo->SetText("Goodbye\0");
}