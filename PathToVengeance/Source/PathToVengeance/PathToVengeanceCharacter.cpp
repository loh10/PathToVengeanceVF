// Copyright Epic Games, Inc. All Rights Reserved.

#include "PathToVengeanceCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"
#include "Public/EnemiTest.h"

APathToVengeanceCharacter::APathToVengeanceCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	//Set up Collider
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(FName("BoxCollision"));
	BoxCollision->SetupAttachment(RootComponent);
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &APathToVengeanceCharacter::OnBeginOverlap);
}

void APathToVengeanceCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void APathToVengeanceCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void APathToVengeanceCharacter::Attack()
{
	if (bIsAttacking == false)
	{
		bIsAttacking = true;
		for (AActor* Enemi : EnemiArray)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, (Enemi->GetName()));
			if(Enemi != nullptr)
			{
				AEnemiTest* EnemiCharacter = Cast<AEnemiTest>(Enemi);
				if(EnemiCharacter != nullptr)
				{
					EnemiCharacter->Life -= 1;
					if(EnemiCharacter->Life <= 0)
					{
						EnemiCharacter->Die();
					}
				}
			}
		}
		GetWorldTimerManager().SetTimer(MyTimerHandle, this, &APathToVengeanceCharacter::StopAttack, AttackCooldown,
		                                false);
	}
}

void APathToVengeanceCharacter::StopAttack()
{
	bIsAttacking = false;
	GetWorldTimerManager().ClearTimer(MyTimerHandle);
}



void APathToVengeanceCharacter::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,const FHitResult& SweepResult)
{
	if(!EnemiArray.Contains(OtherActor))
	{
		EnemiArray.Add(OtherActor);
	}
}

