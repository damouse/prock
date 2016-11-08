// Fill out your copyright notice in the Description page of Project Settings.

#include "ProckFPS.h"
#include "ProckNode.h"

// This is the real base implementation of ProckNode::Spawn
void Base_Spawn(UWorld *world, ProckNode *node, FVector pos) {
	node->box = world->SpawnActor<ABoxActor>(ABoxActor::StaticClass(), pos, FRotator::ZeroRotator);
	node->box->SetText(node->Name());
	node->box->SizeFitContents();
}


// Spawn the box for this node. The real implementation for this method is held as the function pointer spawnerCurryFunction
void Spawn(UWorld *world, ProckNode *node, FVector pos) {
	return Base_Spawn(world, node, pos);
}

void PNList_Spawn(PNList *node, UWorld *world, FVector pos) {

}