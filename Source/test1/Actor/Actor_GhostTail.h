// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/PoseableMeshComponent.h"
#include "Actor_GhostTail.generated.h"

UCLASS()
class TEST1_API AActor_GhostTail : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AActor_GhostTail();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Set Initial Setting
	void Init(USkeletalMeshComponent* Pawn);

	UPROPERTY(Editanywhere, Category = Mesh)
		UPoseableMeshComponent* PoseMesh;
	
	UPROPERTY(Editanywhere, Category = Mat)
		UMaterialInstance* GhostMaterial;

	UPROPERTY(Editanywhere, Category = Mat)
		TArray<UMaterialInstanceDynamic*> Materials;

	// Data
	bool bGhostSpwn = false;
	float currentGhostTime;
	float GhostDuration = 1.0f;
};
