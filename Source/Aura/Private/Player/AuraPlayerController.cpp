// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/AuraPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Interaction/EnemyInterface.h"

AAuraPlayerController::AAuraPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (!IsLocalController()) return;

	check(MovementMappingContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	check(Subsystem);

	Subsystem->AddMappingContext(MovementMappingContext, 0);

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void AAuraPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!IsLocalController()) return;
	
	CursorTrace();
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (!IsLocalController()) return;

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	check(MoveAction);

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
}

void AAuraPlayerController::Move(const FInputActionValue& ActionValue)
{
	const FVector2d LocalInputVector = ActionValue.Get<FVector2d>();
	
	const FRotator YawRotation = FRotator(0, GetControlRotation().Yaw, 0);

	const FVector ForwardDir = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDir = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn())
	{
		ControlledPawn->AddMovementInput(ForwardDir, LocalInputVector.Y);
		ControlledPawn->AddMovementInput(RightDir, LocalInputVector.X);
	}
}

void AAuraPlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Vehicle, false, CursorHit);

	if (!CursorHit.bBlockingHit) return;

	LastActor = ThisActor;
	ThisActor = CursorHit.GetActor();

	/**
	 * Scenario 1: Both LastActor and ThisActor are null
	 *	- Do Nothing
	 * Scenario 2: LastActor is null, but This Actor is not
	 *	- Highlight ThisActor
	 * Scenario 3: LastActor and ThisActor are valid and different
	 *	- Highlight ThisActor and unhighlight LastActor
	 * Scenario 4: LastActor and This Actor are both valid and the same
	 *	- Do nothing
	 *	Scenario 5: LastActor is valid and ThisActor is null
	 *	- Unhighlight last actor
	 */

	if (LastActor == nullptr)
	{
		if (ThisActor != nullptr)
		{
			//Scenario 2
			ThisActor->HighlightActor();
		}

		//Scenario 1 Do Nothing
		return;
	}
	
	if (ThisActor == nullptr)
	{
		//Scenario 5
		LastActor->UnHighlightActor();
		return;
	}

	if (ThisActor == LastActor)
	{
		//Scenario 4 Do Nothing
		return;
	}

	//Scenario 3
	LastActor->UnHighlightActor();
	ThisActor->HighlightActor();
}
