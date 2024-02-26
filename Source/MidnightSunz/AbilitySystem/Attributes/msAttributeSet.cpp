// Fill out your copyright notice in the Description page of Project Settings.


#include "msAttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "GameplayEffectExtension.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GameFramework/Character.h"
#include "MidnightSunz/msGameplayTags.h"
#include "MidnightSunz/Player/msPlayerController.h"

UmsAttributeSet::UmsAttributeSet()
{
	const FmsGameplayTags& GameplayTags = FmsGameplayTags::Get();


}

void UmsAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UmsAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UmsAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UmsAttributeSet, Armor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UmsAttributeSet, CriticalHitChance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UmsAttributeSet, CriticalHitDamage, COND_None, REPNOTIFY_Always);
}

void UmsAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	ClampAttribute(Attribute, NewValue);
}

void UmsAttributeSet::ClampAttribute(const FGameplayAttribute& Attribute, float& NewValue) const
{
	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	}
	else if (Attribute == GetMaxHealthAttribute())
	{
		NewValue = FMath::Max(NewValue, 1.f);
	}
}

void UmsAttributeSet::ExtractProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& OutProperties) const
{
	OutProperties.EffectContextHandle = Data.EffectSpec.GetContext();
	OutProperties.SourceASC = OutProperties.EffectContextHandle.GetInstigatorAbilitySystemComponent();

	if (IsValid(OutProperties.SourceASC) && OutProperties.SourceASC->AbilityActorInfo.IsValid() && OutProperties.SourceASC->AbilityActorInfo->AvatarActor.IsValid())
	{
		OutProperties.SourceAvataActor = OutProperties.SourceASC->AbilityActorInfo->AvatarActor.Get();
		OutProperties.SourceController = OutProperties.SourceASC->AbilityActorInfo->PlayerController.Get();
		if (!OutProperties.SourceController && OutProperties.SourceAvataActor)
		{
			if (const APawn* Pawn = Cast<APawn>(OutProperties.SourceAvataActor))
			{
				OutProperties.SourceController = Pawn->GetController();
			}
		}
		if (OutProperties.SourceController)
		{
			OutProperties.SourceCharacter = Cast<ACharacter>(OutProperties.SourceController->GetPawn());
		}
	}

	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		OutProperties.TargetAvataActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		OutProperties.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		OutProperties.TargetCharacter = Cast<ACharacter>(OutProperties.TargetAvataActor);
		OutProperties.TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OutProperties.TargetAvataActor);
	}
}

void UmsAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	FEffectProperties Properties;
	ExtractProperties(Data, Properties);

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
	}
	else if (Data.EvaluatedData.Attribute == GetDamageAttribute())
	{
		const float LocalDmamage = GetDamage();
		SetDamage(0.f);
		if (LocalDmamage > 0.f)
		{
			const float NewHealth = GetHealth() - LocalDmamage;
			SetHealth(FMath::Clamp(NewHealth, 0.f, GetMaxHealth()));

			const bool bDie = NewHealth <= 0.f;
			if (bDie)
			{
				//TODO! 
			}
			else
			{
				//TODO!
			}

			ShowDamageText(Properties, LocalDmamage);
		}
	}
}

void UmsAttributeSet::ShowDamageText(const FEffectProperties& Properties, float DamageAmount)
{
	if (Properties.SourceCharacter == Properties.TargetCharacter)
	{
		return;
	}

	if (auto PC = Cast<AmsPlayerController>(Properties.SourceController))
	{
		PC->ShowDamageNumber(Properties.TargetCharacter, DamageAmount);
	}
}

void UmsAttributeSet::OnRep_Health(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UmsAttributeSet, Health, OldValue);
}

void UmsAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UmsAttributeSet, MaxHealth, OldValue);
}

void UmsAttributeSet::OnRep_Armor(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UmsAttributeSet, Armor, OldValue);
}

void UmsAttributeSet::OnRep_CriticalHitChance(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UmsAttributeSet, CriticalHitChance, OldValue);
}

void UmsAttributeSet::OnRep_CriticalHitDamage(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UmsAttributeSet, CriticalHitDamage, OldValue);
}
