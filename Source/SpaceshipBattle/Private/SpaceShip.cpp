// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceShip.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/SceneComponent.h"
#include "Bullet.h"
#include "Engine/World.h"




// Sets default values
ASpaceShip::ASpaceShip()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootSceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	RootComponent = RootSceneComp;

	ShipSM = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipSM"));
	ShipSM->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ShipSM->SetRelativeRotation(FRotator(0, 270, 0));
	ShipSM->SetRelativeScale3D(FVector(0.75, 0.75, 0.75));
	ShipSM->SetupAttachment(RootSceneComp);

	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComp"));
	CollisionComp->SetupAttachment(RootComponent);

	SpringComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringComp"));
	SpringComp->SetRelativeRotation(FRotator(270,0,0));
	SpringComp->bInheritYaw = false;
	SpringComp->bInheritRoll = false;
	SpringComp->bInheritPitch = false;
	SpringComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetProjectionMode(ECameraProjectionMode::Orthographic);
	CameraComp->SetOrthoWidth(6000.0);
	CameraComp->SetupAttachment(SpringComp);

	SpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnPoint"));
	SpawnPoint->SetRelativeLocation(FVector(0, 190, 0));
	SpawnPoint->SetRelativeRotation(FRotator(0, 90, 0));
	SpawnPoint->SetupAttachment(ShipSM);

	Init();

}

// Called when the game starts or when spawned
void ASpaceShip::BeginPlay()
{
	Super::BeginPlay();
	
	// 获取控制器
	PC = Cast<APlayerController>(GetController());
	// 显示鼠标
	PC->bShowMouseCursor = true;
	
}

void ASpaceShip::Init()
{
	Speed = 2500.0f;
}

void ASpaceShip::LookAtCursor()
{
	// 获取鼠标位置并转换成世界位置返回
	FVector MouseLocation, MosueDirection, TargetLocation;
	PC->DeprojectMousePositionToWorld(MouseLocation, MosueDirection);
	TargetLocation = FVector(MouseLocation.X, MouseLocation.Y, GetActorLocation().Z);
	// 获取一个坐标看向另一个坐标需要转动的角度
	FRotator LookAtRotator = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TargetLocation);
	SetActorRotation(LookAtRotator);
}

void ASpaceShip::Move(float DeltaTime)
{
	AddActorWorldOffset(ConsumeMovementInputVector()*Speed*DeltaTime, true);
}

void ASpaceShip::MoveForward(float Value)
{
	AddMovementInput(FVector::ForwardVector, Value);
}

void ASpaceShip::MoveRight(float Value)
{
	AddMovementInput(FVector::RightVector, Value);
}

void ASpaceShip::Fire()
{
	if (Bullet)
	{
		FActorSpawnParameters SpawnParames;
		GetWorld()->SpawnActor<ABullet>(Bullet, SpawnPoint->GetComponentLocation(), SpawnPoint->GetComponentRotation(), SpawnParames);
	}
}

// Called every frame
void ASpaceShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	LookAtCursor();

	Move(DeltaTime);
}

// Called to bind functionality to input
void ASpaceShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASpaceShip::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASpaceShip::MoveRight);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ASpaceShip::Fire);
}

