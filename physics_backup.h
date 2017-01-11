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
	virtual void Tick(float DeltaSeconds) override;

	TSubclassOf<ABoxActor> boxBPClass;

	// Likely temporary, but this is the RoomBP placed in the map before the procedural rendering starts
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Room")
	ABoxActor *room;

	// PHYSICS TESTING
	ABoxActor *a;
	ABoxActor *b;
	ABoxActor *c;

	float dt;

private:
	Peter *peter;
};

// PHYSICS TESTING

typedef struct {
	double m;   /* Mass                          */
	FVector p;      /* Position                      */
	FVector v;      /* Velocity                      */
	FVector f;      /* Force                         */
	bool fixed;  /* Fixed point or free to move   */
} PARTICLE;

typedef struct {
	FVector dpdt;
	FVector dvdt;
} PARTICLEDERIVATIVES;

typedef struct {
	double gravitational;
	double viscousdrag;
} PARTICLEPHYS;

typedef struct {
	int from;
	int to;
	double springconstant;
	double dampingconstant;
	double restlength;
} PARTICLESPRING;

void CalculateForces(PARTICLE *, int, PARTICLEPHYS, PARTICLESPRING *, int);
void UpdateParticles(PARTICLE *, int, PARTICLEPHYS, PARTICLESPRING *, int, double, int);
void CalculateDerivatives(PARTICLE *, int, PARTICLEDERIVATIVES *);
