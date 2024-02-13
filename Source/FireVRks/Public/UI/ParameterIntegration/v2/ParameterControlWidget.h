// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DFUI/DFUIBase.h"
#include "ParameterControlWidget.generated.h"

/**
 * 
 */
UCLASS()
class FIREVRKS_API UParameterControlWidget : public UDFUIBase
{
	GENERATED_BODY()
public:	
	/**
	 * Construct the root widget
	*/
	virtual UPanelWidget* MakeRootWidget() PURE_VIRTUAL("MakeRootWidget", return nullptr;);
	virtual void OnChange();	
};
