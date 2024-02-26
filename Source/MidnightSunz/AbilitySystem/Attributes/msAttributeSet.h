// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "msAttributeSet.generated.h"


#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

USTRUCT(BlueprintType)
struct FEffectProperties
{
	GENERATED_BODY()

	FGameplayEffectContextHandle EffectContextHandle;

	UPROPERTY()
	UAbilitySystemComponent* SourceASC = nullptr;

	UPROPERTY()
	AActor* SourceAvataActor = nullptr;

	UPROPERTY()
	AController* SourceController = nullptr;

	UPROPERTY()
	ACharacter* SourceCharacter = nullptr;

	UPROPERTY()
	UAbilitySystemComponent* TargetASC = nullptr;

	UPROPERTY()
	AActor* TargetAvataActor = nullptr;

	UPROPERTY()
	AController* TargetController = nullptr;

	UPROPERTY()
	ACharacter* TargetCharacter = nullptr;
};

/**
 *
 */
UCLASS()
class MIDNIGHTSUNZ_API UmsAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UmsAttributeSet();
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

	ATTRIBUTE_ACCESSORS(UmsAttributeSet, Health);
	ATTRIBUTE_ACCESSORS(UmsAttributeSet, MaxHealth);
	ATTRIBUTE_ACCESSORS(UmsAttributeSet, Armor);
	ATTRIBUTE_ACCESSORS(UmsAttributeSet, CriticalHitChance);
	ATTRIBUTE_ACCESSORS(UmsAttributeSet, CriticalHitDamage);
	ATTRIBUTE_ACCESSORS(UmsAttributeSet, Damage);

protected:
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_Armor(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_CriticalHitChance(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_CriticalHitDamage(const FGameplayAttributeData& OldValue);

private:
	void ClampAttribute(const FGameplayAttribute& Attribute, float& NewValue) const;
	void ExtractProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& OutProperties) const;
	void ShowDamageText(const FEffectProperties& Properties, float DamageAmount);

private:
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "Vital Attributes", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Health;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "Vital Attributes", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxHealth;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Armor, Category = "Combat Attributes", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Armor;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalHitChance, Category = "Combat Attributes", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData CriticalHitChance;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalHitDamage, Category = "Combat Attributes", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData CriticalHitDamage;

	// -------------------------------------------------------------------
	//	Meta Attribute (please keep attributes that aren't 'stateful' below 
	// -------------------------------------------------------------------

	UPROPERTY(BlueprintReadOnly, Category = "Meta Attributes", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Damage;
};
