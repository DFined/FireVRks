#include "GenericLauncherArray.h"

FString UGenericLauncherArray::GetArrayName() const
{
	return ArrayName;
}

void UGenericLauncherArray::SetArrayName(const FString& NewArrayName)
{
	this->ArrayName = NewArrayName;
}

void UGenericLauncherArray::AddLauncher(AGenericFireworkLauncher* Launcher)
{
	Launchers.Add(Launcher);
}

int UGenericLauncherArray::GetSize()
{
	return Launchers.Num();
}
