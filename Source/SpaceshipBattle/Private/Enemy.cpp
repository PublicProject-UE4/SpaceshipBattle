// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SpaceShip.h"
#include "Kismet/KismetMathLibrary.h"
#include <SpaveShipGameMode.h>
#include <EnemySpawn.h>

// Sets default values
AEnemy::AEnemy()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// RootSceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	// RootComponent = RootSceneComp;

	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComp"));
	// CollisionComp->SetupAttachment(RootComponent);
	RootSceneComp = CollisionComp;

	EnemySM = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EnemySM"));
	EnemySM->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	EnemySM->SetRelativeRotation(FRotator(0, 270, 0));
	EnemySM->SetRelativeScale3D(FVector(0.75, 0.75, 0.75));
	EnemySM->SetupAttachment(RootSceneComp);

	Init();
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	SpaceShip = Cast<ASpaceShip>(UGameplayStatics::GetPlayerPawn(this, 0));

	SpaveShipGameMode = Cast<ASpaveShipGameMode>(UGameplayStatics::GetGameMode(this));

	TArray<AActor *> SpawnEnemyArray;
	UGameplayStatics::GetAllActorsOfClass(this, AEnemySpawn::StaticClass(), SpawnEnemyArray);
	EnemySpawn = Cast<AEnemySpawn>(SpawnEnemyArray[0]);

	SetColor();

}

void AEnemy::Init()
{
	Speed = 300.0f;
}

void AEnemy::MoveTowardPlayer(float DeltaTime)
{
	// 更新敌人的移动位置
	FVector Direction = (SpaceShip->GetActorLocation() - GetActorLocation()).GetSafeNormal();
	AddActorWorldOffset(Direction * DeltaTime * Speed, true);
	// 更新敌人的方向向量
	FRotator Rotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), SpaceShip->GetActorLocation());
	SetActorRotation(Rotation);
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (SpaceShip->GetBDead()) return;
	MoveTowardPlayer(DeltaTime);
}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemy::OnDeath()
{
	SpaveShipGameMode->IncreaseScore();
	EnemySpawn->DecreaseEnemyCount();
	/* 生成爆炸效果
	if (ExplosionParticle)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionParticle, GetActorLocation(), FRotator::ZeroRotator, true);
	}
	*/
	SpawnExplosion();
	Destroy();
}

