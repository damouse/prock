/*
 An actor that connects two BoxActors with some kind of line.
*/

#pragma once

#include "Actors/LinkableInterface.h"
#include "Actors/BoxActor.h"
#include "Utils/Config.h"
#include "GhostActor.generated.h"

UCLASS()
class PROCKFPS_API AGhostActor : public ALinkable
{
	GENERATED_BODY()
public:	
	// Sets the label for the floating instance of this ghost
	void SetText(char *name);

	// The sliding box that represents an instance of this ghost
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BoxInstance")
	ABoxActor *boxInstance;
};
