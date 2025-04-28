// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/AuraHUD.h"

#include "Aura/Public/UI/AuraUserWidget.h"
#include "Blueprint/UserWidget.h"

void AAuraHUD::BeginPlay()
{
	Super::BeginPlay();

	UUserWidget* UserWidget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	UserWidget->AddToViewport();
}
