// Fill out your copyright notice in the Description page of Project Settings.


#include "Cannon.h"
#include "Components\StaticMeshComponent.h"
#include "Components\ArrowComponent.h"
#include "TimerManager.h"
#include "Engine/Engine.h"


// Sets default values
ACannon::ACannon()
{
	PrimaryActorTick.bCanEverTick = false;

	CannonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CannonMesh"));
	RootComponent = CannonMesh;

	ProjectileSpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("ProjectileSpawnPoint"));
	ProjectileSpawnPoint->SetupAttachment(CannonMesh);
}

void ACannon::Fire()
{
	if (!bCanFire)
	{
		return;
	}

	if (CannonType == ECannonType::FireProjectile && NumberOfProjectiles == 0 || CannonType == ECannonType::FireTrace && NumberOfTraces == 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("Out of ammo")));
		return;
	}

	bCanFire = false;

	if (CannonType == ECannonType::FireProjectile)
	{
		NumberOfProjectiles--;
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, FString::Printf(TEXT("Number of projectile: %i"), NumberOfProjectiles));
	}
	else
	{
		NumberOfTraces--;
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, FString::Printf(TEXT("Number of traces: %i"), NumberOfTraces));
	}

	GetWorld()->GetTimerManager().SetTimer(ReloadTimer, this, &ACannon::Reload, ReloadTime, false);
}

void ACannon::FireSpecial()
{
	if (!bCanFire)
	{
		return;
	}

	bCanFire = false;

	if (CannonType == ECannonType::FireProjectile)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, FString::Printf(TEXT("Alternative fire projectile")));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, FString::Printf(TEXT("Alternative fire trace")));
	}

	GetWorld()->GetTimerManager().SetTimer(ReloadTimer, this, &ACannon::Reload, ReloadTime, false);
}

void ACannon::Reload()
{
	bCanFire = true;
}
