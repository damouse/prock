// Fill out your copyright notice in the Description page of Project Settings.

#include "ProckFPS.h"
#include "Actors/GhostActor.h"

void AGhostActor::SetText(char *text) {
	if (boxInstance) {
		boxInstance->SetText(text);
	}
}
