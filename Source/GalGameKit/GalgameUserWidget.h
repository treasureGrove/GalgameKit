// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "GalgameUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class GALGAMEKIT_API UGalgameUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Button")
	void BindButtonOnClick(const TArray<UButton*>& Buttons, const TArray<UObject*>& Sources);
	UFUNCTION(BlueprintImplementableEvent, Category = "Button")
	void SelectionBtn(UObject* Source);
protected:
	UPROPERTY()
	TMap<UButton*, UObject*> ButtonToSourceMap;
	UFUNCTION()
	void HandleButtonClicked();

};
