// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Components/SplineMeshComponent.h"
#include <vector>
#include "BoxActor.generated.h"

const int LABEL_MARGIN = 5;
const int BOX_DEPTH = 40;		// Depth when looking straight-on. Corresponds to y coordinate

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
	void AddEdge(FVector start, FVector end);

	// Change the text displayed in this box. TODO: 
	void SetText(char *text);

	// Resize this box to fit its contents by calling SizeToContents on all children, or 
	// caluculating the dimensions of internal text. Returns the resized bounds
	FVector SizeFitContents();
	
	// The lines of this box
	std::vector<UParticleSystemComponent *> beams;
	std::vector<USplineMeshComponent *> splines;
	std::vector<UParticleSystemComponent *> connections;

	// Stored in the constructor. Not needed if not building lines at runtime
	UParticleSystem *particleBeamComponent;
	UParticleSystem *particleBeamActorComponent; // Same beam with connection settings set to actors instead of points
	UStaticMesh *splineStaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cuber")
	UTextRenderComponent* mainLabel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cuber")
	UStaticMeshComponent *cube;

	// Used to animate the box up and down for testing
	float RunningTime;


	// Calls from the blueprint to cpp
	//UFUNCTION(BlueprintCallable, Category = "Callbacks")
	//	void CursorOver();

	// Calls from cpp to the blueprint
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Happened"))
		void SomethingHappened();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control")
		bool SpawnOnce;
};
