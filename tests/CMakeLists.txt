################################################################################
# Copyright© 2020-2021 Mason DeRoss 
# Released under the MIT license.
#
# use this to build tests
################################################################################

set(TESTS_FILES
		tests.cpp							tests.h
		tests_a.cpp
		tests_byte.cpp)

add_executable(catch2tests "${TESTS_FILES}")
set_target_properties(catch2tests PROPERTIES CXX_STANDARD 20 LANGUAGE CXX LINKER_LANGUAGE CXX)
target_include_directories(catch2tests PUBLIC
		"." "../" "../include"
		"../directx" "../directx/common" "../directx/common/inc"
		"${COMMON_INCLUDE_DIRS}")
target_link_libraries(catch2tests PRIVATE dx12lib)
target_precompile_headers(catch2tests PUBLIC ../include/stdafx.h)

target_compile_options(catch2tests PUBLIC "${WIN64_COMPILE_OPTIONS}")
target_compile_definitions(catch2tests PUBLIC "${COMMON_DEFINITIONS}")
