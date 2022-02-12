// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HitReactInterface.h"
#include "Components/TimelineComponent.h"
#include "SunWukongCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAttacking);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBlockedAttack);

UENUM()
enum Direction
{
	Front  UMETA(DisplayName = "Front"),
	Back   UMETA(DisplayName = "Back"),
	Left   UMETA(DisplayName = "Left"),
	Right  UMETA(DisplayName = "Right"),
};

UCLASS()
class WUKONGENDLESSRUNNER_API ASunWukongCharacter : public ACharacter, public IHitReactInterface
{
	GENERATED_BODY()
	
	/** Side view camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* SideViewCameraComponent;

	/** Camera boom positioning the camera beside the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	
public:
	// Sets default values for this character's properties
	ASunWukongCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void InitRotationTimelineComp();

	/** Called for side to side input */
	void MoveRight(float Value);

	UPROPERTY(VisibleAnywhere)
		USceneComponent* CloudPlaceHolder;

	UPROPERTY(VisibleAnywhere)
		class UBoxComponent* CloudCollision3;

public:

	FORCEINLINE USceneComponent* GetCloudPlaceHolder()
	{
		return CloudPlaceHolder;
	}

	FORCEINLINE UBoxComponent* GetCloudCollision()
	{
		return CloudCollision3;
	}

	/** Properties */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttackSystem)
		int AttackCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttackSystem)
		bool SaveAttack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttackSystem)
		bool IsAttacking;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BlockSystem)
		bool IsBlocking;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HealthSystem)
		float Health;

	UPROPERTY(BlueprintAssignable)
		FAttacking AttackingDelegate;

	UPROPERTY(BlueprintAssignable)
		FBlockedAttack BlockedAttackDelegate;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called to bind functionality to input
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	void calculateNewHealth(float Damage);

	/** Attack System */
	UFUNCTION(BlueprintCallable, Category = "AttackSystem")
		void PerformCombo();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "AttackSystem")
		void ResetCombo();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "AttackSystem")
		void ComboAttackSave();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "AttackSystem")
		void PerformPrimaryAttackA();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "AttackSystem")
		void PerformPrimaryAttackB();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "AttackSystem")
		void PerformPrimaryAttackC();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "AttackSystem")
		void PerformPrimaryAttackD();

	/** HitReact System */
	UFUNCTION(BlueprintNativeEvent, BlueprintInternalUseOnly, Category = "HitReactInterface")
		void HitReact(AActor* damageCauser, const struct FImpactParticleSystemStruct& impactParticleSystem);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "HitReactInterface")
		void HitReactPlayBlockEffect();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "HitReactInterface")
		void HitReactPlayGetHit(const struct FImpactParticleSystemStruct& impactParticleSystem, Direction direction);

	/** Health System */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "HealthSystem")
		void UpdateHealthWidget();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "HealthSystem")
		void CharacterHasDied();

	UFUNCTION(BlueprintPure, Category = "AttackSystem")
		bool IsAlive();

	/* Character Auto Rotate Left/Right */
	UPROPERTY(EditAnywhere, Category = "Timeline")
		UCurveFloat* RotateTimelineFloatCurve;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UTimelineComponent* RotationTimelineComp;

	UFUNCTION()
		void UpdateRelativeRotation(float Alpha);

	UFUNCTION()
		void RotateFinished();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Jump")
		void ToggleFlying();

private:

	void JumpPressed();
	void JumpReleased();
	void Attack();
	Direction CalculateDirection(FRotator normalizedRotation);
	bool IsFacing(AActor* damageCauser);
};
