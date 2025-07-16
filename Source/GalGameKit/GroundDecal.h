// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GroundDecal.generated.h"

UCLASS()
class GALGAMEKIT_API AGroundDecal :public AActor
{
	GENERATED_BODY()
	
public:	
	AGroundDecal();
protected:


private: 
	UFUNCTION()
	void OnRunButtonClicked();
};
