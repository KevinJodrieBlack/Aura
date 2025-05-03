// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AuraAttributeSet.h"

#include "GameplayEffectExtension.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"

UAuraAttributeSet::UAuraAttributeSet()
{
	InitMaxHealth(100.f);
	InitHealth(50.f);
	InitMaxMana(50.f);
	InitMana(25.f);
}

void UAuraAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//Register attributes for replication
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
}

void UAuraAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0, GetMaxHealth());
	}
	else if (Attribute == GetManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0, GetMaxMana());
	}
}

void UAuraAttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& EffectProps)
{
	EffectProps.ContextHandle = Data.EffectSpec.GetContext();
	
	EffectProps.SourceASC = EffectProps.ContextHandle.GetOriginalInstigatorAbilitySystemComponent();

	if (IsValid(EffectProps.SourceASC) && EffectProps.SourceASC->AbilityActorInfo.IsValid() && EffectProps.SourceASC->AbilityActorInfo->AvatarActor.IsValid())
	{
		EffectProps.SourceAvatarActor = EffectProps.SourceASC->AbilityActorInfo->AvatarActor.Get();
		EffectProps.SourceController = EffectProps.SourceASC->AbilityActorInfo->PlayerController.Get();

		if (EffectProps.SourceController == nullptr && EffectProps.SourceAvatarActor != nullptr)
		{
			if (const APawn* Pawn = Cast<APawn>(EffectProps.SourceAvatarActor))
			{
				EffectProps.SourceController = Pawn->GetController();
			}
		}
		if (EffectProps.SourceController)
		{
			EffectProps.SourceCharacter = Cast<ACharacter>(EffectProps.SourceController->GetPawn());
		}
	}

	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		EffectProps.TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		EffectProps.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		EffectProps.TargetCharacter = Cast<ACharacter>(EffectProps.TargetController->GetPawn());
		EffectProps.TargetASC = Data.Target.AbilityActorInfo->AbilitySystemComponent.Get();
	}
}

void UAuraAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	FEffectProperties EffectProps;
	SetEffectProperties(Data, EffectProps);
}

void UAuraAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Health, OldHealth);
}

void UAuraAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxHealth, OldMaxHealth);
}

void UAuraAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Mana, OldMana);
}

void UAuraAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxMana, OldMaxMana);
}


