// Fill out your copyright notice in the Description page of Project Settings.

#include "ProckFPS.h"
#include "Config.h"

#include "Actors/BoxActor.h"
#include "Actors/LineActor.h"

TSubclassOf<ABoxActor> UConfig::boxBPClass = nullptr;
TSubclassOf<ALineActor> UConfig::lineBPClass = nullptr;

UWorld *UConfig::world = nullptr;

UConfig::UConfig() {
	static ConstructorHelpers::FClassFinder<ABoxActor> boxBPFinder(TEXT("Blueprint'/Game/Blueprints/BoxActorBP'"));
	if (boxBPFinder.Class != NULL) {
		UConfig::boxBPClass = boxBPFinder.Class;
	}

	static ConstructorHelpers::FClassFinder<ALineActor> lineBPFinder(TEXT("Blueprint'/Game/Blueprints/LineActorBP'"));
	if (lineBPFinder.Class != NULL) {
		UConfig::lineBPClass = lineBPFinder.Class;
	}
}