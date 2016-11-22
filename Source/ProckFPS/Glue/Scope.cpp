// Fill out your copyright notice in the Description page of Project Settings.

#include "ProckFPS.h"
#include "Scope.h"

using namespace std;

void Scope::NewVariable(ProckNode *node) {
	if (node->Type() != PNT_Name) {
		return;
	}

	PNName *n = (PNName *) node;

	for (Ghost *g : ghosts) {
		if (g->AddReference(n)) {
			return;
		}
	}

	ghosts.insert(new Ghost(n));
}

void Scope::Spawn(ProckNode *n) {

}