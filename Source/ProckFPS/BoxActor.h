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
	virtual void Tick(float DeltaSeconds) override;

	void AddEdge(FVector start, FVector end);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RootComponentSphere")
	UBoxComponent* root;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Beams")
	std::vector<UParticleSystemComponent *> beams;

	UParticleSystem *particleBeamComponent;

	float RunningTime;
};