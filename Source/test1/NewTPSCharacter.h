// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <Engine/Classes/GameFramework/SpringArmComponent.h>
#include <Engine/Classes/Components/CapsuleComponent.h>
#include <Engine/Classes/Camera/CameraComponent.h>
#include <Engine/Classes/GameFramework/CharacterMovementComponent.h>
#include "NewTPSCharacter.generated.h"

UCLASS()
class TEST1_API ANewTPSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANewTPSCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void ControllMode(int32 mode);
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

	UFUNCTION()
		void StartJump();

	UFUNCTION()
		void StopJump();

	UFUNCTION()
		void PressDash();


	UPROPERTY(EditAnywhere, Category = "camera")
		USpringArmComponent* SpringArm;
	UPROPERTY(EditAnywhere, Category = "camera")
		UCameraComponent* Camera;

	

	bool isDash = false;
};
