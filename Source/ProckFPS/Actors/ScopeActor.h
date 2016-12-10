// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Actors/LineActor.h"
#include "Actors/GhostActor.h"
#include "Nodes/ProckNodeSubclasses.h"

#include <vector>
#include <set>
#include "ScopeActor.generated.h"

/**
 * Collection of references visible within a certain scope, usually attached to a Node.
 * Belongs to some node; all nodes contained within the scope hold a reference to it. 
 *
 * Think of this class as a representation of the nested content within a node and not the node itself.
 */
UCLASS()
class PROCKFPS_API AScopeActor : public AActor {
	GENERATED_BODY()
public:
	// Connect the two logical nodes with a line with ALineActor
	// The real connection (ALineActor) could either be between two boxes or a box and a ghost
	// This isn't part of the programming scope, its part of the scope of things drawn within a box
	void Connect(ProckNode *from, ProckNode *to);

	AGhostActor *RefVar(PNName *name);

	// Name a variable in scope. This function returns a contact point for that 
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "GetGhostConnectionPoint")
	void ReferenceVar(FVector requestorLocation, bool isAssignment, FVector &pos);

	// Add the next box in the line, if this node represents a list
	// This room should append the box to an array and draw scope between the two 
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "SetNextLine"))
	void SetNextLine(ABoxActor *next);

	// Add the next box in the line, if this node represents a list
	// This room should append the box to an array and draw scope between the two 
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "RedrawGhosts"))
	void RedrawGhosts();

	// The name of this ghost
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ghosts")
	TArray<AGhostActor *> Ghosts;

//private: 
	std::set<ALineActor *> lines;

	// The root prock node this scope is bound to
	ProckNode *Root;
};
