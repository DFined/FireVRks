#include "InsertablePanelGrid.h"

#include "WidgetArray.h"
#include "Components/Button.h"
#include "Components/CanvasPanelSlot.h"
#include "DFUI/DFUI.h"
#include "UI/Icons.h"
#include "Util/DFStatics.h"

UCanvasPanelSlot* UInsertablePanelGrid::GetSlot(int X, int Y)
{
	return Cast<UCanvasPanelSlot>((*Children[X])[Y]->Slot);
}

void UInsertablePanelGrid::MakePlusButton(int X, int Y)
{
	auto Btn = DFUI::AddImageButton(this->GetMountingPoint(), UDFStatics::ICONS->PLUS_ICON, BUTTON_SIZE);
	auto BSlot = Cast<UCanvasPanelSlot>(Btn->Slot);
	BSlot->SetAutoSize(true);
	BSlot->SetPosition(FVector2D(X, Y));
	PlusButtons.Add(Btn);
}

void UInsertablePanelGrid::AddColumn(UWidget* Widget, int PosX)
{
	if (PosX <= Children.Num())
	{
		auto VArr = NewObject<UWidgetArray>(this);
		Children.Insert(VArr, PosX);
		AddWidget(Widget, PosX, 0);
	}
}

void UInsertablePanelGrid::AddWidget(UWidget* Widget, int PosX, int PosY)
{
	Children[PosX]->Insert(Widget, PosY);
	Append(Widget);
	if (auto bSlot = Cast<UCanvasPanelSlot>(Widget->Slot))
	{
		bSlot->SetAutoSize(true);
	}
	ReTile();
}

int UInsertablePanelGrid::GetWidthForColumn(int X)
{
	int MaxWidth = 0;
	for (UWidget* Widget : Children[X]->Get())
	{
		Widget->ForceLayoutPrepass();
		auto Width = Widget->GetDesiredSize().X;
		MaxWidth = Width > MaxWidth ? Width : MaxWidth;
	}
	return MaxWidth;
}

int UInsertablePanelGrid::GetWidth(int X, int Y)
{
	return Children[X]->Get()[Y]->GetDesiredSize().X;
}

int UInsertablePanelGrid::GetHeight(int X, int Y)
{
	return Children[X]->Get()[Y]->GetDesiredSize().Y;
}

void UInsertablePanelGrid::setSize(int X, int Y, int Width, int Height)
{
	GetSlot(X, Y)->SetSize(FVector2D(Width, Height));
}

void UInsertablePanelGrid::ReTile()
{
	ForceLayoutPrepass();
	int XOffset = 0;

	for (UButton* Button : PlusButtons)
	{
		this->Panel->GetAllChildren().Remove(Button);
		Button->RemoveFromParent();
	}
	PlusButtons.Empty();

	for (int X = 0; X < Children.Num(); X++)
	{
		int YOffset = 0;
		auto ColWidth = GetWidthForColumn(X);
		for (int Y = 0; Y < Children[X]->Num(); Y++)
		{
			auto CSlot = GetSlot(X, Y);
			auto XStart = X * (X_SPACING * 2 + BUTTON_SIZE) + XOffset + (ColWidth - GetWidth(X, Y)) / 2;
			auto YStart = Y * (Y_SPACING * 2 + BUTTON_SIZE) + YOffset;
			CSlot->SetPosition(FVector2D(XStart, YStart));
			YOffset += GetHeight(X,Y);

			MakePlusButton(
				X * (X_SPACING * 2 + BUTTON_SIZE) + XOffset + (ColWidth - BUTTON_SIZE) / 2,
				Y * (Y_SPACING * 2 + BUTTON_SIZE) + YOffset + Y_SPACING
			);
		}
		XOffset += ColWidth;
		MakePlusButton(X * (X_SPACING * 2 + BUTTON_SIZE) + X_SPACING + XOffset, (GetSlot(X, 0)->GetSize().Y / 2) - (BUTTON_SIZE / 2) + 32);
	}
}


UPanelWidget* UInsertablePanelGrid::MakeRootWidget()
{
	Panel = DFUI::MakeWidget<UCanvasPanel>(this);
	return Panel;
}

UPanelWidget* UInsertablePanelGrid::GetMountingPoint()
{
	return Panel;
}
