// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Sword.h"
#include "EnemiTest.h"
#include "Weapon.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/Character.h"
#include "Components/BoxComponent.h"
#include "GameFramework/PlayerController.h"
#include "PathToVengeanceCharacter.generated.h"

UCLASS(Blueprintable)
class APathToVengeanceCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APathToVengeanceCharacter();
	void SetSpeed(float Speed);
	void BeginPlay();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	void Attack();
	void StopAttack();
	void Interract();
	bool bIsAttacking = false;

	UPROPERTY(EditAnywhere, Category = "Attack")
	TArray<AActor*> EnemiArray;

	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<ASword> SwordBlueprintClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attack")
	AWeapon* NearWeapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attack")
	AWeapon* CurrentWeapon;

	// Create Event
	UFUNCTION(BlueprintImplementableEvent, Category = "Attack")
	void OnNewWeapon();

	UFUNCTION(BlueprintImplementableEvent, Category = "Attack")
	void CheckWeapon();

	UPROPERTY()
	bool bInterract;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                    int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* BoxCollision;

	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	FTimerHandle MyTimerHandle;


#pragma region Stat
	UPROPERTY(VisibleAnywhere, Category = "Stat")
	int Damage = 10;
	int BaseDamage = 10;
	UPROPERTY(VisibleAnywhere, Category = "Stat")
	int Life = 15;
	int BaseLife = 15;
	
	UPROPERTY(VisibleAnywhere, Category = "Stat")
	int Speed = 300;
	int BaseSpeed = 300;
	
	UPROPERTY(VisibleAnywhere, Category = "Stat")
	float AttackSpeed = .33f;
	float BaseAttackSpeed = .33f;
	
	UPROPERTY(VisibleAnywhere, Category = "Stat")
	int distAttack = 400;
	int BasedistAttack = 400;
	
	UPROPERTY(VisibleAnywhere, Category = "Stat")
	int CriticalHit = 20;
	int BaseCriticalHit = 20;
	
	UPROPERTY(VisibleAnywhere, Category = "Stat")
	int Energy = 5;
	int BaseEnergy = 5;

#pragma endregion
};
