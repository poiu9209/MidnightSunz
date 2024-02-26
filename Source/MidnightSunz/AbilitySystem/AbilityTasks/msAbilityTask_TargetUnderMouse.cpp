// Fill out your copyright notice in the Description page of Project Settings.


#include "msAbilityTask_TargetUnderMouse.h"
#include "AbilitySystemComponent.h"

UmsAbilityTask_TargetUnderMouse* UmsAbilityTask_TargetUnderMouse::CreateTargetUnderMouse(UGameplayAbility* OwningAbility)
{
	UmsAbilityTask_TargetUnderMouse* Obj = NewAbilityTask<UmsAbilityTask_TargetUnderMouse>(OwningAbility);
	return Obj;
}

void UmsAbilityTask_TargetUnderMouse::Activate()
{
	Super::Activate();

	const bool bIsLocallyControlled = Ability->GetCurrentActorInfo()->IsLocallyControlled();
	if (bIsLocallyControlled)
	{
		SendMouseCursorData();
	}
	else
	{
		const FGameplayAbilitySpecHandle SpecHandle = GetAbilitySpecHandle();
		const FPredictionKey ActivationPredictionKey = GetActivationPredictionKey();
		AbilitySystemComponent.Get()->AbilityTargetDataSetDelegate(SpecHandle, ActivationPredictionKey).AddUObject(this, &ThisClass::OnTargetDataReplicatedCallback);
		// 바인딩되기전에 델리게이트가 이미 브로드캐스트 되었다면 다시 브로드캐스트 하게 해줌.
		const bool bCalledDelegate = AbilitySystemComponent.Get()->CallReplicatedTargetDataDelegatesIfSet(SpecHandle, ActivationPredictionKey);
		if (!bCalledDelegate)
		{
			SetWaitingOnRemotePlayerData();
		}
	}
}

void UmsAbilityTask_TargetUnderMouse::SendMouseCursorData()
{
	FScopedPredictionWindow ScopePrediction(AbilitySystemComponent.Get());

	APlayerController* PC = Ability->GetCurrentActorInfo()->PlayerController.Get();
	FHitResult CursorHit;
	PC->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, CursorHit);

	FGameplayAbilityTargetDataHandle DataHandle;
	FGameplayAbilityTargetData_SingleTargetHit* Data = new FGameplayAbilityTargetData_SingleTargetHit();
	Data->HitResult = CursorHit;
	DataHandle.Add(Data);

	AbilitySystemComponent->ServerSetReplicatedTargetData(GetAbilitySpecHandle(), GetActivationPredictionKey(), DataHandle, FGameplayTag(), AbilitySystemComponent->ScopedPredictionKey);
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		ValidData.Broadcast(DataHandle);
	}
}

void UmsAbilityTask_TargetUnderMouse::OnTargetDataReplicatedCallback(const FGameplayAbilityTargetDataHandle& DataHandle, FGameplayTag ActivationTag)
{
	// 타겟데이터 컨슘, 캐시한거 지워도된다라고 알려줘야함
	AbilitySystemComponent->ConsumeClientReplicatedTargetData(GetAbilitySpecHandle(), GetActivationPredictionKey());
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		ValidData.Broadcast(DataHandle);
	}
}
