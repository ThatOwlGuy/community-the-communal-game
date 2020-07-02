// Fill out your copyright notice in the Description page of Project Settings.

#include "DrawDebugHelpers.h"

#include "Weapon.h"
#include "ProjectileType.h"

#include "Projectile.h"

// Sets default values
AProjectile::AProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	// Check if the ammo is already going to be destroyed
	if (IsPendingKill())
		return;

	Super::Tick(DeltaTime);

	// get the current position and expected position at the end of the frame
	FVector start = GetActorLocation();
	FVector end = start + (Speed * DeltaTime);

	// trace between the two positions, see if there was a collision
	TArray<FHitResult> hitResults;
	FCollisionQueryParams traceParams;
	traceParams.bTraceComplex = true;
	traceParams.AddIgnoredActor(OwnerActor);
	traceParams.AddIgnoredActor(Weapon);

	FCollisionObjectQueryParams queryParams;
	queryParams.ObjectTypesToQuery = FCollisionObjectQueryParams::AllObjects;

	//DrawDebugLine(GetWorld(), start, end, FColor::MakeRandomColor(), false, 10, 0, 1.0);

	if (GetWorld()->LineTraceMultiByObjectType(hitResults, start, end, queryParams, traceParams))
	{
		for (int i = 0; i < hitResults.Num(); ++i)
		{
			FHitResult result = hitResults[i];

			Type->OnHit(result, OwnerActor);

			Destroy();
			return;
		}
	}

	// set the position to the end of the frame
	SetActorLocation(end, false, nullptr, ETeleportType::ResetPhysics);

	// update the speed by lowering by a friction coef
	Speed += (Speed * Type->AirFriction) * DeltaTime;
	// apply gravity on the bullet
	Speed += FVector(0, 0, GetWorld()->GetGravityZ() * Type->Mass) * DeltaTime;
}

AProjectile* AProjectile::Create(AWeapon* wpn, AActor* owner, FVector location, FVector direction)
{
	AProjectile* projectile = wpn->GetWorld()->SpawnActor<AProjectile>(AProjectile::StaticClass(), location, direction.Rotation());
	projectile->Speed = owner->GetVelocity();
	projectile->Weapon = wpn;
	projectile->OwnerActor = owner;
	projectile->Type = wpn->GetProjectileType();

	projectile->MeshComponent->SetStaticMesh(projectile->Type->Mesh);
	projectile->MeshComponent->SetWorldScale3D(projectile->Type->MeshScale);

	return projectile;
}
