// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AuraPlayerController.generated.h"

class UInputMappingContext;
/**
 * 
 */
UCLASS()
class AURA_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()

private:

	UPROPERTY(EditDefaultsOnly, Category = Input)
	TObjectPtr<UInputMappingContext> MovementMappingContext;

public:
	AAuraPlayerController();
	
protected:

	virtual void BeginPlay() override;
};
