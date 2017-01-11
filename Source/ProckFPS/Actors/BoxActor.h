#pragma once

#include "GameFramework/Actor.h"
#include "LinkableInterface.h"

#include <vector>

#include "BoxActor.generated.h"

// TODO: move to config.h
const int LABEL_MARGIN = 2;
const int BOX_DEPTH = 40;		// Depth when looking straight-on. Corresponds to y coordinate

class ALineActor;

UCLASS()
class PROCKFPS_API ABoxActor : public ALinkable
{
	GENERATED_BODY()
public:
	virtual void BeginPlay();
	virtual void Tick(float DeltaSeconds) override;

	void SetText(char *text);

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "ResizeToFitText"))
	void SizeFitContents();

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "NeedsRedraw"))
	void NeedsRedraw();

	// TODO: remove and replace with direct BP method
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Label")
	UTextRenderComponent* mainLabel;

//protected:
	// Physics designed off work from Mr. Paul Bourke
	// http://paulbourke.net/miscellaneous/particle/

	void UpdateForces(TArray<ABoxActor*> boxes, TArray<ALineActor*> lines);
	void UpdatePositions(TArray<ABoxActor*> boxes, TArray<ALineActor*> lines);

	bool fixed = false;
	float dt;
	float m; // Mass

	FVector p; // Position, as recoreded and updated by our physics system
	FVector v; // Velocity
	FVector f; // Force
};

