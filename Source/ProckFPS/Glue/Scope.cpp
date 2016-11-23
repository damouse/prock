// Fill out your copyright notice in the Description page of Project Settings.

#include "ProckFPS.h"
#include "Scope.h"
#include "Utils/Config.h"


using namespace std;

bool Scope::NewVariable(ProckNode *node) {
	if (node->Type() != PNT_Name) {
		return false;
	}

	PNName *n = (PNName *) node;

	for (Ghost *g : ghosts) {
		if (g->AddReference(n)) {
			return true;
		}
	}

	ghosts.push_back(new Ghost(n));
	return true;
}

void Scope::Spawn(ProckNode *n) {
	float offset = -3.f;
	float currOffset = 2.f;

	for (Ghost * g : ghosts) {
		g->ghostActor = UConfig::world->SpawnActor<AGhostActor>(UConfig::ghostBPClass);
		g->ghostActor->AttachToComponent(n->box->GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);
		g->ghostActor->SetActorRelativeLocation(FVector(0, currOffset, -6));
		g->ghostActor->SetText(g->name);
		currOffset = currOffset + offset;
	}
}