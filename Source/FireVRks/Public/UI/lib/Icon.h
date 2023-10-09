#pragma once

struct Icon
{
	FString Name;
	FString Path;

	Icon(FString Name, FString Path)
	{
		this->Name = Name;
		this->Path = Path;
	}
};
