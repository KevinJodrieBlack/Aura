// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/OverlayWidgetController.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	const UAuraAttributeSet* AuraAttributeSet = Cast<UAuraAttributeSet>(AttributeSet);
	
	OnMaxHealthChanged.Broadcast(AuraAttributeSet->GetMaxHealth());
	OnHealthChanged.Broadcast(AuraAttributeSet->GetHealth());
	OnManaChanged.Broadcast(AuraAttributeSet->GetMana());
	OnMaxManaChanged.Broadcast(AuraAttributeSet->GetMaxMana());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	const UAuraAttributeSet* AuraAttributeSet = Cast<UAuraAttributeSet>(AttributeSet);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetHealthAttribute()).AddUObject(this, &UOverlayWidgetController::HealthChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxHealthAttribute()).AddUObject(this, &UOverlayWidgetController::MaxHealthChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetManaAttribute()).AddUObject(this, &UOverlayWidgetController::ManaChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxManaAttribute()).AddUObject(this, &UOverlayWidgetController::MaxManaChanged);
	
	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->AssetTags.AddLambda([] (const FGameplayTagContainer& TagContainer)
	{
		UE_LOG(LogTemp, Warning, TEXT("Effect Applied"))
		for (const FGameplayTag& Tag : TagContainer)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Blue, FString::Printf(TEXT("Effect Tag: %s"), *Tag.ToString()));
		}
	});
}

void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& OnAttributeChangeData) const
{
	OnHealthChanged.Broadcast(OnAttributeChangeData.NewValue);
}

void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& OnAttributeChangeData) const
{
	OnMaxHealthChanged.Broadcast(OnAttributeChangeData.NewValue);
}

void UOverlayWidgetController::ManaChanged(const FOnAttributeChangeData& OnAttributeChangeData) const
{
	OnManaChanged.Broadcast(OnAttributeChangeData.NewValue);
}

void UOverlayWidgetController::MaxManaChanged(const FOnAttributeChangeData& OnAttributeChangeData) const
{
	OnMaxManaChanged.Broadcast(OnAttributeChangeData.NewValue);
}
