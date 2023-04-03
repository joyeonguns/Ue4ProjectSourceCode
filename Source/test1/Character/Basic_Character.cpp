// Fill out your copyright notice in the Description page of Project Settings.


#include "Basic_Character.h"
#include "HP_UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "TPSGameInstance.h"
#include "Engine.h"



// Sets default values
ABasic_Character::ABasic_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	myMaxHealth = 100.0f;
	myHealth = myMaxHealth;
	Status_Component = CreateDefaultSubobject<UCharacter_Stat_Component>(TEXT("Status"));

	isCanMove = true;
	isCanJump = true;
	isCanRotate = true;

	isDash = false;
	isDuringAttack = false;

	bCanNextAttack = false;

	MaxCombo = 3;
	currentCombo = 0;
	bDead = false;

	realMoveSpeed = 600.0f;
}

// Called when the game starts or when spawned
void ABasic_Character::BeginPlay()
{
	Super::BeginPlay();
	//ResetBuff();
	//ApplyBuff_Shield();
}

void ABasic_Character::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	Status_Component->OnHpIsZero.AddLambda([this]() -> void {
		UE_LOG(LogTemp, Warning, TEXT("OnHpIsZero"));
		UE_LOG(LogTemp, Warning, TEXT("DEAD"));
		DieCharacter();
		});
	Status_Component->OnTakeDamage.AddLambda([this]() -> void {
		TakeShock();
		if (BeHit_AnimMontage) {
			PlayAnimMontage(BeHit_AnimMontage);
		}
		});
	Status_Component->OnResetAura.AddLambda([this]() -> void {
		ResetAura();
		});

	Anim = Cast<UTPSAnimInstance>(GetMesh()->GetAnimInstance());

	if (Anim) {
		Anim->OnCanNextComboDelegate.AddLambda([this]() -> void {
			UE_LOG(LogTemp, Warning, TEXT("OnCanNextCombo"));
			isDuringAttack = false;
			bCanNextAttack = true;
			});

		Anim->OnAttackEndDelegate.AddLambda([this]() -> void {
			UE_LOG(LogTemp, Warning, TEXT("OnAttackEnd"));
			AttackEnd();
			});

		Anim->OnHitEnd_Enemy_Delegate.AddLambda([this]() -> void {
			UE_LOG(LogTemp, Warning, TEXT("OnHitEnd_Enemy_Delegate"));
			//bShocking = false;
			//shockTime = 0.0f;
			EndShock();
			});
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AnimError"));
	}

}

void ABasic_Character::OnHit(float InputDamage, FDamageEvent const& DamageEvent, APawn* PawnInstigator, AActor* DamageCauser)
{
}

float ABasic_Character::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (bDead) return 0;

	const float realDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	

	Status_Component->SetDamage(realDamage);

	if (bElectric) {
		ApplyDeBuff_Electric();
	}

	return realDamage;
}

// Called every frame
void ABasic_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DebuffTick(DeltaTime);
}

// Called to bind functionality to input
void ABasic_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABasic_Character::DieCharacter()
{
	if (bDead) return;
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta, FString::Printf(TEXT("Die HP :")));
	if (Death_AnimMontage) {
		PlayAnimMontage(Death_AnimMontage);
	}

	SetActorEnableCollision(false);
	bDead = true;
	TakeShock();
	ResetAura();
	ResetDebuffAura();

	FTimerHandle TH_Attack0_End;
	GetWorldTimerManager().SetTimer(TH_Attack0_End, this, &ABasic_Character::DestroyCharacter, 3.3f, false);
}

void ABasic_Character::DestroyCharacter()
{
	
	this->Destroy();
}

void ABasic_Character::DefaultAttack(float speed)
{
	if (bShocking == false && isDuringAttack == false) {
		if (bCanNextAttack == true && currentCombo <= MaxCombo && currentCombo != 1) {
			//currentCombo++;
		}
		else {
			currentCombo = 1;
		}

		FString PlaySection = "Attack_" + FString::FromInt(currentCombo);
		PlayAnimMontage(DefaultAttack_Montage, speed, FName(*PlaySection));
		currentCombo++;



		isDuringAttack = true;
		isCanJump = false;
		isCanMove = false;
		isCanRotate = false;

	}

}

void ABasic_Character::AttackEnd()
{
	isDuringAttack = false;
	bCanNextAttack = false;

	isCanJump = true;
	isCanMove = true;
	isCanRotate = true;
}

void ABasic_Character::TakeShock()
{
	bShocking = true;
	isCanJump = false;
	isCanMove = false;
	isCanRotate = false;
	broll = false;
	shockTime = 10.0f;
}

void ABasic_Character::EndShock()
{
	bShocking = false;
	isCanJump = true;
	isCanMove = true;
	isCanRotate = true;
	isDuringAttack = false;
	bCanNextAttack = false;
	broll = false;
}

bool ABasic_Character::GetCheckShocking()
{
	return bShocking;
}

void ABasic_Character::SetMoveSpeed()
{
	GetCharacterMovement()->MaxWalkSpeed = realMoveSpeed * Move_Speed;
}

bool ABasic_Character::GetbDead()
{
	return bDead;
}


void ABasic_Character::ApplyBuff_Heart()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("ABasic_Character::ApplyBuff_Heart"));
	ApplyBuffCode = 1;

	Status_Component->SetRecovery_Percent(AddRecoverHp);

	SpwAura(HeartAuraClass);

	FTimerHandle TH;
	GetWorldTimerManager().SetTimer(TH, this, &ABasic_Character::ResetBuff, 1.5f, false);
}

void ABasic_Character::ApplyBuff_Energy()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("ABasic_Character::ApplyBuff_Energy"));
	// 특성 강화
	ApplyBuffCode = 2;

	Status_Component->Getcurrent_Status()->percentage *= 2;
		
	SpwAura(EnergyAuraClass);

}

void ABasic_Character::ApplyBuff_Arcane()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("ABasic_Character::ApplyBuff_Arcane"));
	// 모든 속도 강화
	ApplyBuffCode = 3;

	Move_Speed = (100 + AddSpeed) * 0.01f;
	Attack_Speed = (100 + AddSpeed) * 0.01f;
	SetMoveSpeed();

	SpwAura(ArcaneAuraClass);
}

void ABasic_Character::ApplyBuff_Dia()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("ABasic_Character::ApplyBuff_Dia"));
	// 수호천사
	ApplyBuffCode = 4;

	Status_Component->SetLife(AddLife);

	SpwAura(DiaAuraClass);
}

void ABasic_Character::ApplyBuff_Shield()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("ABasic_Character::ApplyBuff_Shield"));
	// 피격 쉴드
	ApplyBuffCode = 5;
	Status_Component->SetShield(AddShield);

	SpwAura(ShieldeAuraClass);

}

void ABasic_Character::ResetBuff()
{
	switch (ApplyBuffCode)
	{
	case 1:
		Status_Component->SetLife(0);
		break;
	case 2:
		Status_Component->Getcurrent_Status()->percentage /= 2;
		break;
	case 3:
		Move_Speed -= (AddSpeed * 0.01);
		Attack_Speed -= (AddSpeed * 0.01);
		break;
	case 4:
		Status_Component->SetLife(0);
		break;
	case 5:
		Status_Component->SetShield(0);
		break;

	default:
		break;
	}

	ApplyBuffCode = 0;
	ResetAura();
}

void ABasic_Character::ResetAura()
{
	if (ApplyAuraInstance != nullptr) {
		ApplyAuraInstance->Destroy();
		ApplyAuraInstance = nullptr;
	}
}

void ABasic_Character::SpwAura(TSubclassOf<AActor> AuraClass)
{
	ResetAura();

	ApplyAuraInstance = nullptr;

	FActorSpawnParameters spwInfo;
	ApplyAuraInstance = GetWorld()->SpawnActor<AActor>(AuraClass, spwInfo);

	if (ApplyAuraInstance) {
		USkeletalMeshComponent* PawnMessh = GetMesh();
		//FName AttackPoint = MyOwner->GetWeaponAttachPoint();
		//WeaponMesh->AttachTo(PawnMessh, AttachName);

		ApplyAuraInstance->GetRootComponent()->AttachTo(PawnMessh, "Aura");
	}

}

void ABasic_Character::DebuffTick(float deltaTime)
{
	if (bBurnning) {
		BurnTime -= deltaTime;

		if (BurnTime <= 0.0f) {
			BurnTime = 0.0f;
			bBurnning = false;
		}
	}
	if (bWetting) {
		WetTime -= deltaTime;

		if (WetTime <= 0.0f) {
			WetTime = 0.0f;
			bWetting = false;
		}
	}
	if (bElectric) {
		ElectricTime -= deltaTime;

		if (ElectricTime <= 0.0f) {
			ElectricTime = 0.0f;
			bElectric = false;
			ResetDebuffAura();
		}
	}

}

void ABasic_Character::SpwnDebuffAura(TSubclassOf<AActor> AuraClass)
{
	ResetDebuffAura();

	FActorSpawnParameters spwInfo;

	ApplyDebuffAuraInstance = GetWorld()->SpawnActor<AActor>(AuraClass, spwInfo);

	if (ApplyDebuffAuraInstance) {
		USkeletalMeshComponent* PawnMessh = GetMesh();
		//FName AttackPoint = MyOwner->GetWeaponAttachPoint();
		//WeaponMesh->AttachTo(PawnMessh, AttachName);

		ApplyDebuffAuraInstance->GetRootComponent()->AttachTo(PawnMessh, "Aura");
	}
}

void ABasic_Character::ResetDebuffAura()
{
	if (ApplyDebuffAuraInstance) {
		ApplyDebuffAuraInstance->Destroy();
	}
}

void ABasic_Character::GetDeBuff_Burn()
{
	if (!bBurnning) {
		GetWorldTimerManager().SetTimer(TH_burn, this, &ABasic_Character::ApplyDeBuff_Burn, 1.0f, true);
		SpwnDebuffAura(BurnDebuffClass);
	}

	bBurnning = true;
	BurnTime = DefaultBurnTime;
}

void ABasic_Character::GetDeBuff_Electric()
{
	if (!bElectric) {
		ApplyDeBuff_Electric();
		SpwnDebuffAura(ElectricDebuffClass);
	}
		

	bElectric = true;
	ElectricTime = DefaultElectricTime;
}

void ABasic_Character::GetDeBuff_Wet()
{
	if (!bWetting) {
		GetWorldTimerManager().SetTimer(TH_wet, this, &ABasic_Character::ApplyDeBuff_Wet, 0.1f, true);
		SpwnDebuffAura(WetDebuffClass);	
	}
	bWetting = true;
	WetTime = DefaultWetTime;
}



void ABasic_Character::ApplyDeBuff_Burn()
{	
	Status_Component->SetDebuffDamage(5.0);
	if (!bBurnning) {
		GetWorldTimerManager().ClearTimer(TH_burn);
		ResetDebuffAura();
	}		
}

void ABasic_Character::ApplyDeBuff_Electric()
{
	//UGameplayStatics::ApplyDamage(this, 5.0f, NULL, this, UDamageType::StaticClass());
	// 애니메이션 실행
	if (BeElectric_AnimMontage) {
		Status_Component->SetDebuffDamage(3.0);
		PlayAnimMontage(BeElectric_AnimMontage);
	}
}

void ABasic_Character::ApplyDeBuff_Wet()
{
	if (WetDebuff < 0.8f) {
		Move_Speed -= 0.008f;
		Attack_Speed -= 0.004f;
		WetDebuff += 0.008f;
		SetMoveSpeed();
	}	

	if (!bWetting) {
		Move_Speed += WetDebuff;
		Attack_Speed += (WetDebuff / 2);

		WetDebuff = 0;


		SetMoveSpeed();
		GetWorldTimerManager().ClearTimer(TH_wet);
		ResetDebuffAura();
	}
}



void ABasic_Character::DifuseBuff()
{
	bBurnning = false;
	bElectric = false;
	bWetting = false;

	BurnTime = 0;
	ElectricTime = 0;
	bWetting = 0;
}

