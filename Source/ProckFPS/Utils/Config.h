/*
 Holds global static configuration and asset references. Specifically, this class stores:
	- Static Refs to blueprints, the world
	- Coordinate/Spawning offsets
	- Project-wide settings
*/

#pragma once
#include "Object.h"
#include "Config.generated.h"

class ABoxActor;
class AGhostActor;
class ALineActor;

UCLASS()
class PROCKFPS_API UConfig : public UObject
{
    GENERATED_BODY()
public:
	UConfig();

	// World
	static UWorld *world;

	// Blueprints
	static TSubclassOf<ABoxActor> boxBPClass;
	static TSubclassOf<AGhostActor> ghostBPClass;
	static TSubclassOf<ALineActor> lineBPClass;

};
