// Fill out your copyright notice in the Description page of Project Settings.

#include "ProckFPS.h"
#include "ProckNode.h"

//void PNList::Spawn(UWorld *world, FVector pos) {
//	UE_LOG(LogProck, Log, TEXT("Subclass method called"));
//	Super::Spawn(world, pos);
//}

// Spawn the box for this node. The real implementation for this method is held as the function pointer spawnerCurryFunction
void ProckNode::Spawn(UWorld *world, FVector pos) {
	return defaultSpawn(world, pos);
}

void PNList_Spawn(PNList *node, UWorld *world, FVector pos) {

}

void InitializeOverrides() {
	//SPAWN_OVERRIDES[PNT_List] = &PNList_Spawn;

	//SPAWN_OVERRIDES = {
	//	std::pair<ProckNodeType, std::function<void(ProckNode *, UWorld *, FVector)>>(PNT_Base, &ProckNode::defaultSpawn),
	//	std::pair<ProckNodeType, std::function<void(ProckNode *, UWorld *, FVector)>>(PNT_List, &PNList_Spawn),
	//};
}