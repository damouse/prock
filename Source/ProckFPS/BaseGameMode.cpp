// Fill out your copyright notice in the Description page of Project Settings.

#include "ProckFPS.h"
#include "BoxTest.h"
#include "Operation.h"
#include "BaseGameMode.h"
#include "BoxActor.h"

ABaseGameMode::ABaseGameMode() {
	  static ConstructorHelpers::FClassFinder<AActor> doorBPClassFinder(TEXT("Blueprint'/Game/Box'"));
	  static ConstructorHelpers::FClassFinder<AActor> operatorBPFinder(TEXT("Blueprint'/Game/Operator'"));


	  if (doorBPClassFinder.Class != nullptr) {
	  	boxBPClass = doorBPClassFinder.Class;
	  }

	  if (operatorBPFinder.Class != nullptr) {
		  operatorBPClass = operatorBPFinder.Class;
	  }
}

void ABaseGameMode::InitGameState() {
	// Load the processing module, ask it to load python, and return. 
	//peter = new Peter();
	//peter->LoadPython();
	//peter->LoadRoom();

	//peter->UnloadPython();
	//delete peter;
	
	ABoxActor *truebox = GetWorld()->SpawnActor<ABoxActor>(ABoxActor::StaticClass(), FVector(0.f, 0.f, 200.f), FRotator::ZeroRotator);

	// Translation offset between blocks
	//FVector currOffset = FVector(0.f, 0.f, 0.f);
	//float offset = 500.f;

	//for (int i = 0; i < 4; i++) {
	//	currOffset = FVector(i * offset, 0.f, 0.f);
	//	
	//	ABoxTest *box1 = (ABoxTest *)GetWorld()->SpawnActor<AActor>(boxBPClass, FVector(0.f, 0.f, 200.f) + currOffset, FRotator::ZeroRotator);
	//	ABoxTest *box2 = (ABoxTest *)GetWorld()->SpawnActor<AActor>(boxBPClass, FVector(0.f, 0.f, 400.f) + currOffset, FRotator::ZeroRotator);
	//	AOperation *op = (AOperation *)GetWorld()->SpawnActor<AActor>(operatorBPClass, FVector(-200.f, 0.f, 300.f) + currOffset, FRotator::ZeroRotator);

	//	// Connect the operation to the boxes
	//	op->ConnectToBoxes(box2);
	//	op->ConnectToBoxes(box1);
	//}

	//// Spawn a nested box in the coordinate space of its parent
	//ABoxTest *child = (ABoxTest *)GetWorld()->SpawnActor<AActor>(boxBPClass);
	//child->AttachToComponent(box->GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);
	//child->SetActorScale3D(FVector(0.5f, 0.5f, 0.5f));
}
