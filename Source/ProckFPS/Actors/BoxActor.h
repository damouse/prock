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
	void SetText(char *text);

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "ResizeToFitText"))
	void SizeFitContents();

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "NeedsRedraw"))
	void NeedsRedraw();

	// Call to change the material of this box to an Active or Inactive state, wrt the runtime
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "SetRunstate"))
	void SetRunstate(bool isActive);

	// Changes the "value" label of the box with the passed value. Pass an empty string to clear.
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "SetRunValue"))
	void SetRunValue(const FString& value);

	// TODO: remove and replace with direct BP method
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Label")
	UTextRenderComponent* mainLabel;
};

