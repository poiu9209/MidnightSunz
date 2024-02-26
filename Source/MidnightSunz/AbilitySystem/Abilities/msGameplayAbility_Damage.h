// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "msGameplayAbility.h"
#include "msGameplayAbility_Damage.generated.h"

/**
 *
 */
UCLASS()
class MIDNIGHTSUNZ_API UmsGameplayAbility_Damage : public UmsGameplayAbility
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> DamageEffectClass;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	TMap<FGameplayTag, FScalableFloat> DamageTypes;
};
