// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "AuraAttributeSet.generated.h"

USTRUCT()
struct FEffectProperties
{
	GENERATED_BODY()

	UPROPERTY()
	FGameplayEffectContextHandle ContextHandle;
	
	//Source info
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> SourceASC = nullptr;
	UPROPERTY()
	TObjectPtr<AActor> SourceAvatarActor = nullptr;
	UPROPERTY()
	TObjectPtr<AController> SourceController = nullptr;
	UPROPERTY()
	TObjectPtr<ACharacter> SourceCharacter = nullptr;

	//Target info
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> TargetASC = nullptr;
	UPROPERTY()
	TObjectPtr<AActor> TargetAvatarActor = nullptr;
	UPROPERTY()
	TObjectPtr<AController> TargetController = nullptr;
	UPROPERTY()
	TObjectPtr<ACharacter> TargetCharacter = nullptr;
};

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class AURA_API UAuraAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:

	UAuraAttributeSet();

	//Vital Attributes
	UPROPERTY(BlueprintReadOnly, Category = Health, ReplicatedUsing=OnRep_Health)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Health)

	UPROPERTY(BlueprintReadOnly, Category = Health, ReplicatedUsing=OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxHealth)

	UPROPERTY(BlueprintReadOnly, Category = Mana, ReplicatedUsing=OnRep_Mana)
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Mana)

	UPROPERTY(BlueprintReadOnly, Category = Mana, ReplicatedUsing=OnRep_MaxMana)
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxMana)

public:

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

private:

	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth) const;

	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;

	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldMana) const;

	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;

	static void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& EffectProps);
};
