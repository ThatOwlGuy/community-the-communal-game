// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "ProjectileType.h"

#include "GameFramework/Character.h"

#include "Weapon.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	if (TypeClass.Get())
	{
		Type = NewObject<UProjectileType>(this, TypeClass.Get(), *TypeClass.Get()->GetName(), RF_Public, TypeClass.Get()->GetDefaultObject(false));
	}
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool AWeapon::Fire(AActor* firer)
{
	if (firer->GetLocalRole() == ROLE_Authority)
	{
		Fire_Server(firer);
		return true;
	} else if (firer->GetLocalRole() == ROLE_AutonomousProxy)
	{
		OnFire(firer);
		return true;
	}

	return false;
}

bool AWeapon::Fire_Server_Validate(AActor* firer)
{
	return true;
}

void AWeapon::Fire_Server_Implementation(AActor* firer)
{
	FVector direction = this->GetActorRightVector();
	FVector location = this->GetActorLocation() + this->GetActorRotation().RotateVector(this->MuzzlePoint);

	AProjectile* projectile = AProjectile::Create(this, firer, location, direction);
	if (projectile != nullptr)
	{
		projectile->Speed += direction * FiringForce * Type->Mass;

		OnFire(firer);
	}
}

void AWeapon::OnFire_Implementation(AActor* firer)
{
}
