#pragma once
#include "DFSelectable.h"
#include "DFUIAble.generated.h"

UCLASS()
class FIREVRKS_API ADFUIAble : public ADFSelectable
{
public:
	GENERATED_BODY()

protected:
	virtual void OnSelected(AActor* Actor, FKey Key) override;

	UFUNCTION(BlueprintCallable)
	virtual void OpenUI();
};
