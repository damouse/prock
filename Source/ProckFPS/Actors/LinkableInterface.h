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
};
