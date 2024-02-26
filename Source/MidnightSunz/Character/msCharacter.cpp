// Fill out your copyright notice in the Description page of Project Settings.


#include "msCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "AbilitySystemComponent.h"
#include "MidnightSunz/Player/msPlayerState.h"
#include "MidnightSunz/UI/HUD/msHUD.h"

AmsCharacter::AmsCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 500, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bInheritYaw = false;
	CameraBoom->TargetArmLength = 900.f;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
}

void AmsCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	InitAbilityActorInfo();
	AddCharacterAbilities();
}

void AmsCharacter::OnRep_PlayerState()
{
	InitAbilityActorInfo();
}

void AmsCharacter::InitAbilityActorInfo()
{
	AmsPlayerState* PS = GetPlayerState<AmsPlayerState>();
	check(PS);
	PS->GetAbilitySystemComponent()->InitAbilityActorInfo(PS, this);
	AbilitySystemComponent = PS->GetAbilitySystemComponent();
	AttributeSet = PS->GetAttributeSet();
	InitializeDefaultAttributes();

	if (auto PC = Cast<APlayerController>(GetController()))
	{
		if (AmsHUD* HUD = PC->GetHUD<AmsHUD>())
		{
			HUD->InitOverlayWidget();
		}
	}
}
