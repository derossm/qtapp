/* ************************************************************************************************************************************************ *\
	solution to https://codeforces.com/problemset/problem/1446/E

	need coordinate struct (x, y) for cells
	should multi-map work for 3-edged graph? or some simpler way to track adjacency
	ideally create a bitset 2d array to quickly compare neighbors, but I only know
	the manual way to do this atm; must research multimaps

\* ************************************************************************************************************************************************ */

#pragma once

#include "stdafx.h"

class BitMatrix
{
	std::vector<bool> _matrix;
	short _n;
	short _size;

public:
	BitMatrix() : _n{1}, _size{1}, _matrix{false}
	{
	}

	template<std::integral T>
	void flip(T x, T y)
	{
		if (x < _n && y < _n) [[likely]]
		{
			_matrix[y*_size + x].flip();
		}
	}

	template<std::integral T>
	[[nodiscard]]
	bool value(T x, T y)
	{
		return x < _n && y < _n && _matrix[y*_size + x];
	}
};

class Problem_1446E
{
	BitMatrix matrix;
public:

};
