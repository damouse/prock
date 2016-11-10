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

	// Connect another box using 0,0 as both source and target
	void ConnectToBox(ABoxActor* other);

	// Change the text displayed in this box
	void SetText(char *text);

	// Resize this box to fit its contents by calling SizeToContents on all children, or 
	// caluculating the dimensions of internal text
	FVector SizeFitContents();
	
	// The lines of this box
	std::vector<UParticleSystemComponent *> connections;

	// Stored in the constructor. Not needed if not building lines at runtime
	UParticleSystem *particleBeamActorComponent;

	//
	// References to components in the blueprint
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Label")
	UTextRenderComponent* mainLabel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cuber")
	UStaticMeshComponent *cube;

	//
	// Functions that call into blueprints
	// UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "SetMainLabelText"))
	// void SetMainLabelText(const FText& text);
};

