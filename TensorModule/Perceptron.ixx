/**********************************************************************************************************************************************\
	Copyright© 2020-2021 Mason DeRoss

	Released under the MIT license.

	Copying and distribution of this file, with or without modification, are permitted in any medium without royalty,
	provided the copyright notice and this notice are preserved. This file is offered as-is, without any warranty.

	DESCRIPTION:

\**********************************************************************************************************************************************/
module;

export module Perceptron;

import std.core;
import std.memory;
import std.threading;
import std.filesystem;

template<typename InputType, typename Weight>
struct Input
{
	InputType input;
	Weight weight;
};

template<typename AF, typename Bias, typename... Inputs>
class Perceptron
{
	Perceptron(Inputs... in)
	{

	}
};
