#include "Util/DFU.h"

template <class SRC, typename RES>
RES DFU::IfNotNullMapElse(SRC* Src, RES DefaultValue, RES (* Mapper)(SRC*))
{
	if (Src == nullptr) return DefaultValue;
	return Mapper(Src);
}
