#pragma once

/**
 * DFined util class
 */
class DFU
{
	
public:
	template <class SRC, typename RES>
	static RES IfNotNullMapElse(SRC* Src, RES DefaultValue, RES (*Mapper)(SRC*));

};

