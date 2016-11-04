// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Components/SplineMeshComponent.h"
#include <vector>
#include "BoxActor.generated.h"


UCLASS()
class PROCKFPS_API ABoxActor : public AActor
{
	GENERATED_BODY()
public:
	ABoxActor();

	// Base overrides
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	// Connect another box using 0,0 as both source and target
	void ConnectToBox(ABoxActor* other);

	// Add a new line to this box
	//void AddEdge(FVector start, FVector end);

	// Change the text displayed in this box. TODO: 
	void SetText(char *text);
	
	// The lines of this box
	//std::vector<UParticleSystemComponent *> beams;
	//std::vector<USplineMeshComponent *> splines;
	std::vector<UParticleSystemComponent *> connections;

	// Stored in the constructor. Not needed if not building lines at runtime
	//UParticleSystem *particleBeamComponent;
	//UParticleSystem *particleBeamActorComponent; // Same beam with connection settings set to actors instead of points
	//UStaticMesh *splineStaticMesh;
	UTextRenderComponent* mainLabel;
};
