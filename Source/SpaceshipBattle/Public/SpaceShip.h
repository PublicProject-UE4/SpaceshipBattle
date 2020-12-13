// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SpaceShip.generated.h"

class UStaticMeshComponent;
class USphereComponent;
class UCameraComponent;
class USpringArmComponent;
class APlayerController;
class ABullet;
class USoundCue;
class UParticleSystemComponent;
class UParticleSystem;


UCLASS()
class SPACESHIPBATTLE_API ASpaceShip : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASpaceShip();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// 初始化
	void Init();

	// 飞机视角跟鼠标移动而移动
	void LookAtCursor();

	void Move(float DeltaTime);

	// 上下移动
	void MoveForward(float Value);

	// 左右移动
	void MoveRight(float Value);

	// 开火
	void Fire();

	void StartFire();

	void EndFire();

	void RestartLevel();

	void OnDeath();

protected:

	UPROPERTY(VisibleAnywhere, Category = "Component")
		USceneComponent *RootSceneComp;

	UPROPERTY(VisibleAnywhere, Category = "Component")
		USphereComponent *CollisionComp;

	UPROPERTY(VisibleAnywhere, Category = "Component")
		UStaticMeshComponent *ShipSM;

	UPROPERTY(VisibleAnywhere, Category = "Component")
		USpringArmComponent *SpringComp;

	UPROPERTY(VisibleAnywhere, Category = "Component")
		UCameraComponent *CameraComp;

	UPROPERTY(VisibleAnywhere, Category = "Component")
		USceneComponent *SpawnPoint;

	UPROPERTY(VisibleAnywhere, Category = "Component")
		UParticleSystemComponent *ThrusterParticleComp;

	// 爆炸后的例子特效
	UPROPERTY(EditAnywhere, Category = "Particle")
		UParticleSystem* ExplosionParticle;

	APlayerController *PC;

	FTimerHandle TimerHandle_BetweenShot;

	FTimerHandle TimerHandle_Restart;

	bool bDead;

	// 判断是否移动
	bool bForwardMove;
	bool bRightMove;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	bool GetBDead() { return bDead; };

public:

	UPROPERTY(EditAnywhere, Category = "Default")
		float Speed;

	UPROPERTY(EditAnywhere, Category = "Default")
		TSubclassOf<ABullet> Bullet;

	UPROPERTY(EditAnywhere, Category = "Default")
		float BetweenShot;

	// 玩家爆炸声音
	UPROPERTY(EditAnywhere, Category = "Sound")
		USoundCue *GameOverCue;

	// 射击声音
	UPROPERTY(EditAnywhere, Category = "Sound")
		USoundCue *ShootCue;

};
