/*
The one and only game mode. Does most of the heavy lifting on organization and state. 
*/
#pragma once

#include "GameFramework/GameMode.h"
#include "Peter.h"
#include "ParticleDefinitions.h"
#include "Room.h"
#include "BaseGameMode.generated.h"

UCLASS()
class PROCKFPS_API ABaseGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	ABaseGameMode();

	virtual void BeginPlay();

	TSubclassOf<ABoxActor> boxBPClass;

	// Likely temporary, but this is the RoomBP that draws all the stuffs. The reference to it
	// is picked up in BeginPlay
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Room")
	AActor *room;
private:
	Peter *peter;
};
