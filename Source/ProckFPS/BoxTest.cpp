// Fill out your copyright notice in the Description page of Project Settings.

#include "ProckFPS.h"
#include "BoxTest.h"


// Sets default values
ABoxTest::ABoxTest() {
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
}

// Called when the game starts or when spawned
void ABoxTest::BeginPlay() {
	Super::BeginPlay();	
}

void ABoxTest::CursorOver() {
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Overlap started"));
}
