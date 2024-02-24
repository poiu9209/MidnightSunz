// Fill out your copyright notice in the Description page of Project Settings.


#include "msEnemy.h"
#include "MidnightSunz/AbilitySystem/msAbilitySystemComponent.h"
#include "MidnightSunz/AbilitySystem/Attributes/msAttributeSet.h"

AmsEnemy::AmsEnemy()
{
	AbilitySystemComponent = CreateDefaultSubobject<UmsAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<UmsAttributeSet>(TEXT("AttributeSet"));
}

void AmsEnemy::BeginPlay()
{
	Super::BeginPlay();
	InitAbilityActorInfo();
}

void AmsEnemy::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
}
