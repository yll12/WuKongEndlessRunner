// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/TimelineComponent.h"
#include "SunWukongCloudComponent.generated.h"

class ASunWuKongCloud;
class ASunWukongCharacter;

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

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:

	void InitSummonCloudTimelineComp();
	void InitDeactivateTimelineComp();

	ASunWukongCharacter* SunWuKongReference;
	ASunWuKongCloud* SunWuKongCloudRef;
	FVector SunWuKongCloudInitialLocation;
	FVector SunWuKongCloudFinalLocation;

	bool CanActivateFly;
	bool CanDeactivateFly;

public:	
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Toggle Cloud")
		void ToggleCloud(TSubclassOf<ASunWuKongCloud> CloudToSpawn);

	/* Timeline Summon Cloud */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timeline")
		UCurveFloat* SummonCloudTimelineFloatCurve;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UTimelineComponent* SummonCloudTimelineComp;

	UFUNCTION()
		void UpdateSummonCloud(float Alpha);

	UFUNCTION()
		void SummonFinished();

	UFUNCTION()
		void TriggerJump();


	/* Timeline Deactivate Cloud*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timeline")
		UCurveFloat* DeactivateTimelineFloatCurve;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UTimelineComponent* DeactivateTimelineComp;

	UFUNCTION()
		void UpdateDeactivate(float Alpha);

	UFUNCTION()
		void DeactivateFinished();

};
