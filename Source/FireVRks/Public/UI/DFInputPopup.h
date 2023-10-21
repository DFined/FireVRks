// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/VerticalBox.h"
#include "lib/Container/DFUIContainer.h"
#include "DFInputPopup.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnConfirm, UWidget*, InputWidget);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCancel);


UCLASS()
class FIREVRKS_API UDFInputPopup : public UDFUIContainer
{
	GENERATED_BODY()

	UPROPERTY()
	UVerticalBox* RootBox;

	UPROPERTY()
	UWidget* InputWidget;

	FOnConfirm OnConfirm;
	FOnCancel OnCancel;

public:
	virtual UPanelWidget* MakeRootWidget(UWidgetTree* Tree) override;
	virtual UPanelWidget* GetMountingPoint() override;
	UFUNCTION()
	void Confirm();
	UFUNCTION()
	void Cancel();
	void InitializePopup(UWidget* Input, FString Text);

	template <class InputType>
	InputType* GetWidget()
	{
		return Cast<InputType>(InputWidget);
	}

	FOnConfirm* GetOnConfirm() 
	{
		return &OnConfirm;
	}

	FOnCancel* GetOnCancel() 
	{
		return &OnCancel;
	}
};
