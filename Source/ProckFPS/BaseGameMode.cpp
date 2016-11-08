// Fill out your copyright notice in the Description page of Project Settings.

#include "ProckFPS.h"
#include "BaseGameMode.h"
#include "ProckNode.h"
#include "BoxActor.h"

ABaseGameMode::ABaseGameMode() {
	  // I'm not entirely sure this is needed, but the blueprint this was taken from had physical manipulation already
	  static ConstructorHelpers::FClassFinder<APlayerController> playerBPFinder(TEXT("Blueprint'/Game/BasePlayerController'"));
	  if (playerBPFinder.Class != NULL) {
		  PlayerControllerClass = playerBPFinder.Class;
	  }
}

void ABaseGameMode::InitGameState() {
	// Load the bindings and import the code
	peter = new Peter();
	ProckNode *root = peter->LoadPython();
	Spawn(GetWorld(), root, FVector(0, 0, 150));
}

//// Spawn a nested box in the coordinate space of its parent (for nesting boxes)
//ABoxTest *child = (ABoxTest *)GetWorld()->SpawnActor<AActor>(boxBPClass);
//child->AttachToComponent(box->GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);
//child->SetActorScale3D(FVector(0.5f, 0.5f, 0.5f));