// Fill out your copyright notice in the Description page of Project Settings.
#include "PathToVengeance/Public/EnemiTest.h"

#include "Components/BoxComponent.h"
#include "PathToVengeance/PathToVengeanceCharacter.h"
#include "PathToVengeance/PathToVengeancePlayerController.h"

class APathToVengeanceCharacter;
// Sets default values
AEnemiTest::AEnemiTest()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//Set up Collider
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(FName("BoxCollision"));
	BoxCollision->SetupAttachment(RootComponent);
	BoxCollision->OnComponentEndOverlap.AddDynamic(this, &AEnemiTest::OnEndOverlap);
}

// Called when the game starts or when spawned
void AEnemiTest::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemiTest::Die()
{
	Destroy();
}

// Called every frame
void AEnemiTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemiTest::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
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
				if (PlayerControlled->EnemiArray.Contains(this))
				{
					PlayerControlled->EnemiArray.Remove(this);
				}
			}
		}
	}
}


