#pragma once
#include "DFInputPopup.h"
#include "DFUI/DFUI.h"

class EDFUI
{
public:
	template <class InputType>
	static UDFInputPopup* OpenInputPopup(APlayerController* Controller, FString Label)
	{
		auto Popup = CreateWidget<UDFInputPopup>(Controller, UDFInputPopup::StaticClass());
		auto InputWidget = DFUI::MakeWidget<InputType>(Popup);

		Popup->AddToViewport(1000);
		Popup->InitializePopup(InputWidget, Label);
		return Popup;
	}
};
