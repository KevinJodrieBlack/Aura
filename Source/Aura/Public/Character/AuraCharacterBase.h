#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "AuraCharacterBase.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;

UCLASS(abstract)
class AURA_API AAuraCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AAuraCharacterBase();

protected:

	UPROPERTY(EditAnywhere, Category = Weapon)
	TObjectPtr<USkeletalMeshComponent> Weapon;

	UPROPERTY(BlueprintReadWrite, Category = AbilitySystem)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(BlueprintReadWrite, Category= Attributes)
	TObjectPtr<UAttributeSet> AttributeSet;

public:

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const; 
	
protected:
	virtual void BeginPlay() override;

	virtual void InitAbilityActorInfo();

};
