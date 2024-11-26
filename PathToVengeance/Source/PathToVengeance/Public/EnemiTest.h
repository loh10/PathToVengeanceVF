
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Templates/SubclassOf.h"
#include "Components/BoxComponent.h"
#include "EnemiTest.generated.h"


UCLASS()
class PATHTOVENGEANCE_API AEnemiTest : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemiTest();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere, Category = "Stats")
	int Life ;
	void Die();
protected:
	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,int32 OtherBodyIndex);
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* BoxCollision;
	
};
