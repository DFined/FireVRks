#pragma once
#include "ParameterInputUI.h"
#include "FX/Niagara/v2/MapParameterValueContext.h"
#include "FX/Niagara/v2/System/EffectSystem.h"
#include "DFUI/DFUI.h"
#include "EffectParameterInputUI.generated.h"

UCLASS(Blueprintable, BlueprintType)
class FIREVRKS_API UEffectParameterInputUI : public UParameterInputUI
{
	GENERATED_BODY()

	UPROPERTY()
	UEffectSystem* System = nullptr;
	
public:
	UEffectParameterInputUI();

	void SetSystem(UEffectSystem* FSystem)
	{
		this->System = FSystem;
		this->SetProvider(FSystem);
	}

	UFUNCTION(BlueprintCallable)
	static UEffectParameterInputUI* Instance(UPanelWidget* Parent, UEffectSystem* bSystem)
	{
		auto Widget = DFUI::AddWidget<UEffectParameterInputUI>(Parent);
		Widget->SetSystem(bSystem);
		Widget->Draw(UMapParameterValueContext::Instance(Widget));
		return Widget;
	};
};

