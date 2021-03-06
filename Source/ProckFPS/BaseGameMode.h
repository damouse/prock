/*
The one and only game mode. Does most of the heavy lifting on organization and state. 
*/
#pragma once

#include "GameFramework/GameMode.h"
#include "Peter/Peter.h"
#include "Peter/Runtime.h"
#include "ParticleDefinitions.h"
#include "BaseGameMode.generated.h"

UCLASS()
class PROCKFPS_API ABaseGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	ABaseGameMode();

	virtual void BeginPlay();
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);

	// Likely temporary, but this is the RoomBP placed in the map before the procedural rendering starts
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Room")
	ABoxActor *room;

	// Workspace for displaying "scope" variables while Running
	ABoxActor *table;

	// Kick off a "running" phase
	void Run();

private:
	Peter *peter;
	URuntime *runtime;
};
