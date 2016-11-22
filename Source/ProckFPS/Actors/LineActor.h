/*
 An actor that connects two BoxActors with some kind of line.
*/

#pragma once

#include "GameFramework/Actor.h"
#include "Actors/BoxActor.h"
#include "LineActor.generated.h"

UCLASS()
class PROCKFPS_API ALineActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ALineActor();

	// Connect these guys with a line
	void Connect(ABoxActor *from, ABoxActor *to);
};
