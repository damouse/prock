/*
 An actor that connects two BoxActors with some kind of line.
*/

#pragma once

#include "Actors/LinkableInterface.h"
#include "Actors/BoxActor.h"
#include "Utils/Config.h"

#include <set>

#include "GhostActor.generated.h"

class PNName;

UCLASS()
class PROCKFPS_API AGhostActor : public ALinkable
{
	GENERATED_BODY()
public:	
	// The sliding box that represents an instance of this ghost
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BoxInstance")
	ABoxActor *boxInstance;

	// The name of this ghost
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RefName")
	FString RefName;

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "SetMainLabel"))
	void SetMainText(const FString& name);

	// This is so the ghost knows which name nodes reference it. 
	// The BP needs the boxes, too
	std::set<PNName *> nodes;
};
