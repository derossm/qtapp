/**********************************************************************************************************************************************\
	Copyright© 2020-2021 Mason DeRoss

	Released under the GNU All-permissive License

	Copying and distribution of this file, with or without modification, are permitted in any medium without royalty,
	provided the copyright notice and this notice are preserved. This file is offered as-is, without any warranty.

	DESCRIPTION:

\**********************************************************************************************************************************************/
#pragma once
#pragma system_header

// Concepts library
#include <concepts>

// Coroutines library
#include <coroutine>

// Utilities library
#include <cstdlib>
#include <csignal>
#include <csetjmp>
#include <cstdarg>
#include <typeinfo>
#include <typeindex>
#include <type_traits>
#include <bitset>
#include <utility>
#include <ctime>
#include <cstddef>
#include <initializer_list>
#include <tuple>
#include <any>
#include <optional>
#include <variant>
#include <compare>
#include <version>
/*#include <source_location>*/ // DOES NOT EXIST YET

// Dynamic memory management
#include <new>
#include <scoped_allocator>

// Numeric limits
#include <climits>
#include <cfloat>
#include <cstdint>
#include <cinttypes>
#include <limits>

// Error handling
#include <exception>
#include <stdexcept>
#include <cassert>
#include <cerrno>

// Strings library
#include <cctype>
#include <cwctype>
#include <cstring>
#include <cwchar>
#include <cuchar>
#include <string>
#include <string_view>
/*#include <format>*/ // DOES NOT EXIST YET

// Containers library
#include <array>
#include <vector>
#include <deque>
#include <list>
#include <forward_list>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <stack>
#include <queue>
#include <span>

// Iterators library
#include <iterator>

// Ranges library
#include <ranges>

// Algorithms library
#include <algorithm>

// Numerics library
#include <cmath>
#include <valarray>
#include <random>
#include <numeric>
#include <ratio>
#include <cfenv>
#include <bit>
#include <numbers>

// Localization library
#include <clocale>

// Input/output library
#include <iosfwd>
/*#include <syncstream>*/ // DOES NOT EXIST YET
#include <cstdio>

#include "std_nomodules.h"

// End of Standard Headers
//=====

#include "os_native.h"

#include <fmt/format.h>
#include <spdlog/spdlog.h>
#include <gsl/gsl>
