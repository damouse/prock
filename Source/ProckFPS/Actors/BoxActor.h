// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Components/SplineMeshComponent.h"
#include <vector>
#include "BoxActor.generated.h"

const int LABEL_MARGIN = 2;
const int BOX_DEPTH = 40;		// Depth when looking straight-on. Corresponds to y coordinate

UCLASS()
class PROCKFPS_API ABoxActor : public AActor
{
	GENERATED_BODY()
public:
	ABoxActor();

	// Connect another box using 0,0 as both source and target
	//void ConnectToBox(ABoxActor* other);

	// Change the text displayed in this box
	void SetText(char *text);

	// The lines of this box
	std::vector<UParticleSystemComponent *> connections;

	
	// References to components in the blueprint
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Label")
	UTextRenderComponent* mainLabel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cuber")
	UStaticMeshComponent *cube;


	// Resize the box to fit its current text
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "ResizeToFitText"))
	void SizeFitContents();

private:
	// Stored in the constructor. Not needed if not building lines at runtime
	UParticleSystem *particleBeamActorComponent;
};

