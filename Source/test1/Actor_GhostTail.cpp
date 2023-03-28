// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor_GhostTail.h"
#include <Kismet/KismetMaterialLibrary.h>

// Sets default values
AActor_GhostTail::AActor_GhostTail()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PoseMesh = CreateDefaultSubobject<UPoseableMeshComponent>(TEXT("POSEABLEMESH"));

	/*ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_PoseMesh(TEXT("SkeletalMesh"));
	if (SK_PoseMesh.Succeeded())
	{
		PoseMesh->SetSkeletalMesh(SK_PoseMesh.Object);
	}*/

	/*ConstructorHelpers::FObjectFinder<UMaterialInstance> M_GhostTail(TEXT("MaterialInstanceConstanttTail'"));
	if (M_GhostTail.Succeeded())
	{
		GhostMaterial = M_GhostTail.Object;
	}*/


}

// Called when the game starts or when spawned
void AActor_GhostTail::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AActor_GhostTail::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bGhostSpwn) {
		currentGhostTime -= DeltaTime;
		for (int i = 0; i < Materials.Num(); i++)
		{
			Materials[i]->SetScalarParameterValue("Opacity", currentGhostTime / GhostDuration);
		}


		if (currentGhostTime <= 0.0f) {
			Destroy();
		}
	}
}

void AActor_GhostTail::Init(USkeletalMeshComponent* Pawn)
{
	PoseMesh->CopyPoseFromSkeletalComponent(Pawn);
	TArray<UMaterialInterface*> Mats = PoseMesh->GetMaterials();

	for (int i = 0; i < Mats.Num(); i++)
	{
		Materials.Add(UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(), GhostMaterial));
		PoseMesh->SetMaterial(i, Materials[i]);
	}
	currentGhostTime = GhostDuration;
	bGhostSpwn = true;
}

