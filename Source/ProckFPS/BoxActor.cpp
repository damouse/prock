// Fill out your copyright notice in the Description page of Project Settings.

#include "ProckFPS.h"
#include "BoxActor.h"
#include <stdio.h>
#include <math.h>  

/*
// See this for adding connections between actors:
// http://ironthighs.com/unreal-engine-4/coding/2015/04/18/

Possible answer: setting the particle locations
https://answers.unrealengine.com/questions/140298/attaching-particle-to-socket-of-skeletal-mesh-runt.html
*/

ABoxActor::ABoxActor() {
	static ConstructorHelpers::FObjectFinder<UParticleSystem> beamActorClassFinder(TEXT("ParticleSystem'/Game/Particles/P_Beam_Actor.P_Beam_Actor'"));
	if (beamActorClassFinder.Succeeded()) {
		particleBeamActorComponent = beamActorClassFinder.Object;
	}
}

void ABoxActor::SetText(char *text) {
	if (mainLabel) {
		//UE_LOG(LogProck, Log, TEXT("Setting label to: '%s'"), ANSI_TO_TCHAR(text));
		mainLabel->SetText(FString(ANSI_TO_TCHAR(text)));
	}
}

// Create a beam attached to each actor 
void ABoxActor::ConnectToBox(ABoxActor* other) {
	char buffer[10];
	sprintf(buffer, "Connection%d\0", (int)connections.size());
	FString name = FString(ANSI_TO_TCHAR(buffer));

	UParticleSystemComponent *beam = NewObject<UParticleSystemComponent>(this, (FName(*(name))));
	beam->RegisterComponent();
	beam->SetTemplate(particleBeamActorComponent);
	beam->SetActorParameter(TEXT("BeamSource"), this);
	beam->SetActorParameter(TEXT("BeamTarget"), other);

	connections.push_back(beam);
}
