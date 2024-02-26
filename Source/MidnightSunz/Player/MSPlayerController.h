// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "GameplayTagContainer.h"
#include "msPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
class UmsInputConfig;
class UmsAbilitySystemComponent;

/**
 *
 */
UCLASS()
class MIDNIGHTSUNZ_API AmsPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UFUNCTION(Client, Reliable)
	void ShowDamageNumber(ACharacter* TargetCharacter, float DamageAmount);

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	void Move(const FInputActionValue& InputActionValue);
	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);

private:
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UmsInputConfig> InputConfig;

	UPROPERTY()
	TObjectPtr<UmsAbilitySystemComponent> AbilitySystemComponent;

	UmsAbilitySystemComponent* GetAbilitySystemComponent();
};
