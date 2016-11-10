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

/*
This method resolves the size of its internal contents (somewhat) and resizes
the translucent portion of the box to match them. 

It should be looking at nested nodes to do this resolution. Right now its just checking the size of its text
*/
FVector ABoxActor::SizeFitContents() {
	//return FVector();

	// Get the target size of the label and calculate a new size 
	FVector labelSize = mainLabel->GetTextLocalSize();
	FVector newSize;

	newSize.Y = BOX_DEPTH;
	newSize.Z = labelSize.Z + LABEL_MARGIN * 2;
	newSize.X = labelSize.Y + LABEL_MARGIN * 2;

	// Update the volume. The div(100) is for the base size of the box mesh
	FVector scale(newSize.X / 100, newSize.Y / 100, newSize.Z / 100);
	cube->SetRelativeScale3D(scale);

	// Center the label by halving its dimensions
	mainLabel->SetRelativeLocation(FVector(-newSize.X / 2 + LABEL_MARGIN, 0, -newSize.Z / 2 + LABEL_MARGIN));

	return newSize;
}

void ABoxActor::SetText(char *text) {
	if (mainLabel) {
		mainLabel->SetText(FString(UTF8_TO_TCHAR(text)));
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
