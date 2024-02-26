// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 * Native로 추가한 게임플레이 태그
 */

struct FmsGameplayTags
{
public:
	static FmsGameplayTags& Get() { return GameplayTags; }
	static void InitializeNativeGameplayTags();

	/* Combat Attribute */
	FGameplayTag Attributes_Combat_Armor;
	FGameplayTag Attributes_Combat_CriticalHitChance;
	FGameplayTag Attributes_Combat_CriticalHitDamage;

	/* Input */
	FGameplayTag InputTag_LMB;
	FGameplayTag InputTag_RMB;
	FGameplayTag InputTag_Shift;
	FGameplayTag InputTag_Space;
	FGameplayTag InputTag_E;
	FGameplayTag InputTag_Q;

	/* Dmage */
	FGameplayTag Damage;


private:
	static FmsGameplayTags GameplayTags;
};