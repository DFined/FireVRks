// Fill out your copyright notice in the Description page of Project Settings.


#include "Display/DisplayManager.h"

#include "Display/DisplayData.h"

UDisplayData* UDisplayManager::GetDisplayInEditing()
{
	if (!DisplayInEditing)
	{
		DisplayInEditing = UDisplayData::New(this);
	}
	return DisplayInEditing;
}

void UDisplayManager::SetDisplayInEditing(UDisplayData* bDisplayInEditing)
{
	this->DisplayInEditing = bDisplayInEditing;
	OnDisplayLoaded.Broadcast();
}

FOnDisplayLoaded& UDisplayManager::GetOnDisplayLoaded()
{
	return OnDisplayLoaded;
}
