// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <Engine/Classes/GameFramework/CharacterMovementComponent.h>
#include <Engine/Classes/Camera/CameraComponent.h>
#include "GameFramework/SpringArmComponent.h"
#include "Weapon_Actor.h"
#include "Basic_Character.h"
#include "HUD_UserWidget.h"
#include "TPS_Character.generated.h"

UCLASS()
class TEST1_API ATPS_Character : public ABasic_Character
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATPS_Character();

	// *** weapon ***
	USkeletalMeshComponent* GetSpecificPawnMesh() const;
	FName GetWeaponAttachPoint() const;
	void EquipWeapon(class AWeapon_Actor* Weapon);
	virtual void PostInitializeComponents() override;
	void SpawnDefaultInventory(int32 itemCode);
	// *** weapon ***
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void ControllMode(int32 mode);

	// *** weapon ***
	//USkeletalMeshComponent* WeaponComponent;

	UPROPERTY(EditDefaultsOnly, Category = Inventory)
	FName DisarmPoint;

	UPROPERTY(EditDefaultsOnly, Category = Inventory)
	FName WeaponAttackPoint;

	TArray<class AWeapon_Actor*> Inventory;

	UPROPERTY(EditAnywhere, Category = Inventory)
	class AWeapon_Actor* CurrentWeapon;

	void AddWeapon(class AWeapon_Actor* Weapon);

	void SetCurrentWeapon(class AWeapon_Actor* NewWeapon, class AWeapon_Actor* LastWeapon);
	
	UPROPERTY(EditDefaultsOnly, Category=Inventory)
	TArray<TSubclassOf<class AWeapon_Actor>> DefaultInventoryClasses;	

	void EquipWeapon();

	void DisArmWeapon();
		
	// *** weapon ***

	virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

public:	

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
		void MoveForward(float Axisval);
	UFUNCTION()
		void MoveRight(float Axisval);
	
	virtual void AddControllerPitchInput(float Axisval);
	virtual void AddControllerYawInput(float Axisval);
	virtual void Landed(const FHitResult& Hit) override;
		
	UFUNCTION()
		void StartJump();

	UFUNCTION()
		void StopJump();
	

	UFUNCTION()
		void PressDash();

	UFUNCTION()
		void Attack_0();

	UFUNCTION()
		void Disarm();

	/*UFUNCTION()
		void Attack_0_End();*/

	
	

	UPROPERTY(VisibleAnywhere)
	int32 jumpCount = 0;

	int32 ComboAttackNum = 1;

	UPROPERTY(VisibleAnywhere)
		USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere)
		UCameraComponent* TPSCameraComponent;

	

	UPROPERTY(EditAnywhere, Category = Anim)
		UAnimMontage* DoubleJump_AnimMontage;

	
	
	/*UPROPERTY()
		UHUD_UserWidget* hud;*/

	void SetGroundFriction(float friction);
	void ResetGroundFriction();

	void HpUIAplly();
};
