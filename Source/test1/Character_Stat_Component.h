// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterStat_DataTable.h"
#include "DataTable_StatLevel.h"
#include "Character_Stat_Component.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHPIsZeroDelegate);
DECLARE_MULTICAST_DELEGATE(FOnHPApllyDelegate);
DECLARE_MULTICAST_DELEGATE(FOnTakeDamageDelegate);
DECLARE_MULTICAST_DELEGATE(FOnResetAuraDelegate);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnTakeDamageDelegate_Param, float)

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
	void TakeInstanceDatas(int32 Rolecode);
	void SetCurrentData();

	void SetDamage(float Damage);	
	void SetDebuffDamage(float Damage);
	void SetHp(float newHp);

	void SetRecovery(float addHp);
	void SetRecovery_Percent(float addHp);

	float GetAttack();
	float GetHpRatio();

	float GetHp();

	FOnHPIsZeroDelegate OnHpIsZero;
	FOnHPApllyDelegate OnHpApply;
	FOnTakeDamageDelegate OnTakeDamage;
	FOnResetAuraDelegate OnResetAura;
	FOnTakeDamageDelegate_Param OnTakeDamage_Param;

	void SetMode(int32 mode);

	FCharacterStat* GetStatus();

	void SetShield(int32 NewShield);
	void SetLife(int32 NewLife);

	struct FCharacterStat* Getcurrent_Status();

	void SetEnemyRangeData();

private:

	// Ä³¸¯ÅÍ ½ºÅÝ
	struct FStatusLevel* current_StatusLevel = nullptr;

	struct FCharacterStat* Default_Status = nullptr;
	struct FCharacterStat* current_Status = nullptr;
	

	UPROPERTY(EditInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
		int32 code;
	UPROPERTY(EditInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
		FString School;
	UPROPERTY(Transient, EditInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
		float currentHp;

	UPROPERTY(EditAnywhere, Category = HUD)
		class UHUD_UserWidget* Hud;

	int32 Mode;

	int32 Shield = 0;
	int32 life = 0;

};
