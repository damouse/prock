#pragma once

#include "GameFramework/Actor.h"
#include "LinkableInterface.h"

#include <vector>

#include "BoxActor.generated.h"

// TODO: move to config.h
const int LABEL_MARGIN = 2;
const int BOX_DEPTH = 40;		// Depth when looking straight-on. Corresponds to y coordinate

class AScopeActor;
class APathSegment;

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

	// TODO: Remove all of these
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Label")
	UTextRenderComponent* mainLabel;
};

