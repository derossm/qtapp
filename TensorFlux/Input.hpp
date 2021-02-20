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

template<typename InputType, typename Weight>
struct Input
{
	InputType input{};
	Weight weight{};

	constexpr Input() noexcept = default;
	~Input() noexcept = default;

	constexpr Input(InputType input, Weight weight) noexcept : input{input}, weight{weight} {}

	constexpr Input(Input&& other) noexcept
	{
		this->input = other.input;
		this->weight = other.weight;
	}

	constexpr Input(const Input& other) noexcept
	{
		this->input = other.input;
		this->weight = other.weight;
	}

	constexpr Input& operator=(Input&& other) noexcept
	{
		this->input = other.input;
		this->weight = other.weight;
		return *this;
	}

	constexpr Input& operator=(const Input& other) noexcept
	{
		this->input = other.input;
		this->weight = other.weight;
		return *this;
	}

	constexpr Input& operator=(int other) noexcept
	{
		this->input = other;
		this->weight = 1;
		return *this;
	}

	constexpr Input Product() const noexcept
	{
		return Input{this->input * this->weight, 1};
	}

	constexpr Input operator+(const Input& other) const noexcept
	{
		return Input{input * weight + other.input * other.weight, 1};
	}

	constexpr Input operator+(Input&& other) const noexcept
	{
		return Input{input * weight + other.input * other.weight, 1};
	}

	constexpr Input& operator+=(const Input& other) { this = this + other; return *this; }
	constexpr Input& operator+=(Input&& other) { this = this + other; return *this; }

	template<typename InputType, typename Weight>
	friend constexpr  auto operator+(int lhs, const Input<InputType, Weight>& rhs) noexcept;
};

template<typename InputType, typename Weight>
constexpr auto operator+(int lhs, const Input<InputType, Weight>& rhs) noexcept
{
	return lhs + rhs.input * rhs.weight;
}
