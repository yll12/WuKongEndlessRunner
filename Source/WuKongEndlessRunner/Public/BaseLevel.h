// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseLevel.generated.h"

class UBoxComponent;
class USceneComponent;

UCLASS()
class WUKONGENDLESSRUNNER_API ABaseLevel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseLevel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UBoxComponent* NextLevelSpawnTriggerBox;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UBoxComponent* NextLevelSpawnLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USceneComponent* RootSceneComponent;

//	UPROPERTY(EditAnywhere)
//		TSubclassOf<ABaseLevel> Level1;

//	APawn* Player;

public:	

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FVector SpawnLocation = FVector();
	FRotator SpawnRotation = FRotator();
	FActorSpawnParameters SpawnInfo = FActorSpawnParameters();

	FORCEINLINE UBoxComponent* GetNextLevelSpawnTriggerBox()
	{
		return NextLevelSpawnTriggerBox;
	}

	FORCEINLINE UBoxComponent* GetNextLevelSpawnLocation()
	{
		return NextLevelSpawnLocation;
	}

//	UPROPERTY(EditAnywhere)
//		TSubclassOf<ULevelManager> LevelManagerType;

//	UPROPERTY(BlueprintReadOnly)
//		ULevelManager* LevelManagerRef;

//	UPROPERTY(EditAnywhere)
//		TArray<TSubclassOf<ABaseLevel>> LevelList;

	UFUNCTION()
		void OnTriggerBoxOverlapBegin(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


};
