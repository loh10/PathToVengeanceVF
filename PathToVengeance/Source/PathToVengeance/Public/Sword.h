// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DropChoose.h"
#include "Weapon.h"
#include "GameFramework/Actor.h"
#include "Sword.generated.h"

UCLASS()
class PATHTOVENGEANCE_API ASword : public AWeapon
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASword();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	FString GetName() const;
	void SetRarity(Rarity);
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Base")
	class UStaticMeshComponent* Mesh;
	Rarity rarity;
	UPROPERTY(EditAnywhere, Category = "Mesh")
	TArray<UMaterial*> Materials;
	UPROPERTY(EditAnywhere, Category = "Mesh")
	TArray<UTexture2D*> Texture;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "Mesh")
	UTexture2D* currentTexture;
protected:
	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void SetColor(Rarity);
};
