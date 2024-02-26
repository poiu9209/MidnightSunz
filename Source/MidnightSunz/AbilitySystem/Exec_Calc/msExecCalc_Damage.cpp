// Fill out your copyright notice in the Description page of Project Settings.


#include "msExecCalc_Damage.h"
#include "MidnightSunz/msGameplayTags.h"
#include "MidnightSunz/AbilitySystem/Attributes/msAttributeSet.h"

UmsExecCalc_Damage::UmsExecCalc_Damage()
{
}

void UmsExecCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	const UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();

	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();
	const FmsGameplayTags& Tags = FmsGameplayTags::Get();

	float Damage = Spec.GetSetByCallerMagnitude(Tags.Damage);

	const FGameplayModifierEvaluatedData EvaluatedData(UmsAttributeSet::GetDamageAttribute(), EGameplayModOp::Additive, Damage);
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
}
