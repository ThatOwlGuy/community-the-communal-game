// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ProjectileType.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class COMMUNITYTG_API UProjectileType : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY( BlueprintReadOnly, Category = "Balistics", Meta = (ClampMin = "0", ClampMax = "2000"))
	float Caliber;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Balistics", Meta = (ClampMin = "-1.0", ClampMax = "0.0"))
	float AirFriction;

	UPROPERTY(BlueprintReadOnly, Category = "Balistics")
	float Defelecting;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Balistics")
	float Mass;

	UPROPERTY(BlueprintReadOnly, Category = "Balistics")
	float TypicalSpeed;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	UStaticMesh* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	FVector MeshScale;

	/**	\brief	Called when the bullet has hit something
	 *
	 *	@param	hit		The actor which was hit
	 *	@param	owner	The owner which fired the weapon
	 */
	UFUNCTION(BlueprintNativeEvent, Category = "Events")
	void OnHit(FHitResult hit, AActor* owner);
};
