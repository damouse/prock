// Fill out your copyright notice in the Description page of Project Settings.

#include "ProckFPS.h"
#include "BoxTest.h"
#include "BaseGameMode.h"

ABaseGameMode::ABaseGameMode() {
	  static ConstructorHelpers::FClassFinder<AActor> doorBPClassFinder(TEXT("Blueprint'/Game/Box'"));

	  if (doorBPClassFinder.Class != nullptr) {
	  	boxBPClass = doorBPClassFinder.Class;
	  }
}

void ABaseGameMode::InitGameState() {
	  // Create the new actor at the given position, cast it to the appropriate class, and call a method on it for testing
	  FVector NewLocation = FVector(0.f, 0.f, 200.f);
	  ABoxTest *box = (ABoxTest *) GetWorld()->SpawnActor<AActor>(boxBPClass, NewLocation, FRotator::ZeroRotator);
	  box->SomethingHappened();
}