#pragma once
#include "DFUI/Icon.h"
#include "Icons.generated.h"

UCLASS()
class UIcons : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY()
	UIcon* LEFT_OFFSET_BORDER;
	
	UPROPERTY()
	UIcon* DEFAULT_EFFECT_ICON;
	
	UPROPERTY()
	UIcon* CUSTOM_EFFECT_ICON;
	
	UPROPERTY()
	UIcon* NOT_SELECTED_EFFECT_ICON;
	
	UPROPERTY()
	UIcon* DELETE_ICON;
	
	UPROPERTY()
	UIcon* PLUS_ICON;
	
	UPROPERTY()
	UIcon* UP_ICON;
	
	UPROPERTY()
	UIcon* DOWN_ICON;

	void Initialize()
	{
		LEFT_OFFSET_BORDER = UIcon::New(this, "/Game/FireVRks/UI/Icons/LeftOffsetBorder.LeftOffsetBorder", true);
		DEFAULT_EFFECT_ICON = UIcon::New(this, "/Game/FireVRks/UI/Icons/DefaultEffectIcon.DefaultEffectIcon", true);
		CUSTOM_EFFECT_ICON = UIcon::New(this, "/Game/FireVRks/UI/Icons/CustomEffectIcon.CustomEffectIcon", true);
		NOT_SELECTED_EFFECT_ICON = UIcon::New(this, "/Game/FireVRks/UI/Icons/DefaultEffectIcon.NotSelected", true);
		DELETE_ICON = UIcon::New(this, "/Game/FireVRks/UI/Icons/DeleteIcon.DeleteIcon", true);
		PLUS_ICON = UIcon::New(this, "/Game/FireVRks/UI/Icons/Plus.Plus", true);
		UP_ICON = UIcon::New(this, "/Game/FireVRks/UI/Icons/Up.Up", true);
		DOWN_ICON = UIcon::New(this, "/Game/FireVRks/UI/Icons/Down.Down", true);
	}

	static UIcons* StaticInstance()
	{
		auto Instance = NewObject<UIcons>(GetTransientPackage());
		Instance->AddToRoot();
		Instance->Initialize();
		return Instance;
	}
};
