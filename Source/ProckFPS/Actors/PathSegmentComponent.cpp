// Fill out your copyright notice in the Description page of Project Settings.

#include "ProckFPS.h"
#include "PathSegmentComponent.h"

void APathSegment::InitializeSegment(ABoxActor *start, ABoxActor *end, bool connectToStartSource, bool connectToEndSource, TArray<AGhostActor*> ghosts) {
	Start = start;
	End = end;
	ConnectToStartSource = connectToStartSource;
	ConnectToEndSource = connectToEndSource;
	Ghosts = ghosts;
}