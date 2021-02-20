/**********************************************************************************************************************************************\
	Copyright© 2020-2021 Mason DeRoss

	Released under the MIT license.

	Copying and distribution of this file, with or without modification, are permitted in any medium without royalty,
	provided the copyright notice and this notice are preserved. This file is offered as-is, without any warranty.

	DESCRIPTION:

\**********************************************************************************************************************************************/
#include "stdafx.h"

template<typename InputType, typename Weight>
struct Input
{
	InputType input{};
	Weight weight{};

	constexpr Input() noexcept = default;
	constexpr ~Input() noexcept = default;

	constexpr Input(InputType input, Weight weight) noexcept : input{input}, weight{weight} {}

	constexpr Input(Input<InputType, Weight>&& other) noexcept
	{
		this->input = other.input;
		this->weight = other.weight;
	}

	constexpr Input(const Input<InputType, Weight>& other) noexcept
	{
		this->input = other.input;
		this->weight = other.weight;
	}

	constexpr Input<InputType, Weight>& operator=(Input<InputType, Weight>&& other) noexcept
	{
		this->input = other.input;
		this->weight = other.weight;
		return *this;
	}

	constexpr Input<InputType, Weight>& operator=(const Input<InputType, Weight>& other) noexcept
	{
		this->input = other.input;
		this->weight = other.weight;
		return *this;
	}

	constexpr Input<InputType, Weight>& operator=(int other) noexcept
	{
		this->input = other;
		this->weight = 1;
		return *this;
	}

	constexpr int Product() noexcept
	{
		return input * weight;
		//return 0;
	}

	constexpr auto operator+(const Input<InputType, Weight>& other) noexcept
	{
		return input * weight + other.input * other.weight;
		//return 0;
	}

	constexpr auto operator+(Input<InputType, Weight>&& other) noexcept
	{
		return input * weight + other.input * other.weight;
		//return 0;
	}

	auto operator+=(const Input<InputType, Weight>& other) = delete;
	auto operator+=(Input<InputType, Weight>&& other) = delete;

	template<typename InputType, typename Weight>
	friend constexpr auto operator+(const Input<InputType, Weight>& lhs, const Input<InputType, Weight>& rhs) noexcept;

	//template<typename InputType, typename Weight>
	//friend auto operator+(Input<InputType, Weight>&& lhs, const Input<InputType, Weight>& rhs) noexcept;

	//template<typename InputType, typename Weight>
	//friend auto operator+(const Input<InputType, Weight>& lhs, Input<InputType, Weight>&& rhs) noexcept;

	//template<typename InputType, typename Weight>
	//friend auto operator+(Input<InputType, Weight>&& lhs, Input<InputType, Weight>&& rhs) noexcept;

	template<typename InputType, typename Weight>
	friend constexpr auto operator+(int lhs, const Input<InputType, Weight>& rhs) noexcept;
};

template<typename InputType, typename Weight>
constexpr auto operator+(int lhs, const Input<InputType, Weight>& rhs) noexcept
{
	return lhs + rhs.input * rhs.weight;
	//return 0;
}

template<typename InputType, typename Weight>
constexpr auto operator+(const Input<InputType, Weight>& lhs, const Input<InputType, Weight>& rhs) noexcept
{
	return lhs.input * lhs.weight + rhs.input * rhs.weight;
	//return 0;
}

//template<typename InputType, typename Weight>
//auto operator+(const Input<InputType, Weight>& lhs, Input<InputType, Weight>&& rhs)
//{
//	return lhs.input * lhs.weight + rhs.input * rhs.weight;
//	//return 0;
//}

//template<typename InputType, typename Weight>
//auto operator+(Input<InputType, Weight>&& lhs, const Input<InputType, Weight>& rhs)
//{
//	return lhs.input * lhs.weight + rhs.input * rhs.weight;
//	//return 0;
//}

//template<typename InputType, typename Weight>
//auto operator+(Input<InputType, Weight>&& lhs, Input<InputType, Weight>&& rhs)
//{
//	return lhs.input * lhs.weight + rhs.input * rhs.weight;
//	//return 0;
//}

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
	constexpr auto Sum() noexcept
	{
		return std::accumulate(inputs.cbegin(), inputs.cend(), Input{0,0});
		//return std::accumulate(inputs.cbegin(), inputs.cend(), Input{0,0}, [](const auto& lhs, const auto& rhs){ return 0;});
		//return std::accumulate(inputs.cbegin(), inputs.cend(), Input{0,0}, [](auto& iter){ return iter.Product(); });
	}

	// apply the activation function to introduce non-linearity
	constexpr auto Activate() noexcept
	{
		return activationFunction(bias + Sum());
	}

	// output result y = g(bias + X*W)
	constexpr auto Output() noexcept
	{
		return Activate();
	}
};
