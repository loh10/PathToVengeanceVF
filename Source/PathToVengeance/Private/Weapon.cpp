// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"

#include "Algo/RandomShuffle.h"
#include "PathToVengeance/PathToVengeanceCharacter.h"

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
	TArray<UStaticMeshComponent*> MeshComponents;
	GetComponents<UStaticMeshComponent>(MeshComponents);
	if (MeshComponents.Num() > 0)
	{
		Mesh = MeshComponents[0];
	}
	Mesh->OnComponentEndOverlap.AddDynamic(this, &AWeapon::OnEndOverlap);
	
}
void AWeapon::SetColor(Rarity rarityToApply)
{
	if(rarityToApply == Rarity::Common)
	{
		Mesh->SetMaterial(0, Materials[0]);
		currentTexture = Texture[0];
	}
	else if(rarityToApply == Rarity::Rare)
	{
		Mesh->SetMaterial(0, Materials[1]);
		currentTexture = Texture[1];

	}
	else if(rarityToApply == Rarity::Epic)
	{
		Mesh->SetMaterial(0, Materials[2]);
		currentTexture = Texture[2];
	}
	else if(rarityToApply == Rarity::Legendary)
	{
		Mesh->SetMaterial(0, Materials[3]);
		currentTexture = Texture[3];
	}
	StatToChange = SetStat(rarityToApply);
}

int AWeapon::SetStat(Rarity rarityToApply)
{
	int value = FMath::RandRange(0, 3);
	if(rarityToApply == Rarity::Common)
	{
		PercentValue =  FMath::RandRange(1, 5);
	}
	else if(rarityToApply == Rarity::Rare)
	{
		PercentValue = FMath::RandRange(5, 15);
	}
	else if(rarityToApply == Rarity::Epic)
	{
		PercentValue =  FMath::RandRange(15, 30);
	}
	else if(rarityToApply == Rarity::Legendary)
	{
		PercentValue = FMath::RandRange(30, 65);
	}
	return value;
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
// Get the name of the sword
FString AWeapon::GetName() const
{
	return TEXT("Sword");
}

void AWeapon::SetRarity(Rarity rarityToSet)
{
	rarity = rarityToSet;
	AWeapon::SetColor(rarity);
}

void AWeapon::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
						  int32 OtherBodyIndex)
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController != nullptr)
	{
		APawn* ControlledPawn = PlayerController->GetPawn();
		if (ControlledPawn != nullptr)
		{
			APathToVengeanceCharacter* PlayerControlled = Cast<APathToVengeanceCharacter>(ControlledPawn);
			if (PlayerControlled != nullptr)
			{
				if (PlayerControlled->NearWeapon != nullptr && PlayerControlled->NearWeapon == this)
				{
					PlayerControlled->NearWeapon = nullptr;
					PlayerControlled->bIsNearWeapon = false;
				}
			}
		}
	}
}


