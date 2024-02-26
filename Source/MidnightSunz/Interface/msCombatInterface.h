// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "msCombatInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType)
class UmsCombatInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 *
 */
class MIDNIGHTSUNZ_API ImsCombatInterface
{
	GENERATED_BODY()

public:
	virtual FVector GetSpawnProjectileLocation();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void UpdateFacingTarget(const FVector& Target);

	UFUNCTION(BlueprintImplementableEvent)
	void ShowDamageText(const float Damage);
};
