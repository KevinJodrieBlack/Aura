// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AuraEffectActor.generated.h"

class UGameplayEffect;
class USphereComponent;

UENUM(BlueprintType)
enum class EEffectApplicationPolicy
{
	ApplyOnOverlap,
	ApplyOnEndOverlap,
	DoNotApply
};

UENUM(BlueprintType)
enum class EEffectRemovalPolicy
{
	RemoveOnEndOverlap,
	DoNotRemove
};

UCLASS()
class AURA_API AAuraEffectActor : public AActor
{
	GENERATED_BODY()

public:
	
	AAuraEffectActor();

protected:

	UPROPERTY(EditAnywhere)
	float EffectLevel = 1.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bIsDestroyedOnOverlap = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<TSubclassOf<UGameplayEffect>> InstantEffects;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EEffectApplicationPolicy InstantEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<TSubclassOf<UGameplayEffect>> DurationEffects;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EEffectApplicationPolicy DurationEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<TSubclassOf<UGameplayEffect>> InfiniteEffects;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EEffectApplicationPolicy InfiniteEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EEffectRemovalPolicy InfiniteEffectRemovalPolicy = EEffectRemovalPolicy::RemoveOnEndOverlap;

private:

	UPROPERTY()
	TArray<AActor*> AffectedActors;

protected:

	UFUNCTION(BlueprintCallable)
	void TryApplyGameplayEffectToActor(AActor* Actor, TSubclassOf<UGameplayEffect> Effect);

	UFUNCTION()
	void TryRemoveInfiniteEffect(AActor* Actor, TSubclassOf<UGameplayEffect> Effect);

	UFUNCTION(BlueprintCallable)
	void OnOverlap(AActor* Actor);

	UFUNCTION(BlueprintCallable)
	void OnEndOverlap(AActor* Actor);
};
