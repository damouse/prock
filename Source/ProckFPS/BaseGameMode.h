/*
The one and only game mode. Does most of the heavy lifting on organization and state. 
*/
#pragma once

#include "GameFramework/GameMode.h"
#include "Peter/Peter.h"
#include "ParticleDefinitions.h"
#include "BaseGameMode.generated.h"

UCLASS()
class PROCKFPS_API ABaseGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	ABaseGameMode();

	virtual void BeginPlay();

	TSubclassOf<ABoxActor> boxBPClass;

	// Likely temporary, but this is the RoomBP placed in the map before the procedural rendering starts
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Room")
	ABoxActor *room;

private:
	Peter *peter;
};
