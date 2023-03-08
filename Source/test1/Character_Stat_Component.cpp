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
	SetRole(code);
}

void UCharacter_Stat_Component::SetRole(int32 Rolecode)
{
	//FName txtn = UGameplayStatics::GetGameInstance(GetWorld())->GetFName();
	UE_LOG(LogTemp, Warning, TEXT(" NAME!!!"));

	auto _GameInstance = Cast<UTPSGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (_GameInstance) {
		UE_LOG(LogTemp, Warning, TEXT("GameInstance Success"));
		current_Status = _GameInstance->Get_FCharacter_Status(Rolecode);
		if (current_Status) {
			Role = current_Status->Role;
			currentHp = current_Status->Hp;
			SetHp(current_Status->Hp);
			UE_LOG(LogTemp, Warning, TEXT("current_Status Success, Role : %s"), *Role);
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("current_Status ERROR"));
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("GameInstance ERROR"));
	}

}

void UCharacter_Stat_Component::SetDamage(float Damage)
{
	if (current_Status) {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Delecate SetDamage"));
		currentHp = FMath::Clamp<float>(currentHp - Damage, 0.0f, current_Status->Hp);
		SetHp(currentHp);
	}
}

void UCharacter_Stat_Component::SetHp(float newHp)
{
	OnHpApply.Broadcast();
	if (currentHp <= KINDA_SMALL_NUMBER) {
		currentHp = 0.0f;
		OnHpIsZero.Broadcast();
	}
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




