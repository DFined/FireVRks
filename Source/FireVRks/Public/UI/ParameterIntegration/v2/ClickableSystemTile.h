// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Border.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "FX/Niagara/v2/System/EffectSystem.h"
#include "UI/lib/Container/DFUIContainer.h"
#include "ClickableSystemTile.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSystemPressed, UClickableSystemTile*, Tile);

UCLASS()
class FIREVRKS_API UClickableSystemTile : public UDFUIContainer
{
	GENERATED_BODY()

	UPROPERTY()
	UBorder* RootBorder;
	
	UPROPERTY()
	UButton* Button;

	UPROPERTY()
	UTextBlock* Label;

	UPROPERTY()
	UImage* Image;

	FOnSystemPressed OnSystemPressed;

public:
	UFUNCTION()
	void OnClick();
	
	virtual UPanelWidget* MakeRootWidget(UWidgetTree* Tree) override;
	void Initialize(UEffectSystem* System, int Size);
	virtual UPanelWidget* GetMountingPoint() override;
	FOnSystemPressed& GetOnPressed();

	void Select();
	void DeSelect();
};
