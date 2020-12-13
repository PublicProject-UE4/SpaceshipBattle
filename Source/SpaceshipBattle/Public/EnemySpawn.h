// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawn.generated.h"

class UBoxComponent;
class AEnemy;
class ASpaceShip;

UCLASS()
class SPACESHIPBATTLE_API AEnemySpawn : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Init();

	FVector GetGenerateLocation();

	void SpawnEnemy();

protected:

	UPROPERTY(VisibleAnywhere, Category = "Component")
		USceneComponent *RootSceneComp;

	UPROPERTY(VisibleAnywhere, Category = "Component")
		UBoxComponent *SpawnArea;

	ASpaceShip* SpaceShip;

	FTimerHandle TimerHandle_Spawn;

	// ���������
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EnemySpawn")
		int MaxEnemyNum;

	// ��������Ŀ
	UPROPERTY(BlueprintReadOnly, Category = "EnemySpawn")
		int CurrentEnemyCount;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void DecreaseEnemyCount();

public:

	UPROPERTY(EditAnywhere, Category = Enemy)
		TSubclassOf<AEnemy> Enemy;

	// ���ɾ�������С����
	UPROPERTY(EditAnywhere, Category = "Default")
		float MinimumDistanceToPlayer;

	// ���ɵ��˼��ʱ��
	UPROPERTY(EditAnywhere, Category = "Default")
		float SpawnIntVal;
};