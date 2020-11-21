#pragma once

#include "stdafx.h"

#include <map>

/* ******************************************************************************** *\
	solution to https://codeforces.com/problemset/problem/1442/E

\* ******************************************************************************** */

template<class K, class V>
class Problem_1442E
{
public:
	Problem_1442E()
	{
		// remove from a tree all sub-elements not of opposing color
		std::map<K,V> Tree{};
		auto pred = [](const auto& in) -> bool { return true; };
		std::erase_if(Tree, pred);
	}
};
