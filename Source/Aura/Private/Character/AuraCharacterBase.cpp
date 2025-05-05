#include "Aura/Public/Character/AuraCharacterBase.h"

#include "AbilitySystemComponent.h"


AAuraCharacterBase::AAuraCharacterBase()
{

	PrimaryActorTick.bCanEverTick = false;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

UAbilitySystemComponent* AAuraCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAttributeSet* AAuraCharacterBase::GetAttributeSet() const
{
	return AttributeSet;
}

void AAuraCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAuraCharacterBase::InitAbilityActorInfo()
{
}

void AAuraCharacterBase::InitPrimaryAttributes() const
{
	checkf(DefaultPrimaryAttributes, TEXT("Missing primary attribute effect for %s"), *GetName());
	checkf(GetAbilitySystemComponent(), TEXT("Missing ability system component for %s"), *GetName());
	
	if (UAbilitySystemComponent* ASC = GetAbilitySystemComponent())
	{
		const FGameplayEffectContextHandle ContextHandle = ASC->MakeEffectContext();
		const FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(DefaultPrimaryAttributes, 1, ContextHandle);
		ASC->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), ASC);
	}
	
}

