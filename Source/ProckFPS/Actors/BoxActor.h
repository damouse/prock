#pragma once

#include "GameFramework/Actor.h"
#include "LinkableInterface.h"
//#include "Actors/LineActor.h"

#include <vector>

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

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "NeedsRedraw"))
	void NeedsRedraw();

	// Returns the socket location, in local coordinates, of a socket on the extent mesh with the given name
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "GetTentSocket"))
	void GetTentSocket(const FString& name, FVector &position);

	// Call to change the material of this box to an Active or Inactive state, wrt the runtime
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "SetRunstate"))
	void SetRunstate(bool isActive);

	// Changes the "value" label of the box with the passed value. Pass an empty string to clear.
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "SetRunValue"))
	void SetRunValue(const FString& value);

	// Turns on autotenting, which automatically expands the extents of this box to wrap its contents. 
	// Also hides the base box mesh. This is for nodes that primarily hold other nodes, like functions and objects
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "SetAutotenting"))
	void SetAutotenting(bool isAutotenting);

	// TODO: remove and replace with direct BP method
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Label")
	UTextRenderComponent* mainLabel;

	// Denotes a box that is primarily a wrapper for other, nested boxes. Don't set this 
	// field directly, call SetAutotenting.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IsAutotenting")
	bool IsAutotenting;


	// The lines that most directly belong to this node and that are "animated"
	// ERROR: suspect something is wrong with the import cycle here, can't get this to compile
	// during Runtime cycles
	//std::vector<ALineActor *> AttachedActiveLines;
};

