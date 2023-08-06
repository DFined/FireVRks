#pragma once
#include "DFSelectable.generated.h"

UCLASS()
class ADFSelectable : public AActor
{
public:
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	virtual void OnSelected(AActor* Actor, FKey Key){}
};
