#include "World/DFSelectable.h"

void ADFSelectable::BeginPlay()
{
	Super::BeginPlay();
	OnClicked.AddUniqueDynamic(this, &ADFSelectable::OnSelected);
}
