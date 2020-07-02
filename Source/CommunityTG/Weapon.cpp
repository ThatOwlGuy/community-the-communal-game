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
	FVector location;
	FVector direction;

#if 0
	if (ACharacter* character = Cast<ACharacter>(firer))
	{
		FRotator rotation;
		character->GetActorEyesViewPoint(location, rotation);
		direction = rotation.Vector();
	}
	else
	{
		location = firer->GetActorLocation();
		direction = firer->GetActorForwardVector();
	}
#else
	direction = this->GetActorRightVector();
	location = this->GetActorLocation() + this->GetActorRotation().RotateVector(this->MuzzlePoint);
#endif

	AProjectile* projectile = AProjectile::Create(this, firer, location, direction);
	if (projectile != nullptr)
	{
		projectile->Speed += direction * FiringForce * Type->Mass;

		OnFire(projectile, firer);

		return true;
	}

	return false;
}

void AWeapon::OnFire_Implementation(AProjectile* projectile, AActor* firer)
{
}
