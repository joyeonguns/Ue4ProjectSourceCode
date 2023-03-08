// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterStat_DataTable.h"
#include "Character_Stat_Component.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHPIsZeroDelegate);
DECLARE_MULTICAST_DELEGATE(FOnHPApllyDelegate);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TEST1_API UCharacter_Stat_Component : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCharacter_Stat_Component();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void InitializeComponent() override;
	
public:
	void SetRole(int32 Rolecode);

	void SetDamage(float Damage);
	
	void SetHp(float newHp);

	float GetAttack();
	float GetHpRatio();

	float GetHp();

	FOnHPIsZeroDelegate OnHpIsZero;
	FOnHPApllyDelegate OnHpApply;


private:

	struct FCharacterStat* current_Status = nullptr;
	
	UPROPERTY(EditInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
		int32 code;
	UPROPERTY(EditInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
		FString Role;
	UPROPERTY(Transient, EditInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
		float currentHp;

	UPROPERTY(EditAnywhere, Category = HUD)
		class UHUD_UserWidget* Hud;
};
