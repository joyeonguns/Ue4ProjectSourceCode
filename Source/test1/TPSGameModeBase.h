// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include <Blueprint/UserWidget.h>
#include "TPSGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class TEST1_API ATPSGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void StartPlay() override;

	UFUNCTION(BlueprintCallable, Category = UI)
		void ChangeMenuUI(TSubclassOf<UUserWidget> NewWidgetClasss);

	TSubclassOf<UUserWidget> GetLobbyWidgetClass();
	void SetStartingWidgetClass(TSubclassOf<UUserWidget> NewWidgetClass);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = UI)
		TSubclassOf<UUserWidget> StartingWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = UI)
		TSubclassOf<UUserWidget> LobbyWidgetClass;

	UPROPERTY()
		UUserWidget* CurrentWidget;
};
