// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "msOverlayWidget.generated.h"

/**
 *
 */
UCLASS()
class MIDNIGHTSUNZ_API UmsOverlayWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintImplementableEvent)
	void K2_UpdateHealth(float NewHealth);

	UFUNCTION(BlueprintImplementableEvent)
	void K2_UpdateMaxHealth(float NewMaxHealth);
};
