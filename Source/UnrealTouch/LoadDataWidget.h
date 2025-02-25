// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LoadDataWidget.generated.h"

/**
 * 
 */
UCLASS()
class UNREALTOUCH_API ULoadDataWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void RemoveFromParent() override;

	UFUNCTION(BlueprintCallable, Category = "LoadSystem")
	void OpenLevelWithTransform(const FName LevelName, const FTransform& NewTransform);
	UFUNCTION(BlueprintCallable, Category = "LoadSystem")
	void RemoveLoadWidgetFromParent();
private:
	FTransform TargetTransform;
};
