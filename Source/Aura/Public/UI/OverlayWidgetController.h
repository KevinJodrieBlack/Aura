// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WidgetController.h"
#include "OverlayWidgetController.generated.h"

class UAuraUserWidget;

USTRUCT(BlueprintType)
struct FUIWidgetRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag MessageTag = FGameplayTag();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText MessageText = FText();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UAuraUserWidget> MessageWidget = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UTexture2D> Image = nullptr;
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChanged, float, NewValue);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMessageRowWidgetSignature, FUIWidgetRow, Row);

UCLASS(Blueprintable, BlueprintType)
class AURA_API UOverlayWidgetController : public UWidgetController
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChanged OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChanged OnMaxHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChanged OnManaChanged;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChanged OnMaxManaChanged;

	UPROPERTY(BlueprintAssignable)
	FMessageRowWidgetSignature MessageWidgetRowDelegate;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UDataTable> MessageWidgetDataTable;

public:

	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;

protected:

	template<typename T>
	T* GetDataTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag);
	
	
};

template <typename T>
T* UOverlayWidgetController::GetDataTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag)
{
	return DataTable->FindRow<T>(Tag.GetTagName(), TEXT(""));
}
