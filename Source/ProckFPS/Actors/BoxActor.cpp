// Fill out your copyright notice in the Description page of Project Settings.

#include "ProckFPS.h"

#include "Actors/ScopeActor.h"
#include "Actors/BoxActor.h"
#include "Utils/Config.h"

#include <stdio.h>
#include <math.h> 


void ABoxActor::SetText(char *text) {
	if (mainLabel) {
		mainLabel->SetText(FString(ANSI_TO_TCHAR(text)));
	}
}
