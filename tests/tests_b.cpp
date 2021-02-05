/**********************************************************************************************************************************************\
	Copyright© 2021 Mason DeRoss

	Released under either the GNU All-permissive License or MIT license. You pick.

	Copying and distribution of this file, with or without modification, are permitted in any medium without royalty,
	provided the copyright notice and this notice are preserved. This file is offered as-is, without any warranty.

	DESCRIPTION:

\**********************************************************************************************************************************************/
#include "stdafx.h"

#include <catch2/catch.hpp>

#include "common.h"

#include "tests.h"

namespace uge::testing
{

TEST_CASE("convert_color_space_impl tests", "[PNGPP]")
{
	// TODO generate more interesting default values
	//constexpr const byte BASE_OFFSET{147};
	//png_row_info rowInfo;
	//rowInfo.rowbytes = static_cast<size_t>(16);

	//::std::array<byte, 16> row;

	//::std::iota(row.begin(), row.begin() + row.max_size()/static_cast<size_t>(2), BASE_OFFSET);
	//::std::fill(row.begin() + row.size(), row.end(), static_cast<byte>(0));

	//::png::detail::convert_color_space_impl<rgb_pixel>::expand_8_to_16(nullptr, &rowInfo, row.data());
	//for (size_t i{0}; i < row.max_size(); i += 2)
	//{
	//	REQUIRE(row[i] == 0);
	//}
	//for (size_t i{1}, k{0}; i < row.max_size(); i += 2, ++k)
	//{
	//	REQUIRE(row[i] == k + BASE_OFFSET);
	//}
}

} // end namespace png::testing
