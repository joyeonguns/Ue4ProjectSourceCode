// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Actor_ItemModel.generated.h"

UCLASS()
class TEST1_API AActor_ItemModel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AActor_ItemModel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


private:
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		TArray<USkeletalMeshComponent*> MeshArray;

	USkeletalMeshComponent* ItemMesh;

};
