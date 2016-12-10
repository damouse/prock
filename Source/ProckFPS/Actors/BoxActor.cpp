// Fill out your copyright notice in the Description page of Project Settings.

#include "ProckFPS.h"
#include "Actors/BoxActor.h"
#include <stdio.h>
#include <math.h> 

#include "Glue/Scope.h"


void ABoxActor::SetText(char *text) {
	if (mainLabel) {
		mainLabel->SetText(FString(ANSI_TO_TCHAR(text)));
	}
}

