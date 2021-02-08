/**********************************************************************************************************************************************\
	Copyright© 2020-2021 Mason DeRoss

	Released under the MIT License.

	Copying and distribution of this file, with or without modification, are permitted in any medium without royalty,
	provided the copyright notice and this notice are preserved. This file is offered as-is, without any warranty.

	DESCRIPTION:

\**********************************************************************************************************************************************/
#pragma once

#include <memory>
#include <array>

#include <concepts>
#include <type_traits>

#include <ranges>
#include <algorithm>

#include <random>

class Random
{
	using RandomEngine = std::mt19937;
	std::unique_ptr<RandomEngine> m_rng;

public:
	auto GetRNG() noexcept
	{
		std::random_device rd;
		std::array<uint32_t, 624> numbers;
		std::ranges::generate(numbers, [&rd]{ return rd(); });

		std::unique_ptr<RandomEngine> rval;
		try
		{
			std::seed_seq sseq(numbers.begin(), numbers.end());
			rval = std::make_unique<RandomEngine>(RandomEngine(sseq));
		}
		catch (...)
		{
			// FIXME write some safe version i.e.
			//rval = safe_mt19937(sseq);
			//exit(EXIT_FAILURE);
			rval.reset();
		}

		return rval;
	}

	inline Random() noexcept : m_rng{GetRNG()} {}

	inline void reset() noexcept
	{
		m_rng.reset();
		m_rng = GetRNG();
	}

	template<size_t Count, typename T, typename U>
	auto roll_impl(U&& distribution) const noexcept
	{
		std::array<T, Count> result;
		std::ranges::generate(result, [&]{ return distribution(*m_rng.get()); });

		return result;
	}

	template<size_t Count = 1, typename T>
		requires std::integral<T>
	auto roll(T Max, T Min = 1) const //noexcept
	{
		std::uniform_int_distribution<T> distribution(Min, Max);

		return roll_impl<Count, T, decltype(distribution)>(std::move(distribution));
	}

	template<size_t Count = 1, typename T>
		requires std::floating_point<T>
	auto roll(T Max, T Min = 1.0) const //noexcept
	{
		std::uniform_real_distribution<T> distribution(Min, Max);

		return roll_impl<Count, T, decltype(distribution)>(std::move(distribution));
	}
};
