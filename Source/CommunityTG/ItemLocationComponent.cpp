// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemLocationComponent.h"

// Sets default values for this component's properties
UItemLocationComponent::UItemLocationComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UItemLocationComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UItemLocationComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


UFUNCTION(BlueprintCallable, Category = "Inventory")
bool UItemLocationComponent::SetItem(AActor* actorItem)
{
	if (Item != nullptr)
		return false;

	if (actorItem == nullptr)
		return false;

	Item = actorItem;

	Item->AttachToComponent(this, FAttachmentTransformRules::SnapToTargetIncludingScale);
	
	return true;
}

AActor* UItemLocationComponent::RemoveItem()
{
	AActor* removing = Item;

	if (removing != nullptr)
	{
		Item = nullptr;
	}

	return removing;
}