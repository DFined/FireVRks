// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Border.h"
#include "Components/EditableTextBox.h"
#include "Components/HorizontalBox.h"
#include "Components/Image.h"
#include "Components/MultiLineEditableTextBox.h"
#include "Components/VerticalBox.h"
#include "Components/WidgetSwitcher.h"
#include "FX/Niagara/v2/System/CustomEffectSystem.h"
#include "DFUI/DFUIBase.h"
#include "UObject/Object.h"
#include "EffectSystemSavingWidget.generated.h"

/**
 * 
 */
UCLASS()
class FIREVRKS_API UEffectSystemSavingWidget : public UDFUIBase
{
	GENERATED_BODY()

	UPROPERTY()
	UBorder* RootBorder;

	UPROPERTY()
	UVerticalBox* RootBox;

	UPROPERTY()
	UEditableTextBox* SystemNameInput;

	UPROPERTY()
	UEditableTextBox* AuthorInput;
	
	UPROPERTY()
	UMultiLineEditableTextBox* DescriptionInput;
	
	UPROPERTY()
	UHorizontalBox* ResultBox;

	UPROPERTY()
	UImage* Viewport;

	UPROPERTY()
	UTextureRenderTarget2D* RenderTarget;

	UPROPERTY()
	UCustomEffectSystem* System;
	
	UPROPERTY()
	UWidgetSwitcher* IconSelectSwitcher;

public:
	UFUNCTION()
	void Save();
	
	UFUNCTION()
	void ChooseIcon();
	
	UFUNCTION()
	void FinishSavingIcon();
	
	UFUNCTION()
	void CancelSavingIcon();
	virtual UPanelWidget* MakeRootWidget() override;
	virtual UPanelWidget* GetMountingPoint() override;

	void SetMeta(UCustomEffectSystem* Meta);

	void SetRenderTarget(UTextureRenderTarget2D* RenderTarget);
};