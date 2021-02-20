/**********************************************************************************************************************************************\
	Copyright© 2020-2021 Mason DeRoss

	Released under the MIT license.

	Copying and distribution of this file, with or without modification, are permitted in any medium without royalty,
	provided the copyright notice and this notice are preserved. This file is offered as-is, without any warranty.

	DESCRIPTION:
		My niave implementation of a Perceptron as described in MIT Deep Learning course
\**********************************************************************************************************************************************/
#pragma once

#include "stdafx.h"

#include "Input.hpp"

// open questions
// should a Perceptron allow:
//	adding/removing/modifying inputs after construction
//	modifying activation function
//	modifying bias
template<typename AF, typename Bias, typename... Inputs>
class Perceptron
{
	AF activationFunction;
	Bias bias;
	std::vector<std::common_type_t<Inputs...>> inputs;
public:
	constexpr Perceptron(AF activationFunction, Bias bias, Inputs... in) noexcept : activationFunction{activationFunction}, bias{bias}
	{
		inputs.reserve(sizeof...(Inputs));
		(inputs.emplace_back(std::forward<Inputs>(in)), ...);
	}

	/*Perceptron(AF activationFunction, Bias bias, Inputs&&... in) noexcept : activationFunction{activationFunction}, bias{bias}
	{
		inputs.reserve(sizeof...(Inputs));
		(inputs.push_back(std::forward<Inputs>(in)), ...);
	}*/

	/*Perceptron(AF activationFunction, Bias bias, const Inputs&... in) noexcept : activationFunction{activationFunction}, bias{bias}
	{
		inputs.reserve(sizeof...(Inputs));
		(inputs.emplace_back(in), ...);
	}*/

	// sum the input/weight pairs
	constexpr auto Sum() const noexcept
	{
		return std::accumulate(inputs.cbegin(), inputs.cend(), Input{0,0}, [](const auto& lhs, const auto& rhs){ return lhs + rhs.Product(); });
	}

	// apply the activation function to introduce non-linearity
	constexpr auto Activate() const noexcept
	{
		return activationFunction(bias + Sum());
	}

	// output result y = g(bias + X*W)
	constexpr auto Output() const noexcept
	{
		return Activate();
	}
};
