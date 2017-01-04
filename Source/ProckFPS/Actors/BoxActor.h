// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include <vector>
#include "LinkableInterface.h"

#include "BoxActor.generated.h"

// TODO: move to config.h
const int LABEL_MARGIN = 2;
const int BOX_DEPTH = 40;		// Depth when looking straight-on. Corresponds to y coordinate

class AScopeActor;

UCLASS()
class PROCKFPS_API ABoxActor : public ALinkable
{
	GENERATED_BODY()
public:
	void SetText(char *text);

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "ResizeToFitText"))
	void SizeFitContents();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Label")
	UTextRenderComponent* mainLabel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cuber")
	UStaticMeshComponent *cube;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cuber")
	AScopeActor *scope;
	
	//
	// Experimental-- lets take a quick detour and see if cpp is any clearer than blueprints
	// It maybe, but at this point it requires backtracking on a lot of existing work in blueprints
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Pathline", meta = (DisplayName = "GetPathInOut"))
	void GetPathInOut(FVector &startPos, FVector &startTan, FVector &endPos, FVector &endTan);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Pathline", meta = (DisplayName = "CreateSplineMeshComponent"))
	USplineMeshComponent* CreateSplineMeshComponent();

	virtual void BeginPlay();
};

