// Fill out your copyright notice in the Description page of Project Settings.


#include "msAnimInstance.h"
#include "msCharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"

void UmsAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Character = Cast<AmsCharacterBase>(TryGetPawnOwner());
}

void UmsAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	Character = Character ? Character : Cast<AmsCharacterBase>(TryGetPawnOwner());
	if (!Character)
	{
		return;
	}

	FVector Velocity = Character->GetVelocity();
	Speed = Velocity.Size2D();

	bShouldMove = Character->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.f && Speed > 3.f;
}
