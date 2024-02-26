// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayEffectTypes.h"
#include "msProjectile.generated.h"

class UProjectileMovementComponent;
class USphereComponent;
class UNiagaraComponent;
class UNiagaraSystem;

UCLASS()
class MIDNIGHTSUNZ_API AmsProjectile : public AActor
{
	GENERATED_BODY()

public:
	AmsProjectile();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = "true"))
	FGameplayEffectSpecHandle DamageEffectSpecHandle;

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> Sphere;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UNiagaraSystem> FlashEffect;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UNiagaraSystem> ImpactEffect;

	UPROPERTY(EditAnywhere)
	float LifeSpan = 10.f;
public:

};
