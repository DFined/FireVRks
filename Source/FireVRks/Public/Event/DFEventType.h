// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"

enum EDFEventType
{
	NONE,
	// Custom system events
	CUSTOM_SYSTEM_PARAMETER_CREATED,
	CUSTOM_SYSTEM_PARAMETER_DELETED,
	CUSTOM_SYSTEM_PARAMETER_RENAMED,
	CUSTOM_SYSTEM_PARAMETER_RETYPED
};
