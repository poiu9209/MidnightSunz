// Fill out your copyright notice in the Description page of Project Settings.


#include "msEnemy.h"
#include "MidnightSunz/AbilitySystem/msAbilitySystemComponent.h"
#include "MidnightSunz/AbilitySystem/Attributes/msAttributeSet.h"
#include "MidnightSunz/UI/Widgets/msUserWidget.h"
#include "Components/WidgetComponent.h"

AmsEnemy::AmsEnemy()
{
	AbilitySystemComponent = CreateDefaultSubobject<UmsAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<UmsAttributeSet>(TEXT("AttributeSet"));

	HealthBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBar"));
	HealthBar->SetupAttachment(GetRootComponent());
}

void AmsEnemy::Die()
{
	SetLifeSpan(LifeSpan);
	Super::Die();
}

void AmsEnemy::BeginPlay()
{
	Super::BeginPlay();
	InitAbilityActorInfo();
	if (HasAuthority())
	{
		InitializeDefaultAttributes();
	}

	if (UmsUserWidget* HealthBarWidget = Cast<UmsUserWidget>(HealthBar->GetUserWidgetObject()))
	{
		HealthBarWidget->SetWidgetController(this);
	}

	if (const UmsAttributeSet* AS = Cast<UmsAttributeSet>(AttributeSet))
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AS->GetHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnHealthChange.Broadcast(Data.NewValue);
			});

		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AS->GetMaxHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnMaxHealthChange.Broadcast(Data.NewValue);
			});

		OnHealthChange.Broadcast(AS->GetHealth());
		OnMaxHealthChange.Broadcast(AS->GetMaxHealth());
	}
}

void AmsEnemy::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
}
