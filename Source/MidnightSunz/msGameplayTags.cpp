// Fill out your copyright notice in the Description page of Project Settings.


#include "msGameplayTags.h"
#include "GameplayTagsManager.h"

FmsGameplayTags FmsGameplayTags::GameplayTags;

void FmsGameplayTags::InitializeNativeGameplayTags()
{
	GameplayTags.Attributes_Combat_Armor = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Combat.Armor"), FString("Damage reduction"));
	GameplayTags.Attributes_Combat_CriticalHitChance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Combat.CriticalHitChance"), FString("CriticalHitChance"));
	GameplayTags.Attributes_Combat_CriticalHitDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Combat.CriticalHitDamage"), FString("CriticalHitDamage"));

	GameplayTags.InputTag_LMB = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.LMB"), FString("Input Tag for Left Mouse Button"));
	GameplayTags.InputTag_RMB = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.RMB"), FString("Input Tag for Right Mouse Button"));
	GameplayTags.InputTag_Space = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Space"), FString("Input Tag for Space key"));
	GameplayTags.InputTag_Shift = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Shift"), FString("Input Tag for Shift Key"));
	GameplayTags.InputTag_E = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.E"), FString("Input Tag for E Key"));
	GameplayTags.InputTag_Q = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Q"), FString("Input Tag for Q Key"));

	GameplayTags.Damage = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage"), FString("Damage"));
}
