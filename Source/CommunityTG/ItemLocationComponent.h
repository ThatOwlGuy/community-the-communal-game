// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "ItemLocationComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COMMUNITYTG_API UItemLocationComponent : public USceneComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(BlueprintReadOnly, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	AActor* Item;

public:	
	// Sets default values for this component's properties
	UItemLocationComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool SetItem(AActor* actorItem);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	AActor* RemoveItem();

public:
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	inline class AActor* GetItem()
	{
		return Item;
	}
};
