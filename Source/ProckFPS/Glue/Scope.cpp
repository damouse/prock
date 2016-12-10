// Fill out your copyright notice in the Description page of Project Settings.

#include "ProckFPS.h"
#include "Scope.h"
#include "Utils/Config.h"
#include "Actors/LinkableInterface.h"

using namespace std;

//// Check the blueprin
//bool AScopeActor::NewVariable(ProckNode *node) {
//	if (node->Type() != PNT_Name) {
//		return false;
//	}
//
//	PNName *n = (PNName *) node;
//
//	for (Ghost *g : ghosts) {
//		if (g->AddReference(n)) {
//			return true;
//		}
//	}
//
//	Ghost *g = new Ghost(n);
//	g->ghostActor = UConfig::world->SpawnActor<AGhostActor>(UConfig::ghostBPClass);
//	g->ghostActor->AttachToComponent(Root->box->GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);
//	g->ghostActor->SetActorRelativeLocation(FVector(0, spawnOffset, 0));
//	g->ghostActor->SetText(g->name);
//
//	spawnOffset += GHOST_OFFSET;
//	node->ghost = g;
//	ghosts.push_back(g);
//	
//	return true;
//}

// If the scope contains a ghost that matches this name return it
AGhostActor *AScopeActor::RefVar(PNName *name) {
	FString newName(name->Value());

	for (AGhostActor *g : Ghosts) {
		if (g->RefName.Equals(newName)) {
			// Make the ghost aware of which name nodes reference it 
			g->nodes.insert(name);
			return g;
		}
	}

	AGhostActor *g = UConfig::world->SpawnActor<AGhostActor>(UConfig::ghostBPClass);
	g->AttachToActor(this, FAttachmentTransformRules::SnapToTargetIncludingScale);
	g->SetActorRelativeLocation(FVector(0, spawnOffset, 0));
	g->SetText(name->Value());
	g->RefName = newName;
	g->nodes.insert(name);

	Ghosts.Add(g);
	return g;
}

void AScopeActor::Connect(ProckNode *from, ProckNode *to) {
	ALinkable *fromLink, *toLink;
	
	// Fetch the appropriate actor to link to: ghost or box
	if (from->box) {
		fromLink = from->box;
	} else if (from->ghost) {
		fromLink = from->ghost;
	} else {
		UE_LOG(LogProck, Error, TEXT("Scope asked to connect FROM a node that doesn't have a box or ghost"));
		return;
	}
	
	if (to->box) {
		toLink = to->box;
	} else if (to->ghost) {
		toLink = to->ghost;
	} else {
		UE_LOG(LogProck, Error, TEXT("Scope asked to connect TO a node that doesn't have a box or ghost"));
		to->PrintRaw();
		return;
	}

	ALineActor *line = UConfig::world->SpawnActor<ALineActor>(UConfig::lineBPClass);
	line->From = fromLink;
	line->To = toLink;
	line->Connect(fromLink, toLink);
}
