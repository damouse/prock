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
		room = *ActorItr;
	}

	peter = new Peter();
	ProckNode *root = peter->LoadPython();

	// Note that the root prock node should handle this directly, these two sections are just for demonstration
	//root->box = GetWorld()->SpawnActor<ABoxActor>(boxBPClass, FVector(600, 100, 100), FRotator::ZeroRotator);
	//root->box->SetText("A");
	//root->box->SizeFitContents();

	//root->box->AttachToComponent(room->GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);
	//root->box->SetActorScale3D(FVector(0.2f, 0.2f, 0.2f));

	if (root) {
		Spawn(GetWorld(), boxBPClass, root, room, FVector(0, 0, 0));
	}
}