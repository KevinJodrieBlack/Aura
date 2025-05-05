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
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetHealthAttribute())
		.AddLambda([this] (const FOnAttributeChangeData& OnAttributeChangeData)
	{
		OnHealthChanged.Broadcast(OnAttributeChangeData.NewValue);
	});
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxHealthAttribute())
		.AddLambda([this] (const FOnAttributeChangeData& OnAttributeChangeData)
	{
		OnMaxHealthChanged.Broadcast(OnAttributeChangeData.NewValue);
	});
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetManaAttribute())
		.AddLambda([this] (const FOnAttributeChangeData& OnAttributeChangeData)
	{
		OnManaChanged.Broadcast(OnAttributeChangeData.NewValue);
	});
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxManaAttribute())
		.AddLambda([this] (const FOnAttributeChangeData& OnAttributeChangeData)
	{
		OnMaxManaChanged.Broadcast(OnAttributeChangeData.NewValue);
	});
	
	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->AssetTags.AddLambda([this] (const FGameplayTagContainer& TagContainer)
	{
		UE_LOG(LogTemp, Warning, TEXT("Effect Applied"))
		for (const FGameplayTag& Tag : TagContainer)
		{
			if (Tag.MatchesTag(FGameplayTag::RequestGameplayTag(FName("Message"))))
			{
				FUIWidgetRow* WidgetRow = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag);

				if (!WidgetRow)
				{
					UE_LOG(LogTemp, Warning, TEXT("Can't find message data row for %s"), *Tag.ToString())
					return;
				}
				
				MessageWidgetRowDelegate.Broadcast(*WidgetRow);
			}
		}
	});
}
