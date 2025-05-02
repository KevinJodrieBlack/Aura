// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/AuraEffectActor.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffect.h"

AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>("Root"));
}

void AAuraEffectActor::TryApplyGameplayEffectToActor(AActor* Actor, TSubclassOf<UGameplayEffect> Effect)
{
	if (!IsValid(Effect))
	{
		return;
	}

	if (UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Actor))
	{
		FGameplayEffectContextHandle ContextHandle = ASC->MakeEffectContext();
		ContextHandle.AddSourceObject(this);
		const FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(Effect, 1, ContextHandle);
		ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());

		if (SpecHandle.Data.Get()->Def.Get()->DurationPolicy == EGameplayEffectDurationType::Infinite
			&& InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
		{
			AffectedActors.Add(Actor);
		}

		if (bIsDestroyedOnOverlap)
		{
			Destroy();
		}
	}
}

void AAuraEffectActor::TryRemoveInfiniteEffect(AActor* Actor, TSubclassOf<UGameplayEffect> Effect)
{
	if (!IsValid(Effect))
	{
		return;
	}

	if (UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Actor))
	{
		ASC->RemoveActiveGameplayEffectBySourceEffect(Effect, ASC, 1);
	}
}

void AAuraEffectActor::OnOverlap(AActor* Actor)
{
	if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		for (const auto& Effect : InstantEffects)
		{
			TryApplyGameplayEffectToActor(Actor, Effect);
		}
	}

	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		for (const auto& Effect : DurationEffects)
		{
			TryApplyGameplayEffectToActor(Actor, Effect);
		}
	}

	if (InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		for (const auto& Effect : InfiniteEffects)
		{
			TryApplyGameplayEffectToActor(Actor, Effect);
		}
	}
}

void AAuraEffectActor::OnEndOverlap(AActor* Actor)
{
	if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		for (const auto& Effect : InstantEffects)
		{
			TryApplyGameplayEffectToActor(Actor, Effect);
		}
	}

	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		for (const auto& Effect : DurationEffects)
		{
			TryApplyGameplayEffectToActor(Actor, Effect);
		}
	}

	if (InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		for (const auto& Effect : InfiniteEffects)
		{
			TryApplyGameplayEffectToActor(Actor, Effect);
		}
	}

	if (InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		if (AffectedActors.Contains(Actor))
		{
			for (const auto& Effect : InfiniteEffects)
			{
				TryRemoveInfiniteEffect(Actor, Effect);
			}
		}
	}
}

