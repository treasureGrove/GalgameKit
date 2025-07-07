// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/DecalComponent.h"
#include "Engine/StaticMesh.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "GroundDecal.generated.h"

UCLASS()
class GALGAMEKIT_API AGroundDecal : public AActor
{
	GENERATED_BODY()
	
public:	
	AGroundDecal();
	UPROPERTY(EditAnywhere, Category = "Grid Decal")
	UStaticMesh* SourceMesh;
	UPROPERTY(EditAnywhere, Category = "Grid Decal")
	UMaterialInterface* DecalMaterial;
	UPROPERTY(EditAnywhere, Category = "Grid Decal")
	float DecalSize = 100;
	UFUNCTION(BlueprintCallable, Category = "Grid Decal")
	void SpawnGridDecal(const FVector& Location, const FVector& Normal);
	virtual void Tick(float DeltaTime) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FBox GetMeshBounds() const;

	FTransform CalculateDecalTransform(const FVector& Location, const FVector& Normal) const;
private: 
    UPROPERTY(VisibleAnywhere, Category = "Grid Decal")  
    UDecalComponent* GridDecalComponent;  
};
