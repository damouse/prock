/*
 An actor that connects two BoxActors with some kind of line.

 See here for documentation on the iface: https://wiki.unrealengine.com/Interfaces_in_C%2B%2B
*/

#pragma once

#include "GameFramework/Actor.h"
#include "Actors/BoxActor.h"
#include "Actors/LinkableInterface.h"
#include "LineActor.generated.h"

// Line actor
UCLASS()
class PROCKFPS_API ALineActor : public AActor
{
	GENERATED_BODY()
public:	
	//UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Connect"))
	//void Connect(ALinkable *from, ALinkable *to);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "From")
	ABoxActor *From;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "To")
	ABoxActor *To;

	// Call to change the material of this box to an Active or Inactive state, wrt the runtime
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "SetRunstate"))
	void SetRunstate(bool isActive);
};
