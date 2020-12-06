/* ************************************************************************************************************************************************ *\

\* ************************************************************************************************************************************************ */
#pragma once

#include "stdafx.h"

// saw this on a cppcon talk on type erasure
struct TypeErasedNumberRef
{
	template<class Number> TypeErasedNumberRef(Number& n) :
		representation_( (void*)&n ),
		negate_(	[](void* r)->int	{ return -(*(Number*)r); }	),
		not_(		[](void* r)->bool	{ return !(*(Number*)r); }	)
	{}

	void* representation_;
	int (*negate_)(void*);
	bool (*not_)(void*);
	int operator~() const { return negate_(representation_); }
	bool operator!() const { return not_(representation_); }
};
