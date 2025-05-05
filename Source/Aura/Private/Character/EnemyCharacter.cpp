// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EnemyCharacter.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"


AEnemyCharacter::AEnemyCharacter()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("Ability System Component");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("Attribute Set");
}

void AEnemyCharacter::HighlightActor()
{
	check(GetMesh());
	GetMesh()->SetRenderCustomDepth(true);

	if (Weapon != nullptr)
	{
		Weapon->SetRenderCustomDepth(true);
	}
}

void AEnemyCharacter::UnHighlightActor()
{
	check(GetMesh());
	GetMesh()->SetRenderCustomDepth(false);

	if (Weapon != nullptr)
	{
		Weapon->SetRenderCustomDepth(false);
	}
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	check(AbilitySystemComponent);

	InitAbilityActorInfo();
}

int32 AEnemyCharacter::GetPlayerLevel()
{
	return Level;
}

void AEnemyCharacter::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);

	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();
}
