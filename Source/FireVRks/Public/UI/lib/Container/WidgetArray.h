#pragma once
#include "Components/Widget.h"
#include "WidgetArray.generated.h"

UCLASS()
class FIREVRKS_API UWidgetArray : public UObject
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<UWidget*> Widgets;

public:
	UWidget* operator[](int index);

	int Num() const;

	void Insert(UWidget* Widget, int Index);

	TArray<UWidget*>& Get();
};
