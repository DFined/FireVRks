#include "UI/lib/Container/DFUIStack.h"

#include "Blueprint/WidgetTree.h"
#include "Components/Border.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "UI/Icons.h"
#include "DFUI/DFStyleUtil.h"
#include "DFUI/DFUI.h"
#include "Util/DFStatics.h"


UPanelWidget* UDFUIStack::MakeRootWidget()
{
	auto Border = DFUI::MakeWidget<UBorder>(this);
	VerticalBox = DFUI::MakeWidget<UVerticalBox>(Border);
	FSlateBrush Brush = FSlateBrush();
	Brush.Margin = FMargin(0.3f, 0.0f, 0.0f, 0.0f);
	Brush.DrawAs = ESlateBrushDrawType::Box;
	auto Texture = DFStyleUtil::LoadCachedTexture(UDFStatics::ICONS->LEFT_OFFSET_BORDER);
	Brush.SetResourceObject(Texture);
	Brush.Tiling = ESlateBrushTileType::NoTile;
	Brush.ImageType = ESlateBrushImageType::Linear;
	Border->SetBrush(Brush);
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
