// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DropChoose.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UCLASS()
class PATHTOVENGEANCE_API AWeapon : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWeapon();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

#pragma region Mesh
	UPROPERTY(EditAnywhere, Category = "Mesh")
	TArray<UMaterial*> Materials;

	UPROPERTY(EditAnywhere, Category = "Mesh")
	TArray<UTexture2D*> Texture;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
	UTexture2D* currentTexture;
#pragma endregion
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base")
	class UStaticMeshComponent* Mesh;

	Rarity rarity;

	FString GetName() const;
	void SetRarity(Rarity);

	UPROPERTY(BlueprintReadOnly)
	int StatToChange;
	UPROPERTY(BlueprintReadOnly)
	int PercentValue;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                  int32 OtherBodyIndex);
	void SetColor(Rarity);
	int SetStat(Rarity);


};
