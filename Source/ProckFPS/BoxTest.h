// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "BoxTest.generated.h"

UCLASS()
class PROCKFPS_API ABoxTest : public AActor
{
	GENERATED_BODY()
	
public:	
	ABoxTest();

	virtual void BeginPlay() override;
	
	// Calls from the blueprint to cpp
	UFUNCTION(BlueprintCallable, Category = "Callbacks")
	void CursorOver();

	// Calls from cpp to the blueprint
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Happened"))
	void SomethingHappened();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control")
	bool SpawnOnce;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "X")
	//UParticleSystemComponent *beam;
};
