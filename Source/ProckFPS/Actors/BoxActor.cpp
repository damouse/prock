// Fill out your copyright notice in the Description page of Project Settings.

#include "ProckFPS.h"
#include "Actors/BoxActor.h"
#include "Utils/Config.h"
#include <stdio.h>
#include <math.h> 

#include "Actors/ScopeActor.h"

#include "Components/SplineMeshComponent.h"

using namespace std;

void ABoxActor::BeginPlay() {
	// Get the pathline points from blueprint
	FVector startPos, startTan, endPos, endTan; 
	GetPathInOut(startPos, startTan, endPos, endTan);
	
	// Spline right vectors-- automagical for now
	FVector startRight(0, 1, 0);
	FVector endRight(0, 1, 0);

	for (int i = 0; i < 5; i++) {
		USplineMeshComponent *seg = CreateSplineMeshComponent();
		
		FVector start(startPos + ((i * 3) * startRight));
		FVector end(endPos + ((i * 3) * endRight));

		seg->SetStartAndEnd(start, startTan, end, endTan);
	}

	UE_LOG(LogProck, Log, TEXT("Done"));
}

void ABoxActor::SetText(char *text) {
	if (mainLabel) {
		mainLabel->SetText(FString(ANSI_TO_TCHAR(text)));
	}
}
