// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/AuraHUD.h"

#include "Aura/Public/UI/AuraUserWidget.h"
#include "Blueprint/UserWidget.h"
#include "UI/OverlayWidgetController.h"

UOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	if (OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WCParams);
		OverlayWidgetController->BindCallbacksToDependencies();
	}

	return OverlayWidgetController;
}

void AAuraHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	checkf(OverlayWidgetClass, TEXT("Overlay class not initialized, Make sure to assign variable in W_AuraHUD"));
	checkf(OverlayWidgetControllerClass, TEXT("Overlay widget class not initialized in W_AuraHUD"));
	
	UUserWidget* UserWidget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);

	OverlayWidget = Cast<UAuraUserWidget>(UserWidget);

	const FWidgetControllerParams& WCParams = FWidgetControllerParams(PC, PS, ASC, AS);

	UOverlayWidgetController* WidgetController = GetOverlayWidgetController(WCParams);
	
	OverlayWidget->SetWidgetController(WidgetController);

	WidgetController->BroadcastInitialValues();
	
	UserWidget->AddToViewport();
}
