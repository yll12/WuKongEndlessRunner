// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/TimelineComponent.h"
#include "SunWukongCloudComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WUKONGENDLESSRUNNER_API USunWukongCloudComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USunWukongCloudComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void InitRotationTimelineComp();

	class ASunWukongCharacter* sunWuKongReference;
	AActor* SunWuKongCloudRef;
	FVector SunWuKongCloudInitialLocation;

	bool CanActivateFly = true;
	bool CanDeactivateFly;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Toggle Cloud")
		void ToggleCloud(TSubclassOf<class AActor> ClassToSpawn);

	/* Timeline Test */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timeline")
		UCurveFloat* RotateTimelineFloatCurve;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UTimelineComponent* RotationTimelineComp;

	UFUNCTION()
		void UpdateRelativeRotation(float Alpha);

	UFUNCTION()
		void RotateFinished();

	UFUNCTION()
		void TriggerJump();
};
