/*
 Holds global static configuration and asset references. Specifically, this file stores:
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


// Spawning Ofsets
const float GHOST_OFFSET = -3.f;

const float BOX_X_OFFSET = 50;
const float BOX_Z_OFFSET = 20;

const float FRAME_X_OFFSET = 5;
const float FRAME_Z_OFFSET = 5;

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
