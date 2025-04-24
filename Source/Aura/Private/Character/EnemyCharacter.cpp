// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EnemyCharacter.h"


void AEnemyCharacter::HighlightActor()
{
	check(GetMesh());
	GetMesh()->SetRenderCustomDepth(true);

	if (Weapon != nullptr)
	{
		Weapon->SetRenderCustomDepth(true);
	}
}

void AEnemyCharacter::UnHighlightActor()
{
	check(GetMesh());
	GetMesh()->SetRenderCustomDepth(false);

	if (Weapon != nullptr)
	{
		Weapon->SetRenderCustomDepth(false);
	}
}
