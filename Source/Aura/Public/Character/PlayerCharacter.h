// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AuraCharacterBase.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class AURA_API APlayerCharacter : public AAuraCharacterBase
{
	GENERATED_BODY()

public:
	APlayerCharacter();

public:

	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

protected:
	virtual void BeginPlay() override;

	virtual void InitAbilityActorInfo() override;
};
