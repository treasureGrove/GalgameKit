// Fill out your copyright notice in the Description page of Project Settings.


#include "LoadDataWidget.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"

void ULoadDataWidget::RemoveFromParent()
{
}

void ULoadDataWidget::OpenLevelWithTransform(const FName LevelName, const FTransform& NewTransform)
{
	TargetTransform = NewTransform;
}

void ULoadDataWidget::RemoveLoadWidgetFromParent()
{
	Super::RemoveFromParent();
}
