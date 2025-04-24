// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AuraCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class AURA_API AEnemyCharacter : public AAuraCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly)
	bool bIsHighlighted = false;
	
public:

	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
	
};
