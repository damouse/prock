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

	root->Print();

	for (PythonNode *child : root->RootList()) {
		// Ignore comments and endlines, though we may want to display comments at some point
		if (child->Type() == PNT_Endl || child->Type() == PNT_Comment) {
			continue;
		}

		if (child->Type() == PNT_Assignment) {
			PythonNode *target = child->Target();
			PythonNode *value = child->Value();

			target->PrintRaw();
			value->PrintRaw();

			//if (target->Type() == PNT_Name) {
			//	PythonNode *nam = target->Value();
			//	nam->PrintRaw();
			//}

			//if (value->Type() == PNT_Int) {

			//}
		}

		//child->Print();
		//child->PrintRaw();
	}

	// Draw a handful of boxes just for show. Note that this kind of laying-out should not be handled here
	FVector currOffset = FVector(0.f, 0.f, 0.f);
	float offset = 500.f;

	for (int i = 0; i < 4; i++) {
		currOffset = FVector(i * offset, 0.f, 0.f);

		ABoxActor *box1 = GetWorld()->SpawnActor<ABoxActor>(ABoxActor::StaticClass(), FVector(0, 0, 0) + currOffset, FRotator::ZeroRotator);
		ABoxActor *box2 = GetWorld()->SpawnActor<ABoxActor>(ABoxActor::StaticClass(), FVector(0.f, 0.f, 200.f) + currOffset, FRotator::ZeroRotator);
		ABoxActor *op = GetWorld()->SpawnActor<ABoxActor>(ABoxActor::StaticClass(), FVector(200.f, 0.f, 100.f) + currOffset, FRotator::ZeroRotator);

		//box1->SetActorScale3D(FVector(2, 2, 2));
		box1->SetText("HELLO");

		// Connect the operation to the boxes
		op->ConnectToBox(box2);
		op->ConnectToBox(box1);
	}

	//// Spawn a nested box in the coordinate space of its parent (for nesting boxes)
	//ABoxTest *child = (ABoxTest *)GetWorld()->SpawnActor<AActor>(boxBPClass);
	//child->AttachToComponent(box->GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);
	//child->SetActorScale3D(FVector(0.5f, 0.5f, 0.5f));


	//prockRootNode->Resolve();
	//prockRootNode->Print();

	//for (ProckNode *node : prockRootNode->Children()) {
	//	PythonNode *pyNode = (PythonNode *)node;

	//	PythonNode *target = pyNode->GetTarget();
	//	if (target) {
	//		//target->Resolve();
	//		UE_LOG(LogProck, Log, TEXT("Target: %s"), UTF8_TO_TCHAR(target->GetType()));
	//	}

	//	//UE_LOG(LogProck, Log, TEXT("%s"), UTF8_TO_TCHAR(pyNode->GetType()));'
	//	//if (node->Type() != PNT_Endl)
	//	//	UE_LOG(LogProck, Error, TEXT("Type exists"));

	//	//if (node->Type() != PNT_Endl && node->Type() != PNT_Comment) {
	//	//	node->Print();
	//	//}
	//}
}

