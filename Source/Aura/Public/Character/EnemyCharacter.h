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

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Level = 1;
	
public:

	AEnemyCharacter();

	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;

	virtual void BeginPlay() override;

	//Combat interface
	virtual int32 GetPlayerLevel() override;
	//End combat interface

protected:

	virtual void InitAbilityActorInfo() override;
	
};
