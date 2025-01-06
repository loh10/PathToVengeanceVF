// Fill out your copyright notice in the Description page of Project Settings.


#include "DropChoose.h"


DropChoose::DropChoose()
{
}

DropChoose::~DropChoose()
{
}

Rarity DropChoose::SetRandomRarity() const
{
	int rarityPercent = FMath::RandRange(0, 100);
	if (rarityPercent < 50)
	{
		return Rarity::Common;
	}
	else if (rarityPercent < 75)
	{
		return Rarity::Rare;
	}
	else if (rarityPercent < 95)
	{
		return Rarity::Epic;
	}
	else
	{
		return Rarity::Legendary;
	}
}
