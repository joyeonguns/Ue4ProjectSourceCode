// Fill out your copyright notice in the Description page of Project Settings.


#include "Basic_Character.h"
#include "HP_UserWidget.h"
#include "Kismet/GameplayStatics.h"
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

}

// Called when the game starts or when spawned
void ABasic_Character::BeginPlay()
{
	Super::BeginPlay();
}

void ABasic_Character::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	Status_Component->OnHpIsZero.AddLambda([this]() -> void {
		UE_LOG(LogTemp, Warning, TEXT("OnHpIsZero"));
		UE_LOG(LogTemp, Warning, TEXT("DEAD"));
		PlayAnimMontage(Death_AnimMontage);
		SetActorEnableCollision(false);
		//DieCharacter();
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
	const float realDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	myHealth -= realDamage;
	
	Status_Component->SetDamage(realDamage);


	if (BeHit_AnimMontage && myHealth > 20.0f) {
		PlayAnimMontage(BeHit_AnimMontage);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta, FString::Printf(TEXT("HP : %f"), myHealth));
	}

	if (myHealth <= 0) {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta, FString::Printf(TEXT("Die HP : %f"), myHealth));
		
		PlayAnimMontage(Death_AnimMontage);
		FTimerHandle TH_Attack0_End;
		GetWorldTimerManager().SetTimer(TH_Attack0_End, this, &ABasic_Character::DieCharacter, 3.3f, false);	
	}

	return realDamage;
}

// Called every frame
void ABasic_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABasic_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABasic_Character::DieCharacter()
{
	this->Destroy();
}

void ABasic_Character::DefaultAttack()
{
	if (isDuringAttack == false) {
		if (bCanNextAttack == true && currentCombo <= MaxCombo && currentCombo != 1) {
			//currentCombo++;
		}
		else {
			currentCombo = 1;
		}

		FString PlaySection = "Attack_" + FString::FromInt(currentCombo);
		PlayAnimMontage(DefaultAttack_Montage, 1.2f, FName(*PlaySection));
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

//void ABasic_Character::SpawnDamage(float damage)
//{
//	//UWorld* world = GetWorld();
//	//FRotator SpawnRotation = { 0,0,0 };
//	//FVector myLoc = GetActorLocation() + FVector(0,0,150.0f);
//	//if (world)
//	//{
//	//	// 스폰하기 위해 필요한 파라메터 설정
//	//	FActorSpawnParameters SpawnParamater;
//	//	SpawnParamater.Owner = this;
//	//	SpawnParamater.Instigator = GetInstigator();
//	//	// 오브젝트 스폰
//	//	AFloatingDamage_Actor* floatingDamage = world->SpawnActor<AFloatingDamage_Actor>(Damage_Actor, myLoc, SpawnRotation, SpawnParamater);
//	//	// 스폰된 오브젝트의 함수 사용
//	//	if (floatingDamage)
//	//	{
//	//		floatingDamage->SetDamage(damage);
//	//	}
//	//	else {
//	//		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta, FString::Printf(TEXT("floatingDamage Error")));
//
//	//	}
//	//}
//	//else {
//	//	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta, FString::Printf(TEXT("world Error")));
//
//	//}
//
//	
//
//}

