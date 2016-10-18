// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "UnrealEnginePython.h"
#include "BaseGameMode.generated.h"

UCLASS()
class PROCKFPS_API ABaseGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	ABaseGameMode();

	virtual void InitGameState();

	// Stored static classes that reference blueprints for runtime instantiation
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "X") TSubclassOf<AActor> boxBPClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "X") TSubclassOf<AActor> operatorBPClass;

	FUnrealEnginePythonModule python;
};
