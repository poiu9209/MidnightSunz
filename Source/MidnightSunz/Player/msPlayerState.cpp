// Fill out your copyright notice in the Description page of Project Settings.


#include "msPlayerState.h"
#include "MidnightSunz/AbilitySystem/msAbilitySystemComponent.h"
#include "MidnightSunz/AbilitySystem/Attributes/msAttributeSet.h"

AmsPlayerState::AmsPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UmsAbilitySystemComponent>(TEXT("AbilitySystemComponen"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UmsAttributeSet>(TEXT("AttributeSet"));

	// AbilitySystemComponent needs to be updated at a high frequency.
	NetUpdateFrequency = 100.0f;
}

UAbilitySystemComponent* AmsPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAttributeSet* AmsPlayerState::GetAttributeSet() const
{
	return AttributeSet;
}
