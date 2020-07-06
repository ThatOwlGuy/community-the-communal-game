// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Weapon.generated.h"

UCLASS()
class COMMUNITYTG_API AWeapon : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(BlueprintReadOnly, Category = "Projectile", meta = (AllowPrivateAccess = "true"))
	class UProjectileType* Type;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	TSubclassOf<UProjectileType> TypeClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Muzzle")
	float FiringForce;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Muzzle")
	FVector MuzzlePoint;

public:	
	// Sets default values for this actor's properties
	AWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	/**	\brief	Fires the weapon as a self owner
	 *
	 *	@param	firer		The owner which will fire the weapon
	 *						May handle the trajectory of the weapon
	 */
	UFUNCTION(BlueprintCallable, Category="Firing")
	bool Fire(AActor* firer);

	/**	\brief	When the weapon is fired
	 *
	 *	@param	projectile	The projectile actor that was fired from the weapon
	 *	@param	firer		The owner which fired the weapon
	 */
	UFUNCTION(BlueprintNativeEvent, Category = "Events")
	void OnFire(AActor* firer);

private:
	UFUNCTION(Server, Reliable, WithValidation)
	void Fire_Server(AActor* firer);

public:

	inline class UProjectileType* GetProjectileType()
	{
		return Type;
	}
};
