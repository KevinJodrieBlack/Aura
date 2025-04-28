// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController.h"

void UWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WidgetControllerParams)
{
	PlayerState = WidgetControllerParams.PlayerState;
	PlayerController = WidgetControllerParams.PlayerController;
	AbilitySystemComponent = WidgetControllerParams.AbilitySystemComponent;
	AttributeSet = WidgetControllerParams.AttributeSet;
}

void UWidgetController::BroadcastInitialValues()
{
	
}

void UWidgetController::BindCallbacksToDependencies()
{
	
}
