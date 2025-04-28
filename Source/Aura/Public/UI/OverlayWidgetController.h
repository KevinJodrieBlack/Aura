// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WidgetController.h"
#include "OverlayWidgetController.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float, NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChangedSignature, float, NewMaxHealth);

UCLASS(Blueprintable, BlueprintType)
class AURA_API UOverlayWidgetController : public UWidgetController
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable)
	FOnHealthChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnMaxHealthChangedSignature OnMaxHealthChanged;

public:
	
	void HealthChanged(const FOnAttributeChangeData& OnAttributeChangeData) const;
	void MaxHealthChanged(const FOnAttributeChangeData& OnAttributeChangeData) const;
	
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;
};
