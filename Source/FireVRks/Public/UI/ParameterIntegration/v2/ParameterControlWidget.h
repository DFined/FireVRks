// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/lib/Container/DFUIContainer.h"
#include "ParameterControlWidget.generated.h"

/**
 * 
 */
UCLASS()
class FIREVRKS_API UParameterControlWidget : public UDFUIContainer
{
	GENERATED_BODY()
	
public:	
	/**
	 * Construct the root widget
	*/
	virtual UPanelWidget* MakeRootWidget(UWidgetTree* Tree) PURE_VIRTUAL("MakeRootWidget", return nullptr;);
	virtual void OnChange();
};
