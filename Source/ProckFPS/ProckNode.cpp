// Fill out your copyright notice in the Description page of Project Settings.

#include "ProckFPS.h"
#include "ProckNode.h"

//
// Leaf Nodes
//
void Base_Spawn(UWorld *world, TSubclassOf<ABoxActor> klass, ProckNode *node, FVector pos) {
	node->box = world->SpawnActor<ABoxActor>(klass, pos, FRotator::ZeroRotator);
	node->box->SetText(node->Name());
	node->box->SizeFitContents();
}

void Name_Spawn(UWorld *world, TSubclassOf<ABoxActor> klass, PNName *node, FVector pos) {
	Base_Spawn(world, klass, node, pos);
	node->box->SetText(node->Value());
}

void Int_Spawn(UWorld *world, TSubclassOf<ABoxActor> klass, PNInt *node, FVector pos) {
	Base_Spawn(world, klass, node, pos);
	node->box->SetText(node->Value());
}

// 
// "Basic" Operators
// 
void Assignment_Spawn(UWorld *world, TSubclassOf<ABoxActor> klass, PNAssignment *node, FVector pos) {
	ProckNode *target = node->Target();
	ProckNode *value = node->Value();

	Spawn(world, klass, value, pos);
	Spawn(world, klass, target, pos + FVector(300, 0, 0));

	value->box->ConnectToBox(target->box);
}

void BinaryOperator_Spawn(UWorld *world, TSubclassOf<ABoxActor> klass, PNBinaryOperator *node, FVector pos) {
	node->box = world->SpawnActor<ABoxActor>(klass, pos + FVector(200, 0, 0), FRotator::ZeroRotator);
	node->box->SetText(node->Value());
	node->box->SizeFitContents();

	ProckNode *first = node->First();
	ProckNode *second = node->Second();

	Spawn(world, klass, first, pos + FVector(0, 0, 75));
	Spawn(world, klass, second, pos + FVector(0, 0, -25));

	node->box->ConnectToBox(first->box);
	node->box->ConnectToBox(second->box);
}

//
// Collections of Nodes
//
void List_Spawn(UWorld *world, TSubclassOf<ABoxActor> klass, PNList *node, FVector pos) {
	// Very naive spacing implementation
	float offset = 600.f;
	float currOffset = 0.f;

	for (ProckNode *child : *node->NodeList()) {
		// Skip comments and endlines for now. Comments could be useful in the future
		if (child->Type() == PNT_Comment || child->Type() == PNT_Endl) {
			continue;
		}

		Spawn(world, klass, child, FVector(currOffset, 0, 50));
		currOffset = currOffset + offset;
	};
}

// This function switches on the type of the passed node and invokes a respective _Spawn function if one exists, 
// else calls Base_Spawn. Each type check here is basically the implementation of another node "drawing" type.
// When creating new _Spawn methods, please give them the same name as the node being targeted
//
// Note that this design intentionally allows for a single _Spawn method to handle multiple node types.
void Spawn(UWorld *world, TSubclassOf<ABoxActor> klass, ProckNode *node, FVector pos) {
	switch (node->Type()) {

	// Leaf Nodes
	case PNT_Name:				return Name_Spawn(world, klass, (PNName *)node, pos);
	case PNT_Int:				return Int_Spawn(world, klass, (PNInt *)node, pos);

	// Basic Operators
	case PNT_Assignment:		return Assignment_Spawn(world, klass, (PNAssignment *)node, pos);
	case PNT_BinaryOperator:	return BinaryOperator_Spawn(world, klass, (PNBinaryOperator *)node, pos);

	// Collections
	case PNT_List:				return List_Spawn(world, klass, (PNList *)node, pos);

	// Fallback to just drawing the box
	default:					return Base_Spawn(world, klass, node, pos);
	}
}
