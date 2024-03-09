#pragma once
#include "DFId.generated.h"

/**
 * A class which generalizes object ids to both randomizable FGuidS as well as manually specified strings and provides hash-based fast comparison  
 */
USTRUCT()
struct FIREVRKS_API FDFId
{
	GENERATED_BODY()
	FString Id;
	uint32 Hash;
	bool operator==(const FDFId& Other) const;

	/**
	 * Calculates the hash for a DFId.
	 */
	friend uint32 GetTypeHash(const FDFId Id);

	static TSharedPtr<FDFId> Named(FString Fid);
	static TSharedPtr<FDFId> Random();

	FString GetId() const;

	void SetId(FString Id);
};