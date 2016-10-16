#include "ProckFPS.h"
#include "Operation.h"

AOperation::AOperation() {
	//PrimaryActorTick.bCanEverTick = true;
}

void AOperation::BeginPlay() {
	Super::BeginPlay();
	
}

void AOperation::Tick( float DeltaTime ) {
	Super::Tick( DeltaTime );
}

