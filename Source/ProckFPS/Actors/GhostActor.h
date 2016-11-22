/*
 An actor that connects two BoxActors with some kind of line.
*/

#pragma once

#include "GameFramework/Actor.h"
#include "Actors/BoxActor.h"
#include "GhostActor.generated.h"

UCLASS()
class PROCKFPS_API AGhostActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AGhostActor();

	// Connect these guys with a line
	// void Connect(ABoxActor *from, ABoxActor *to);
};
