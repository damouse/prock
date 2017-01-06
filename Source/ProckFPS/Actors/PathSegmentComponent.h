// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Components/SplineMeshComponent.h"

#include "GhostActor.h"

#include "PathSegmentComponent.generated.h"

class ABoxActor;

// One small part of a pathline. Carries ghosts and their lines between two boxes.

UCLASS()
class PROCKFPS_API APathSegment : public AActor
{
	GENERATED_BODY()

public:	
	// Convenience initializer that sets the rest of the fields on this class
	void InitializeSegment(ABoxActor *start, ABoxActor *end, bool connectToStartSource, bool connectToEndSource, TArray<AGhostActor*> ghosts);

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "NeedsRedraw"))
	void NeedsRedraw();

	//UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "AddGhosts"))
	//void AddGhosts(TArray<AGhostActor *> ghost);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Connections")
	ABoxActor *Start;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Connections")
	ABoxActor *End;

	// If true, connects to the "To" point for the Start box. If false, connects to the "From" point on start
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Connections")
	bool ConnectToStartSource;

	// If true, connects to the "To" point for the End box. If false, connects to the "From" point on End
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Connections")
	bool ConnectToEndSource;

	// Boxes we're connected to (for drawing updates)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Positioning")
	FVector StartPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Positioning")
	FVector StartTangent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Positioning")
	FVector StartRight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Positioning")
	FVector EndPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Positioning")
	FVector EndTangent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Positioning")
	FVector EndRight;

	// Private Blueprint Fields
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ghosts")
	TArray<AGhostActor *> Ghosts;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline Segments")
	TArray<USplineMeshComponent *> Splines;
};
