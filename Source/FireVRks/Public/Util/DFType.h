#pragma once

UENUM()
enum class DFType : uint8
{
	NONE UMETA(DisplayName = "NONE"),
	TYPED_INT_PARAMETER UMETA(DisplayName = "TYPED_INT_PARAMETER"),
	TYPED_FLOAT_PARAMETER UMETA(DisplayName = "TYPED_FLOAT_PARAMETER"),
	TYPED_VECTOR_PARAMETER UMETA(DisplayName = "TYPED_VECTOR_PARAMETER"),
	TYPED_BOOL_PARAMETER UMETA(DisplayName = "TYPED_BOOL_PARAMETER"),
	TYPED_ENUM_PARAMETER UMETA(DisplayName = "TYPED_ENUM_PARAMETER"),
	
	COMPOUND_BLOCK_PARAMETER UMETA(DisplayName = "COMPOUND_BLOCK_PARAMETER"),
	LIST_BLOCK_PARAMETER UMETA(DisplayName = "LIST_BLOCK_PARAMETER"),
	SYSTEM_INSTANTIATION_PARAMETER UMETA(DisplayName = "LIST_BLOCK_PARAMETER")
};
