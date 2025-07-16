// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "EditorUtilityLibrary.h"
#include "EditorFunction.generated.h"

/**
 * 
 */
UCLASS()
class GALGAMEKIT_API UEditorFunction : public UEditorUtilityLibrary
{
	GENERATED_BODY()
	
	UFUNCTION(BlueprintCallable, Category = "ArtExtension")
	UMaterialInstanceDynamic* GenerateDefaultMaterial(AActor* Actor);
};
