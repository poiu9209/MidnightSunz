// Fill out your copyright notice in the Description page of Project Settings.


#include "msOverlayWidget.h"
#include "MidnightSunz/Player/msPlayerController.h"
#include "MidnightSunz/Player/msPlayerState.h"
#include "MidnightSunz/AbilitySystem/Attributes/msAttributeSet.h"
#include "AbilitySystemComponent.h"

void UmsOverlayWidget::NativeConstruct()
{
	Super::NativeConstruct();

	auto PC = GetOwningPlayer<AmsPlayerController>();
	if (!PC)
	{
		return;
	}

	auto PS = PC->GetPlayerState<AmsPlayerState>();
	if (!PS)
	{
		return;
	}

	auto ASC = PS->GetAbilitySystemComponent();
	auto AS = CastChecked<UmsAttributeSet>(PS->GetAttributeSet());
	if (!ASC || !AS)
	{
		return;
	}

	ASC->GetGameplayAttributeValueChangeDelegate(AS->GetHealthAttribute()).AddLambda([this](const FOnAttributeChangeData& Data)
		{
			K2_UpdateHealth(Data.NewValue);
		});
	ASC->GetGameplayAttributeValueChangeDelegate(AS->GetMaxHealthAttribute()).AddLambda([this](const FOnAttributeChangeData& Data)
		{
			K2_UpdateMaxHealth(Data.NewValue);
		});

	// Init 
	const float Health = AS->GetHealth();
	const float MaxHealth = AS->GetMaxHealth();
	K2_UpdateHealth(Health);
	K2_UpdateMaxHealth(MaxHealth);
}
