#include "UI/lib/Container/DFUIStack.h"

#include "Blueprint/WidgetTree.h"
#include "Components/Border.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"


UPanelWidget* UDFUIStack::MakeRootWidget(UWidgetTree* Tree)
{
	auto Box = Tree->ConstructWidget<UVerticalBox>(UVerticalBox::StaticClass());
	auto Border = Tree->ConstructWidget<UBorder>(UBorder::StaticClass(), "RootWidget");
	FSlateBrush Brush = FSlateBrush();
	Brush.Margin = FMargin(0.3f, 0.0f, 0.0f, 0.0f);
	Brush.DrawAs = ESlateBrushDrawType::Box;
	auto Texture = LoadObject<UTexture2D>(GetTransientPackage(), TEXT("/Game/FireVRks/UI/Icons/LeftOffsetBorder.LeftOffsetBorder"));
	Brush.SetResourceObject(Texture);
	Brush.Tiling = ESlateBrushTileType::NoTile;
	Brush.ImageType = ESlateBrushImageType::Linear;
	Border->SetBrush(Brush);
	Border->AddChild(Box);
	VerticalBox = Box;
	return Border;
}

UPanelWidget* UDFUIStack::GetMountingPoint()
{
	return VerticalBox;
}

UPanelSlot* UDFUIStack::Append(UWidget* Widget)
{
	auto NewSlot = Cast<UVerticalBoxSlot>(Super::Append(Widget));
	NewSlot->SetPadding(FMargin(18, 0, 0, 0));
	return NewSlot;
}
