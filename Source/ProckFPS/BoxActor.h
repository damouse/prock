// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
 #include <vector>
#include "BoxActor.generated.h"


UCLASS()
class PROCKFPS_API ABoxActor : public AActor
{
	GENERATED_BODY()
public:
	ABoxActor();

	virtual void BeginPlay() override;

	void AddEdge(FVector start, FVector end, int index);

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "X")
	 std::vector<UParticleSystemComponent *> beams;

	//void AddEdge(FVector start, FVector end);
	 UParticleSystem *beam;
};
