/**********************************************************************************************************************************************\
	Copyright© 2020-2021 Mason DeRoss

	Released under the MIT license.

	Copying and distribution of this file, with or without modification, are permitted in any medium without royalty,
	provided the copyright notice and this notice are preserved. This file is offered as-is, without any warranty.

	DESCRIPTION:

\**********************************************************************************************************************************************/
#include "stdafx.h"

#include <catch2/catch.hpp>

#include "tests.h"

#include "../TensorFlux/Perceptron.hpp"

namespace uge::testing
{

	TEST_CASE("Perceptron construction", "[TensorFlux]")
	{
		Input<int, int> in_a{1, 1};
		const auto af{[](auto&& iter){ return iter; }};
		Perceptron p1(af, 1, in_a);
		Perceptron p2(af, 1, in_a, in_a);
		Perceptron p3(af, 1, in_a, in_a, in_a);
		Perceptron p0(af, 1, std::move(in_a));
		spdlog::info("{}", p0.Output());
		spdlog::info("{}", p1.Output());
		spdlog::info("{}", p2.Output());
		spdlog::info("{}", p3.Output());
	}

} // end namespace uge::testing
