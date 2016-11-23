/*
 Base class whose purpose is to act like an interface (since I can't get unreal's system to work.)

 Classes that inherit from Linkable can be connected by LineActors. Minimally this is BoxActors and 
 GhostActors
*/

#pragma once

#include "GameFramework/Actor.h"
#include "LinkableInterface.generated.h"

// Interface  base class
UCLASS()
class PROCKFPS_API ALinkable : public AActor {
	GENERATED_BODY()
public:
	// Get attach positions in worldspace given the object in the other position
	// These functions are implemented in the Blueprint subclasses for Box and Ghost
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Attachment")
	FVector GetToPos(ALinkable *from);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Attachment")
	FVector GetFromPos(ALinkable *to);
};
