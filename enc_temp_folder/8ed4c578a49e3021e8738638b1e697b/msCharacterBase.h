// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "MidnightSunz/Interface/msCombatInterface.h"
#include "msCharacterBase.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;
class UGameplayEffect;
class UGameplayAbility;
class UWidgetComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChangedSignature, float, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCharacterEventSignature);

UCLASS()
class MIDNIGHTSUNZ_API AmsCharacterBase : public ACharacter, public IAbilitySystemInterface, public ImsCombatInterface
{
	GENERATED_BODY()

public:
	AmsCharacterBase();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const;

	// begin ImsCombatInterface
	virtual FVector GetSpawnProjectileLocation() override;
	virtual void Die() override;
	// end ImsCombatInterface

	UFUNCTION(NetMulticast, Reliable)
	virtual void MulticastHandleDeath();

protected:
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo();
	virtual void InitializeDefaultAttributes() const;

	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const;

	void AddCharacterAbilities();

	void Dissolve();

	UFUNCTION(BlueprintImplementableEvent)
	void StartDissolveTimeline(UMaterialInstanceDynamic* DynamicMaterialInstance);

	UFUNCTION(BlueprintImplementableEvent)
	void StartWeaponDissolveTimeline(UMaterialInstanceDynamic* DynamicMaterialInstance);

protected:
	UPROPERTY(EditAnywhere)
	float DefaultWalkSpped = 350.f;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	UAttributeSet* AttributeSet;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attributes")
	TSubclassOf<UGameplayEffect> DefaultVitaltAttributes;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> HealthBar;

	UPROPERTY(BlueprintAssignable, Category = "Attributes")
	FOnAttributeChangedSignature OnHealthChange;

	UPROPERTY(BlueprintAssignable, Category = "Attributes")
	FOnAttributeChangedSignature OnMaxHealthChange;

	UPROPERTY(BlueprintAssignable, Category = "Combat")
	FOnCharacterEventSignature OnDie;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UAnimMontage> DeathMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UMaterialInstance> DissolveMaterialnstance;

private:
	UPROPERTY(EditAnywhere, Category = "Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;

	UPROPERTY(EditAnywhere, Category = "Combat")
	FName ProjectileSpawnSocketName;
};
