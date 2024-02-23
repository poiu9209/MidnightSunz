// Fill out your copyright notice in the Description page of Project Settings.


#include "msCharacterBase.h"

AmsCharacterBase::AmsCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AmsCharacterBase::BeginPlay()
{
	Super::BeginPlay();

}

void AmsCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

