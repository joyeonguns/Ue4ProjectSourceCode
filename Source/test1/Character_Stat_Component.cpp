// Fill out your copyright notice in the Description page of Project Settings.


#include "Character_Stat_Component.h"
#include "TPSGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "TPSPlayerController.h"
#include "HUD_UserWidget.h"

// Sets default values for this component's properties
UCharacter_Stat_Component::UCharacter_Stat_Component()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// Inintialize 함수사용을 위해
	bWantsInitializeComponent = true;

	code = 2;
	// ...
}


// Called when the game starts
void UCharacter_Stat_Component::BeginPlay()
{
	Super::BeginPlay();
	// ...
		
}

void UCharacter_Stat_Component::InitializeComponent()
{
	Super::InitializeComponent();

	current_Status = new FCharacterStat();

	if (Mode == 0) {
		TakeInstanceDatas(code);
		SetCurrentData();
		SetHp(current_Status->Hp);
	}
	else {
		current_Status = new FCharacterStat();
		SetEnemyRangeData();
		SetHp(current_Status->Hp);
	}
}

void UCharacter_Stat_Component::TakeInstanceDatas(int32 Rolecode)
{
	//FName txtn = UGameplayStatics::GetGameInstance(GetWorld())->GetFName();
	UE_LOG(LogTemp, Warning, TEXT(" NAME!!!"));

	auto _GameInstance = Cast<UTPSGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (_GameInstance) {
		UE_LOG(LogTemp, Warning, TEXT("GameInstance Success"));

		Rolecode = _GameInstance->SelectedWeaponCode;
		Default_Status = _GameInstance->Get_FCharacter_Status(Rolecode);
		School = Default_Status->School;

		if (_GameInstance->statusArray.Num() < 1) return;

		TArray<int32> _statusArray = _GameInstance->statusArray;


		current_StatusLevel = new FStatusLevel();
		current_StatusLevel->Hp = _GameInstance->Get_FStatusLevel(_statusArray[0])->Hp;
		current_StatusLevel->Damage = _GameInstance->Get_FStatusLevel(_statusArray[1])->Damage;
		current_StatusLevel->Critical = _GameInstance->Get_FStatusLevel(_statusArray[2])->Critical;
		current_StatusLevel->CoolTime = _GameInstance->Get_FStatusLevel(_statusArray[3])->CoolTime;

		_GameInstance->BattleData_Enemy->Level = _GameInstance->statusArray[4];
		_GameInstance->BattleData_Enemy->Elite = _GameInstance->statusArray[5] * 10;

		if (current_StatusLevel) {
			UE_LOG(LogTemp, Warning, TEXT("current_Status Success, School : %s"), *School);
			
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("current_Status ERROR"));
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("GameInstance ERROR"));
	}

}

void UCharacter_Stat_Component::SetCurrentData()
{	
	if (Default_Status == nullptr) return;

	current_Status->School = Default_Status->School;
	current_Status->Hp = Default_Status->Hp + current_StatusLevel->Hp;
	current_Status->Damage += Default_Status->Damage + current_StatusLevel->Damage;
	current_Status->Critical += Default_Status->Critical + current_StatusLevel->Critical;
	current_Status->CoolTime += Default_Status->CoolTime + current_StatusLevel->CoolTime;
	current_Status->percentage = Default_Status->percentage;

	currentHp = current_Status->Hp;

	auto _GameInstance = Cast<UTPSGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (_GameInstance) {
		_GameInstance->BattleData_Player->Hp = current_Status->Hp;
		_GameInstance->BattleData_Player->Damage = current_Status->Damage;
		_GameInstance->BattleData_Player->Critical = current_Status->Critical;
		_GameInstance->BattleData_Player->Accel_CoolTime = current_Status->CoolTime;
		_GameInstance->BattleData_Player->Speed = 0;
		_GameInstance->BattleData_Player->School_Percent = current_Status->percentage;
	}	

	if (current_StatusLevel) {
		UE_LOG(LogTemp, Warning, TEXT("current_Status Success, School : %s"), *School);
		UE_LOG(LogTemp, Warning, TEXT("current_Status Success, Hp : %f"), current_Status->Hp);
		UE_LOG(LogTemp, Warning, TEXT("current_Status Success, Damage : %f"), current_Status->Damage);
		UE_LOG(LogTemp, Warning, TEXT("current_Status Success, Critical : %d"), current_Status->Critical);
		UE_LOG(LogTemp, Warning, TEXT("current_Status Success, CoolTime : %d"), current_Status->CoolTime);

	}
	
}

void UCharacter_Stat_Component::SetDamage(float Damage)
{
	if (Shield > 0) {
		Shield--;
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Shield"));
		if (Shield == 0) {
			OnResetAura.Broadcast();
		}
		return;
	}
	else {
		Shield = 0;
		if (current_Status && currentHp > 0.0f) {
			//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Delecate SetDamage"));
			int newHp = FMath::Clamp<float>(currentHp - Damage, 0.0f, current_Status->Hp);
			OnTakeDamage.Broadcast();
			OnTakeDamage_Param.Broadcast(Damage);
			SetHp(newHp);
		}
	}	
}

void UCharacter_Stat_Component::SetDebuffDamage(float Damage)
{
	if (current_Status) {
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Delecate SetDamage"));
		int newHp = FMath::Clamp<float>(currentHp - Damage, 0.0f, current_Status->Hp);
		SetHp(newHp);
	}
}

void UCharacter_Stat_Component::SetHp(float newHp)
{
	currentHp = newHp;
	OnHpApply.Broadcast();

	if (currentHp <= KINDA_SMALL_NUMBER) {
		currentHp = 0.0f;
		if (life > 0) {
			life--;
			currentHp = current_Status->Hp / 2;
			OnHpApply.Broadcast();
			OnResetAura.Broadcast();
			return;
		}
		OnHpIsZero.Broadcast();
		//OnResetAura.Broadcast();
	}


	
}

void UCharacter_Stat_Component::SetRecovery(float addHp)
{
	float newHp = FMath::Clamp<float>(currentHp + addHp, 0.0f, current_Status->Hp);
	SetHp(newHp);
}

void UCharacter_Stat_Component::SetRecovery_Percent(float addHp)
{
	float newHp = FMath::Clamp<float>(currentHp + current_Status->Hp * addHp, 0.0f, current_Status->Hp);
	SetHp(newHp);
}

float UCharacter_Stat_Component::GetAttack()
{
	float Attack = 0.0f;
	if (current_Status) {
		Attack = 20.0f;
	}
	return Attack;
}

float UCharacter_Stat_Component::GetHpRatio()
{
	if (currentHp <= KINDA_SMALL_NUMBER)
		currentHp = 0.0f;
	return currentHp / current_Status->Hp;
}

float UCharacter_Stat_Component::GetHp()
{
	return currentHp;
}

void UCharacter_Stat_Component::SetMode(int32 mode)
{
	Mode = mode;
}

FCharacterStat* UCharacter_Stat_Component::GetStatus()
{
	return current_Status;
}

void UCharacter_Stat_Component::SetShield(int32 NewShield)
{
	Shield = NewShield;
}

void UCharacter_Stat_Component::SetLife(int32 NewLife)
{
	life = NewLife;
}

FCharacterStat* UCharacter_Stat_Component::Getcurrent_Status()
{
	return current_Status;
}

void UCharacter_Stat_Component::SetEnemyRangeData()
{
	//FName txtn = UGameplayStatics::GetGameInstance(GetWorld())->GetFName();
	UE_LOG(LogTemp, Warning, TEXT(" NAME!!!"));

	auto _GameInstance = Cast<UTPSGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (_GameInstance) {
		UE_LOG(LogTemp, Warning, TEXT("GameInstance Success"));


		TArray<int32> _statusArray = _GameInstance->statusArray;
		int32 level = _statusArray[4];

		Default_Status = _GameInstance->Get_FEnemyRange_Status(level);

		current_Status = new FCharacterStat();
		Default_Status->DeepCopy(current_Status);
		


		if (current_Status) {
			UE_LOG(LogTemp, Warning, TEXT("Enemy Success, School : %s"), *School);
			UE_LOG(LogTemp, Warning, TEXT("Enemy Success, Hp : %f"), current_Status->Hp);
			UE_LOG(LogTemp, Warning, TEXT("Enemy Success, Damage : %f"), current_Status->Damage);
			UE_LOG(LogTemp, Warning, TEXT("Enemy Success, Critical : %d"), current_Status->Critical);
			UE_LOG(LogTemp, Warning, TEXT("Enemy Success, CoolTime : %d"), current_Status->CoolTime);
			UE_LOG(LogTemp, Warning, TEXT("Enemy Success, percentage : %d"), current_Status->percentage);
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("GameInstance ERROR"));
	}
}




