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
		UBoxComponent* BackTrackBlocker;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USceneComponent* RootSceneComponent;

public:	

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE UBoxComponent* GetNextLevelSpawnTriggerBox()
	{
		return NextLevelSpawnTriggerBox;
	}

	FORCEINLINE UBoxComponent* GetNextLevelSpawnLocation()
	{
		return NextLevelSpawnLocation;
	}

	FORCEINLINE UBoxComponent* GetBackTrackBlocker()
	{
		return BackTrackBlocker;
	}

};
