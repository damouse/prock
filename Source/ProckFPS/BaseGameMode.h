/*
The one and only game mode. Does most of the heavy lifting on organization and state. 
*/
#pragma once

#include "GameFramework/GameMode.h"
#include "Peter.h"
#include "ParticleDefinitions.h"
#include "BaseGameMode.generated.h"



UCLASS()
class PROCKFPS_API ABaseGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	ABaseGameMode();

	virtual void InitGameState();

	// Stored static classes that reference blueprints for runtime instantiation
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "X")
	TSubclassOf<AActor> boxBPClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "X")
	TSubclassOf<AActor> operatorBPClass;

private:
	Peter *peter;
};
