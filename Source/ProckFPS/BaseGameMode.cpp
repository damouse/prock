// Fill out your copyright notice in the Description page of Project Settings.

#include "ProckFPS.h"
#include "BoxTest.h"
#include "Operation.h"
#include "BaseGameMode.h"


ABaseGameMode::ABaseGameMode() {
	  static ConstructorHelpers::FClassFinder<AActor> doorBPClassFinder(TEXT("Blueprint'/Game/Box'"));
	  static ConstructorHelpers::FClassFinder<AActor> operatorBPFinder(TEXT("Blueprint'/Game/Operator'"));

	  if (doorBPClassFinder.Class != nullptr) {
	  	boxBPClass = doorBPClassFinder.Class;
	  }

	  if (operatorBPFinder.Class != nullptr) {
		  operatorBPClass = operatorBPFinder.Class;
	  }

	  peter = new Peter();
	  peter->LoadPython();
}

void ABaseGameMode::InitGameState() {
	// Translation offset between blocks
	FVector currentOffset = FVector(0.f, 0.f, 0.f);
	float offset = 500.f;

	for (int i = 0; i < 4; i++) {
		FVector currentOffset = FVector(i * offset, 0.f, 0.f);
		
		ABoxTest *box1 = (ABoxTest *)GetWorld()->SpawnActor<AActor>(boxBPClass, FVector(0.f, 0.f, 200.f) + currentOffset, FRotator::ZeroRotator);
		ABoxTest *box2 = (ABoxTest *)GetWorld()->SpawnActor<AActor>(boxBPClass, FVector(0.f, 0.f, 400.f) + currentOffset, FRotator::ZeroRotator);
		AOperation *op = (AOperation *)GetWorld()->SpawnActor<AActor>(operatorBPClass, FVector(-200.f, 0.f, 300.f) + currentOffset, FRotator::ZeroRotator);

		// Connect the operation to the boxes
		op->ConnectToBoxes(box2);
		op->ConnectToBoxes(box1);
	}

	//// Spawn a nested box in the coordinate space of its parent
	//ABoxTest *child = (ABoxTest *)GetWorld()->SpawnActor<AActor>(boxBPClass);
	//child->AttachToComponent(box->GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);
	//child->SetActorScale3D(FVector(0.5f, 0.5f, 0.5f));
}
