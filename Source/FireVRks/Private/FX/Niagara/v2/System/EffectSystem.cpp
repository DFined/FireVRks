// Fill out your copyright notice in the Description page of Project Settings.


#include "..\..\..\..\..\Public\FX\Niagara\v2\System\EffectSystem.h"

FString UEffectSystem::GetAuthor() const
{
	return Author;
}

void UEffectSystem::SetAuthor(const FString& bAuthor)
{
	this->Author = bAuthor;
}

FString UEffectSystem::GetDescription() const
{
	return Description;
}

void UEffectSystem::SetDescription(const FString& bDescription)
{
	this->Description = bDescription;
}
