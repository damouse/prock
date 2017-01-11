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
class ALineActor;

// Spawning Ofsets
const float GHOST_OFFSET = -3.f;

const float BOX_X_OFFSET = 10;
const float BOX_Z_OFFSET = 10;

const float FRAME_X_OFFSET = 10;
const float FRAME_Z_OFFSET = 5;

// Box Physics Parameters
const float GRAVITY = 0;
const float VISCOUS_DRAG = 0.1;

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
	static TSubclassOf<ALineActor> lineBPClass;
};
