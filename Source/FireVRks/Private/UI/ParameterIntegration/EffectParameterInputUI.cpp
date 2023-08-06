#include "UI/ParameterIntegration/EffectParameterInputUI.h"

#include "FX/Niagara/Scheduler/EffectSystemScheduler.h"
#include "Util/DFStatics.h"


UEffectParameterInputUI::UEffectParameterInputUI()
{
}

void UEffectParameterInputUI::SpawnSystem(AActor* Target)
{
	UDFStatics::EFFECT_SYSTEM_SCHEDULER->SpawnNow(System, Target, FVector::Zero(), FVector(0,0,1), Context);
}

USystemAndContext* UEffectParameterInputUI::GetSpawnObject()
{
	auto Obj = NewObject<USystemAndContext>();
	Obj->SetContext(Context);
	Obj->SetSystem(System);
	return Obj;
}



