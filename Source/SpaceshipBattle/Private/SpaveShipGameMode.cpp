// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaveShipGameMode.h"
#include "SpaceShip.h"

ASpaveShipGameMode::ASpaveShipGameMode()
{
	DefaultPawnClass = ASpaceShip::StaticClass();
}

void ASpaveShipGameMode::IncreaseScore()
{
	Score++;
}

int ASpaveShipGameMode::GetScore()
{
	return Score;
}
