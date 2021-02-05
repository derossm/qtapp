/**********************************************************************************************************************************************\
	Copyright© 2020-2021 Mason DeRoss

	Released under the GNU All-permissive License

	Copying and distribution of this file, with or without modification, are permitted in any medium without royalty,
	provided the copyright notice and this notice are preserved. This file is offered as-is, without any warranty.

	DESCRIPTION:

\**********************************************************************************************************************************************/
#pragma once

#include "stdafx.h"

namespace uge
{

template<typename E, E N = E::count>
	requires ::std::is_enum_v<::std::remove_reference_t<E>>
class BitSet : public ::std::bitset<static_cast<size_t>(N)>
{
public:
	// only overloading methods with parameterized variations, so any/all/none_of etc don't need overloaded
	inline BitSet<E, N>& set() noexcept
	{
		this->bitset::set();
		return *this;
	}

	inline BitSet<E, N>& set(E pos, bool value = true) noexcept
	{
		this->bitset::set(static_cast<size_t>(pos), value);
		return *this;
	}

	inline BitSet<E, N>& set(size_t pos, bool value = true) noexcept
	{
		this->bitset::set(pos, value);
		return *this;
	}

	template<typename... Es>
		requires (::std::is_enum_v<::std::remove_reference_t<Es>> && ...) || (::std::is_integral<::std::remove_reference_t<Es>> && ...)
	inline BitSet<E, N>& set(bool value, Es... es) noexcept
	{
		auto ev = {es...};
		// there should be a better way to mass set contiguous ranges, but this can allow any number of non-contiguous bits to be specified
		::std::for_each(ev.begin(), ev.end(), [&](auto& iter){ this->bitset::set(static_cast<size_t>(iter), value); });
		return *this;
	}

	inline BitSet<E, N>& flip() noexcept
	{
		this->bitset::flip();
		return *this;
	}

	inline BitSet<E, N>& flip(E pos) noexcept
	{
		this->bitset::flip(static_cast<size_t>(pos));
		return *this;
	}

	inline BitSet<E, N>& flip(size_t pos) noexcept
	{
		this->bitset::flip(pos);
		return *this;
	}

	inline BitSet<E, N>& reset() noexcept
	{
		this->bitset::reset();
		return *this;
	}

	inline BitSet<E, N>& reset(E pos) noexcept
	{
		this->bitset::reset(static_cast<size_t>(pos));
		return *this;
	}

	inline BitSet<E, N>& reset(size_t pos) noexcept
	{
		this->bitset::reset(pos);
		return *this;
	}

	inline bool test(E pos) const noexcept
	{
		return this->bitset::test(static_cast<size_t>(pos));
	}

	inline bool test(size_t pos) const noexcept
	{
		return this->bitset::test(pos);
	}
};

} // end namespace uge
