// Fill out your copyright notice in the Description page of Project Settings.

#include "ProckFPS.h"
#include "BaseGameMode.h"
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
	PythonNode *root = peter->LoadPython();

	// Draw a handful of boxes. Note that this kind of laying-out should not be handled here
	FVector currOffset = FVector(0.f, 0.f, 0.f);
	float offset = 500.f;

	for (int i = 0; i < 4; i++) {
		currOffset = FVector(i * offset, 0.f, 0.f);

		ABoxActor *box1 = GetWorld()->SpawnActor<ABoxActor>(ABoxActor::StaticClass(), FVector(0.f, 0.f, 0.f) + currOffset, FRotator::ZeroRotator);
		ABoxActor *box2 = GetWorld()->SpawnActor<ABoxActor>(ABoxActor::StaticClass(), FVector(0.f, 0.f, 200.f) + currOffset, FRotator::ZeroRotator);
		ABoxActor *op = GetWorld()->SpawnActor<ABoxActor>(ABoxActor::StaticClass(), FVector(200.f, 0.f, 100.f) + currOffset, FRotator::ZeroRotator);

		// Connect the operation to the boxes
		op->ConnectToBox(box2);
		op->ConnectToBox(box1);
	}

	//// Spawn a nested box in the coordinate space of its parent (for nesting boxes)
	//ABoxTest *child = (ABoxTest *)GetWorld()->SpawnActor<AActor>(boxBPClass);
	//child->AttachToComponent(box->GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);
	//child->SetActorScale3D(FVector(0.5f, 0.5f, 0.5f));
}
