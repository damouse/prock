// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "BoxTest.h"

#include "Operation.generated.h"


UCLASS()
class PROCKFPS_API AOperation : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOperation();

	// Calls from cpp to the blueprint
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "ConnectToBoxes"))
	void ConnectToBoxes(ABoxTest *start);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
};
