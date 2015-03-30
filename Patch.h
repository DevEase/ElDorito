#pragma once

#include "Pointer.h"

#include <initializer_list>
#include <array>
#include <vector>

// Todo: Stray away from vectors, use initializer list to stick to compile-time constant data
//       without any run-time overhead. Optimized code should propogate to simple memcpys

class Patch
{
public:
	Patch()
		:
		Offset(0)
	{
	}
	Patch(size_t Offset,
		  std::initializer_list<uint8_t> Data,
		  std::initializer_list<uint8_t> Reset = {})
		  :
		  Offset(Offset), Data(Data), Orig(Reset)
	{
	}

	inline void Apply(Pointer offset = Pointer::Base()) const
	{
		if( Data.size() )
		{
			offset(Offset).Write(&Data[0], Data.size());
		}
	}

	inline void Reset(Pointer offset = Pointer::Base()) const
	{
		if( Orig.size() )
		{
			offset(Offset).Write(&Orig[0], Orig.size());
		}
	}

	static inline void NopFill(Pointer offset, size_t length)
	{
		memset(offset, 0x90, length);
	}
private:
	size_t Offset;
	const std::vector<uint8_t> Data, Orig;
};