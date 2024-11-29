// Fill out your copyright notice in the Description page of Project Settings.


#include "Sword.h"

#include "PathToVengeance/PathToVengeanceCharacter.h"


// Sets default values
ASword::ASword()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}


// Get the name of the sword
FString ASword::GetName() const
{
	return TEXT("Sword");
}

void ASword::SetRarity(Rarity rarityToSet)
{
	rarity = rarityToSet;
	ASword::SetColor(rarity);
}

void ASword::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
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
				}
			}
		}
	}
}

// Called when the game starts or when spawned
void ASword::BeginPlay()
{
	Super::BeginPlay();
	TArray<UStaticMeshComponent*> MeshComponents;
	GetComponents<UStaticMeshComponent>(MeshComponents);
	if (MeshComponents.Num() > 0)
	{
		Mesh = MeshComponents[0];
	}
	Mesh->OnComponentEndOverlap.AddDynamic(this, &ASword::OnEndOverlap);
}
void ASword::SetColor(Rarity rarityToApply)
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
}
// Called every frame
void ASword::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
