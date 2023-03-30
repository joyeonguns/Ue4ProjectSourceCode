// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSGameModeBase.h"

void ATPSGameModeBase::StartPlay()
{
	Super::StartPlay();
	/*if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Hellow TPSGameMode"));
	}
	if (GetWorld()->GetMapName() == FString("UEDPIE_0_Title_Level")) {
		ChangeMenuUI(StartingWidgetClass);
	}*/
}

void ATPSGameModeBase::ChangeMenuUI(TSubclassOf<UUserWidget> NewWidgetClasss)
{
	if (CurrentWidget != nullptr) {
		CurrentWidget->RemoveFromViewport();
		CurrentWidget = nullptr;
	}

	if (NewWidgetClasss != nullptr) {
		CurrentWidget = CreateWidget(GetWorld(), NewWidgetClasss);
		if (CurrentWidget != nullptr) {
			CurrentWidget->AddToViewport();
			//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT(" CurrentWidget "));
		}
	}

	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Change UI"));
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, GetWorld()->GetMapName());
}

TSubclassOf<UUserWidget> ATPSGameModeBase::GetLobbyWidgetClass()
{
	return LobbyWidgetClass;
}

void ATPSGameModeBase::SetStartingWidgetClass(TSubclassOf<UUserWidget> NewWidgetClass)
{
	StartingWidgetClass = NewWidgetClass;
}
