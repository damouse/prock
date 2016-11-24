// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include <vector>
#include "LinkableInterface.h"
#include "BoxActor.generated.h"

// TODO: move to config.h
const int LABEL_MARGIN = 2;
const int BOX_DEPTH = 40;		// Depth when looking straight-on. Corresponds to y coordinate

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

	//UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Attachment")
	//void NestBox(ALinkable *to, FVector &pos, FVector &tan);
};

