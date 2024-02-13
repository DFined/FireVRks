#include "FX/Niagara/v2/FormalParameter/CompoundableFormalParameter.h"

#include "FX/Niagara/v2/ParamUtil.h"
#include "FX/Niagara/v2/ValueEqualsPredicate.h"
#include "FX/Niagara/v2/FormalParameter/BoolFormalParameter.h"

UBlockFormalParameter* UCompoundableFormalParameter::GetBlockParam()
{
	return BlockParam;
}