// Fill out your copyright notice in the Description page of Project Settings.


#include "TPS_Character.h"
#include "TPSPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include <Engine/Classes/Components/CapsuleComponent.h>

// Sets default values
ATPS_Character::ATPS_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	
	
	
	ControllMode(1);
	isCanJump = true;
	isCanMove = true;
	isCanRotate = true;
}


// ============= weapon ==============
USkeletalMeshComponent* ATPS_Character::GetSpecificPawnMesh() const
{
	return GetMesh();
}

FName ATPS_Character::GetWeaponAttachPoint() const
{
	return WeaponAttackPoint;
}

void ATPS_Character::EquipWeapon(AWeapon_Actor* Weapon)
{
	if (Weapon) {
		SetCurrentWeapon(Weapon, CurrentWeapon);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("EQUIP WEAPON !!"));
	}
}

void ATPS_Character::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void ATPS_Character::SpawnDefaultInventory(int32 itemCode)
{
	int32 NumWeaponClasses = DefaultInventoryClasses.Num();
	FActorSpawnParameters SpawnInfo;
	UWorld* world = GetWorld();
	AWeapon_Actor* NewWeapon = world->SpawnActor<AWeapon_Actor>(DefaultInventoryClasses[itemCode], SpawnInfo);
	AddWeapon(NewWeapon);

	if (Inventory.Num() > 0) {
		EquipWeapon(Inventory[0]);
	}
}

void ATPS_Character::AddWeapon(AWeapon_Actor* Weapon)
{
	if (Weapon) {
		Inventory.AddUnique(Weapon);
	}
}

void ATPS_Character::SetCurrentWeapon(AWeapon_Actor* NewWeapon, AWeapon_Actor* LastWeapon)
{
	AWeapon_Actor* LocalLastWeapon = NULL;
	if (LastWeapon != NULL) {
		LocalLastWeapon = LastWeapon;
	}

	if (NewWeapon) {
		CurrentWeapon = NewWeapon;
		NewWeapon->SetOwningPawn(this);
		EquipWeapon();
	}
}

void ATPS_Character::EquipWeapon()
{
	if (CurrentWeapon) {
		CurrentWeapon->AttachMeshToPawn(WeaponAttackPoint);
	}
}

void ATPS_Character::DisArmWeapon()
{
	if (CurrentWeapon) {
		CurrentWeapon->AttachMeshToPawn(DisarmPoint);
	}
}

float ATPS_Character::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float takeDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Player Take Damage"));

	

	return takeDamage;
}

// ============= weapon ==============


// Called when the game starts or when spawned
void ATPS_Character::BeginPlay()
{
	Super::BeginPlay();
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Set TPS_Character"));
	}


	Status_Component->OnHpApply.AddUObject(this, &ATPS_Character::HpUIAplly);
	
	bDisarm = false;
}

void ATPS_Character::ControllMode(int32 mode)
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	TPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));

	SpringArmComponent->SetupAttachment(GetCapsuleComponent());
	TPSCameraComponent->SetupAttachment(SpringArmComponent);

	SpringArmComponent->TargetArmLength = 450.0f;
	SpringArmComponent->SetRelativeRotation(FRotator::ZeroRotator);
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->bInheritPitch = true;
	SpringArmComponent->bInheritRoll = true;
	SpringArmComponent->bInheritYaw = true;
	SpringArmComponent->bDoCollisionTest = true;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);	
}

// Called every frame
void ATPS_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATPS_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// 축 매핑
	InputComponent->BindAxis("MoveForward", this, &ATPS_Character::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ATPS_Character::MoveRight);
	InputComponent->BindAxis("Turn", this, &ATPS_Character::AddControllerYawInput);
	InputComponent->BindAxis("LookUp", this, &ATPS_Character::AddControllerPitchInput);
	// 액션 매핑
	InputComponent->BindAction("Jump", IE_Pressed, this, &ATPS_Character::StartJump);
	InputComponent->BindAction("Jump", IE_Released, this, &ATPS_Character::StopJump);
	InputComponent->BindAction("Dash", IE_Pressed, this, &ATPS_Character::PressDash);
	InputComponent->BindAction("Attack_0", IE_Pressed, this, &ATPS_Character::Attack_0);
	InputComponent->BindAction("Disarm", IE_Pressed, this, &ATPS_Character::Disarm);

}

void ATPS_Character::MoveForward(float Axisval)
{
	if (isCanMove) {
		FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
		AddMovementInput(Direction, Axisval);
	}
}

void ATPS_Character::MoveRight(float Axisval)
{
	if (isCanMove) {
		FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
		
		
		AddMovementInput(Direction, Axisval);
	}
	
}

void ATPS_Character::AddControllerPitchInput(float Axisval)
{	
	if (isCanRotate) {
		//Axisval *= 0.5f;
		Super::AddControllerPitchInput(Axisval);
	}
	
}

void ATPS_Character::AddControllerYawInput(float Axisval)
{
	if (isCanRotate) {
		Super::AddControllerYawInput(Axisval);
	}
	
}

void ATPS_Character::Landed(const FHitResult& Hit)
{
	jumpCount = 0;
}

void ATPS_Character::StartJump()
{
	if (isCanJump) {	
		jumpCount++;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Jump!!"));		
		if (jumpCount == 1) {
			Jump();			
		}	
		else if (jumpCount == 2) {
			LaunchCharacter(FVector(0, 0, 500), false, true);
			PlayAnimMontage(DoubleJump_AnimMontage);
		}		
	}
}

void ATPS_Character::StopJump()
{
	if (isCanJump) {
		//bPressedJump = false;
	}
	
}

void ATPS_Character::PressDash()
{
	/*SetGroundFriction(0.0f);

	FVector DashVector = (GetVelocity().GetSafeNormal()) * 2000;
	LaunchCharacter(DashVector, false, true);
	PlayAnimMontage(Dash_AnimMontage, 0.2f);


	FTimerHandle TH_Friction;
	GetWorldTimerManager().SetTimer(TH_Friction, this, &ATPS_Character::ResetGroundFriction, 0.3f, false);
	*/


	// 대쉬 온
	if (isDash == false) {
		isDash = true;

		GetCharacterMovement()->MaxWalkSpeed = 700;
	}
	else {
		isDash = false;
		GetCharacterMovement()->MaxWalkSpeed = 400;
	}
}

void ATPS_Character::Attack_0()
{
	//if (isDuringAttack == false) {
	//	FString PlaySection = "Attack_" + FString::FromInt(ComboAttackNum);
	//	PlayAnimMontage(DefaultAttack_Montage, 1.2f, FName(*PlaySection));
	//	ComboAttackNum++;
	//	if (ComboAttackNum > 3)
	//		ComboAttackNum = 1;
	//	
	//	
	//	
	//	isDuringAttack = true;
	//	isCanJump = false;
	//	isCanMove = false;
	//	isCanRotate = false;

	//	CurrentWeapon->ApplyAttack();

	//	// 1초후 상태 변경
	//	FTimerHandle TH_Attack0_End;
	//	GetWorldTimerManager().SetTimer(TH_Attack0_End, this, &ATPS_Character::Attack_0_End, 1.f, false);
	//}

	if (bDisarm) return;

	if (!isDuringAttack) {
		CurrentWeapon->ApplyAttack();
	}

	DefaultAttack();
	
}

void ATPS_Character::Disarm()
{
	if (bDisarm) {
		bDisarm = false;
		PlayAnimMontage(Armed_AnimMontage);

		FTimerHandle TH_Equip;
		GetWorldTimerManager().SetTimer(TH_Equip, this, &ATPS_Character::EquipWeapon, 1.f, false);		
	}
	else {
		bDisarm = true;
		PlayAnimMontage(Disarm_AnimMontage);

		FTimerHandle TH_Disarm;
		GetWorldTimerManager().SetTimer(TH_Disarm, this, &ATPS_Character::DisArmWeapon, 1.f, false);

	}
}

void ATPS_Character::SetGroundFriction(float friction)
{
	GetCharacterMovement()->GroundFriction = friction;
}

void ATPS_Character::ResetGroundFriction()
{
	GetCharacterMovement()->GroundFriction = 8.0f;
}

void ATPS_Character::HpUIAplly()
{
	auto playerController = Cast<ATPSPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	playerController->GetHUD()->SetHP(Status_Component->GetHpRatio(), 1.f);

}



