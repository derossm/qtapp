#pragma once
#include <concepts>
#include <type_traits>
#include <ranges>
#include <algorithm>
#include <array>
#include <vector>
#include <random>
#include <memory>

//template<typename T = int>
//	requires (std::integral<T> || std::floating_point<T>)
class Random
{
	std::unique_ptr<std::mt19937> m_rng;

public:
	std::mt19937 GetRNG() noexcept
	{
		std::random_device rd;
		std::array<uint32_t, 624> numbers;
		std::ranges::generate(numbers, [&rd]{ return rd(); });

		std::seed_seq sseq(numbers.begin(), numbers.end());

		return std::mt19937(sseq);
	}

	inline Random() noexcept : m_rng{std::make_unique<std::mt19937>(GetRNG())} {}

	void reset() noexcept
	{
		m_rng.reset();
		m_rng = std::make_unique<std::mt19937>(GetRNG());
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
	auto roll(T Max, T Min = 1) const noexcept
	{
		std::uniform_int_distribution<T> distribution(Min, Max);

		return roll_impl<Count, T, decltype(distribution)>(std::move(distribution));
	}

	template<size_t Count = 1, typename T>
		requires std::floating_point<T>
	auto roll(T Max, T Min = 1.0) const noexcept
	{
		std::uniform_real_distribution<T> distribution(Min, Max);

		return roll_impl<Count, T, decltype(distribution)>(std::move(distribution));
	}
};

/*template<typename T = double>
	requires std::is_floating_point_v<T>
class Random
{
	std::mt19937 m_rng;

public:
	inline constexpr Random() noexcept : m_rng{GetRNG()} {}

	std::mt19937 GetRNG()
	{
		std::random_device rd;
		std::array<uint32_t, 624> numbers;
		std::ranges::generate(numbers, [&rd]{ return rd(); });

		std::seed_seq sseq(numbers.begin(), numbers.end());

		return std::mt19937(sseq);
	}
		for (size_t i; i < Count, ++i)
		{
			result.emplace_back(distribution(m_rng));
		}

	template<size_t Count>
	auto roll(long double Max, long double Min = 1.0)
	{
		std::uniform_real_distribution<T> distribution(Min, Max);

		std::array<T, Count> result;
		std::for_each_n(result, Count)
		{
			result.emplace_back(distribution(m_rng));
		}

		return result;
	}

		//std::array<T, Count> result;
		/*for (size_t i; i < Count, ++i)
		{
			result.emplace_back(distribution(m_rng));
		}
		//std::ranges::generate(result, [&]{ return distribution(m_rng); });

		//return result;
		//std::array<T, Count> result;
		for (size_t i; i < Count, ++i)
		{
			result.emplace_back(distribution(m_rng));
		}*
		//std::ranges::generate(result, [&]{ return distribution(m_rng); });

		//return result;
};*/
