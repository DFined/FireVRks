#pragma once
#include "DFId.generated.h"

/**
 * A class which generalizes object ids to both randomizable FGuidS as well as manually specified strings and provides hash-based fast comparison  
 */
UCLASS()
class FIREVRKS_API UDFId : public UObject
{
	GENERATED_BODY()
	FString Id;
	uint32 Hash;
	
public:

	bool operator==(const UDFId& Other) const;

	/**
	 * Calculates the hash for a DFId.
	 */
	FORCEINLINE uint32 GetTypeHash(const UDFId* Id);

	static uint32 PreHash(const FString& Fid);
	static UDFId* Named(UObject* Outer, const FString& Fid);
	static UDFId* Random(UObject* Outer);
};