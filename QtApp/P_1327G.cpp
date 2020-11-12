module;

#include <string>
#include <array>
#include <vector>

#include <charconv>
#include <ranges>
#include <string_view>

#include <regex>

module P_1327G;

//import std.core;
//import std.regex;
//import std.threading;
//import std.memory;
//import std.filesystem;

namespace ns
{
/*********************************************************************************/
	Problem_1327G::Problem_1327G() noexcept
	{
		calculate();
	}

	void Problem_1327G::input(size_t num_, std::vector<std::string> args) noexcept
	{
		num = num_;
		entry = std::move(args.front());
		args.erase(args.begin());
		patterns.swap(args);
	}

	// test case generator atm, replace later TODO with parsing real pattern input
	void Problem_1327G::populatePatterns() noexcept
	{
		using namespace std::literals;
		input(3, std::move(std::vector{"?a?bc?def???ghij??klmn?abcaa"s, "a"s, "aa"s, "abc"s}));
	}

	size_t Problem_1327G::calculate() noexcept
	{
		populatePatterns();

		auto first{entry.find('?')};
		if (size_t i{entry.find('?')}; i != std::string::npos)
		{
			if (i > 0)
			{
				// emplace anything before the first '?' if anything present
				substrings.emplace_back(entry.substr(0, i));
			}
			mask.emplace_back(std::pair{i, std::size_t{0}});

			for (++i; (i = entry.find('?', i)) != std::string::npos; ++i)
			{
				auto pos{mask.back().first};
				if (i > (pos + 1))
				{
					// emplace anything between current and previous '?' if non-sequential '?'
					substrings.emplace_back(entry.substr(pos + 1, i - pos - 1));
				}
				mask.emplace_back(std::pair{i, i - pos});
			}

			if (entry.length() > (mask.back().first + 1))
			{
				// emplace anything after the final '?' if anything remains
				substrings.emplace_back(entry.substr(mask.back().first + 1));
			}
		}
		else
		{
			substrings.emplace_back(std::reference_wrapper(entry)); // try not to excessively copy the string w/ size up to 400,000 characters
		}

		size_t matches{0};
		for (auto& iter : patterns)
		{
			// would it be more efficient to parse every pattern at a sub-stage?
			// might profile that later
			matches += patternMatchWildcards(iter);
			matches += patternMatchSimple(iter);
		}

		return matches;
	}

	size_t Problem_1327G::patternMatchSimple(std::string_view pattern) const noexcept
	{
		size_t weight{0};

		for (auto& iter : substrings)
		{
			const size_t max_len{iter.length()};
			const size_t len{pattern.length()};

			if (max_len >= len)
			{
				const size_t end{max_len - len};
				const auto str{iter.substr(0, max_len)}; // get the actual size, avoid manual checking r-side bound

				for (size_t i{0}; i <= end; ++i)
				{
					[&pattern, &weight](std::string_view str)
					{
						if (str.find(pattern) != std::string::npos)
						{
							// DO STUFF HERE, MATCH
							weight += 1;
						}
					}(str.substr(i, len));
				}
			}
		}

		return weight;
	}

	size_t Problem_1327G::patternMatchWildcards(std::string_view pattern) const noexcept
	{
		size_t weight{0};

		const size_t max_len{entry.length()};
		const size_t len{pattern.length()};

		// it should be impossible for this to be false by construction of pattern, but invalid input is possible
		if (len <= max_len)
		{
			size_t xpos{0};
			for (auto& iter : mask)
			{
				const size_t pos{iter.first};

				// equivalent to (max_len - len) < pos // should I re-arrange this way and make (max_len - len) a constant? 
				// Note: max_len >= len, and max_len >= pos
				if ((max_len - pos) < len)
				{
					// pattern too big for remaining string
					return weight;
				}

				if (xpos > pos)
				{
					// ALREADY PARSED THIS -- is this possible with current algorithm?
					continue;
				}

				const size_t start
				{
					[&pos, &xpos, &len]
					{
						// BEWARE OF OVERFLOW IF REORDERING THESE, i.e. pos > len is not a reasonable assumption before this if check
						if ((pos - xpos) < len)
						{
							// distance between current wildcard and previous end point < pattern len
							// or current wildcard closer than pattern len to entry start
							return xpos;
						}
						else
						{
							// NO OVERLAP, PLENTY OF ROOM to LEFT for FULL SWEEP (possibly limited on right side)
							// and xpos is too far away to be the starting position now
							//assert(pos >= len);
							// EITHER PROVE pos >= len in this branch or add new IF TODO
							// Note: [xpos >= 0], [pos >= 0], and [pos >= xpos]
							// if [len > pos], then [len > (pos - xpos)]
							// but [(pos - xpos) >= len]
							// thus [pos >= len] by contradiction
							return (pos - len) + 1;
						}
					}
				()};

				const size_t size{len + pos - start}; // size either len + pos - xpos or 2*len - 1
				//const auto str{entry.substr(start, size)}; // get the actual size, avoid manual checking r-side bound

				if (const auto str{entry.substr(start, size)}; str.length() >= len)
				{
					const size_t end{str.length() - len};
					for (size_t i{0}; i <= end; ++i)
					{
						[&pattern, &weight](auto&& str)
						{
							//size_t pos{0};
							//while ((pos = str.find('?', pos)) != std::string::npos)
							//for (size_t pos{str.find('?', pos)}; pos != std::string::npos; pos = str.find('?', pos))
							for (size_t pos{0}; (pos = str.find('?', pos)) != std::string::npos;)
							{
								str.at(pos) = pattern.at(pos);
							}

							if (str.find(pattern) != std::string::npos)
							{
								// DO STUFF HERE, MATCH
								weight += 1;
							}
						}(std::move(std::string{str.substr(i, len)}));
					}
					xpos = start + end + 1;
				}
			}
		}

		return weight;
	}

	bool Problem_1327G::patternMatchRegex() const noexcept
	{
		//using namespace std::string_view_literals;
		const static std::regex pattern("([?]*[a-z]*)*");
		std::smatch matches;

		return std::regex_match(entry, matches, pattern);
	}
/*********************************************************************************/
}
