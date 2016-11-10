/*
 An actor that connects two BoxActors with some kind of line.
*/

#pragma once

#include "GameFramework/Actor.h"
#include "BoxActor.h"
#include "LineActor.generated.h"

UCLASS()
class PROCKFPS_API ALineActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALineActor();

	void Connect();
};
