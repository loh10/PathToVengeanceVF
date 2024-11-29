// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
UENUM()
enum class Rarity : uint8
{
	Common,
	Rare,
	Epic,
	Legendary,
	None
};
class PATHTOVENGEANCE_API DropChoose
{
public:
	DropChoose();
	~DropChoose();
	Rarity SetRandomRarity() const;
};
