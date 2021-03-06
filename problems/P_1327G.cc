/* ************************************************************************************************************************************************ *\
	solution to https://codeforces.com/problemset/problem/1327/G

	NOTE - had to break up into .cpp the implementation details to get some future C++20 module related things to compile with old Qt library code
	otherwise errors prevent compilation -- can't use import std.* either, because Qt uses #include versions of same code and causes a lot of errors

\* ************************************************************************************************************************************************ */
//module;

#include "stdafx.h"

//export module P_1327G;

namespace ns
{
//export
//{
	class Problem_1327G
	{
		size_t num;

		std::string entry;							// up to length 400,000
		std::vector<std::string> substrings;		// break entry into up to 15 substrings for non-wildcard parsing
		std::vector<std::string> patterns;
		std::vector<std::pair<size_t, size_t>> mask;
		//std::map<size_t, size_t> mask;

	public:
		Problem_1327G() noexcept;

		void input(size_t num_, std::vector<std::string> args) noexcept;

		// test case generator atm, replace later TODO with parsing real pattern input
		void populatePatterns() noexcept;

		[[nodiscard]]
		size_t calculate() noexcept;

		[[nodiscard]]
		size_t patternMatchSimple(std::string_view pattern) const noexcept;

		[[nodiscard]]
		size_t patternMatchWildcards(std::string_view pattern) const noexcept;

		[[nodiscard]]
		bool patternMatchRegex() const noexcept;
	};
//} // export
} // namespace
