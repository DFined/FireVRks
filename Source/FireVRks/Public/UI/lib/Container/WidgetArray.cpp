#include "WidgetArray.h"

#include "Components/Widget.h"

UWidget* UWidgetArray::operator[](int index)
{
	return Widgets[index];
}

int UWidgetArray::Num() const
{
	return Widgets.Num();
}

void UWidgetArray::Insert(UWidget* Widget, int Index)
{
	Widgets.Insert(Widget, Index);
}

TArray<UWidget*>& UWidgetArray::Get()
{
	return Widgets;
}
