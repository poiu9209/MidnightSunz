// Fill out your copyright notice in the Description page of Project Settings.


#include "msCharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "AbilitySystemComponent.h"
#include "MidnightSunz/MidnightSunz.h"
#include "MidnightSunz/AbilitySystem/msAbilitySystemComponent.h"

AmsCharacterBase::AmsCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECollisionResponse::ECR_Ignore);
	GetCapsuleComponent()->SetGenerateOverlapEvents(false);

	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECollisionResponse::ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_Projectile, ECollisionResponse::ECR_Overlap);
	GetMesh()->SetGenerateOverlapEvents(true);
}

UAbilitySystemComponent* AmsCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAttributeSet* AmsCharacterBase::GetAttributeSet() const
{
	return AttributeSet;
}

FVector AmsCharacterBase::GetSpawnProjectileLocation()
{
	return GetMesh()->GetSocketLocation(ProjectileSpawnSocketName);
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
	// ���� Init ���ش�.
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

void AmsCharacterBase::AddCharacterAbilities()
{
	if (!HasAuthority())
	{
		return;
	}

	if (UmsAbilitySystemComponent* ASC = Cast<UmsAbilitySystemComponent>(AbilitySystemComponent))
	{
		ASC->AddCharacterAbilities(StartupAbilities);
	}
}
