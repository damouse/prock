#pragma once
#include "GameFramework/Actor.h"
#include "LinkableInterface.h"

#include <vector>

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

};

