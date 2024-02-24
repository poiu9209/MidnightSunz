// Fill out your copyright notice in the Description page of Project Settings.


#include "msCharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AbilitySystemComponent.h"

AmsCharacterBase::AmsCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;
}

UAbilitySystemComponent* AmsCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAttributeSet* AmsCharacterBase::GetAttributeSet() const
{
	return AttributeSet;
}

void AmsCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	GetCharacterMovement()->MaxWalkSpeed = DefaultWalkSpped;
}

void AmsCharacterBase::InitAbilityActorInfo()
{
	// Player -> PlayerStaet
	// Enemy -> Enemy  
	// 따로 Init 해준다.
}

void AmsCharacterBase::InitializeDefaultAttributes() const
{
	ApplyEffectToSelf(DefaultVitaltAttributes, 1.f);
}

void AmsCharacterBase::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const
{
	check(IsValid(GetAbilitySystemComponent()));
	check(GameplayEffectClass);

	FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	ContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(GameplayEffectClass, Level, ContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), GetAbilitySystemComponent());
}
