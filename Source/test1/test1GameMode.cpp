// Copyright Epic Games, Inc. All Rights Reserved.

#include "test1GameMode.h"
#include "test1Character.h"
#include "UObject/ConstructorHelpers.h"

Atest1GameMode::Atest1GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void Atest1GameMode::StartPlay()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Hellow World"));
}
