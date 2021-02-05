################################################################################
# Copyright© 2021 Mason DeRoss 
# Released under either the GNU All-permissive License or MIT license. You pick.
#
# use this to build tests for PNG++
################################################################################

set(TESTS_FILES
											#../include/stdafx.h
		tests.cpp							tests.h
		tests_a.cpp
		tests_b.cpp
		tests_byte.cpp)

add_executable(catch2tests "${TESTS_FILES}")
set_target_properties(catch2tests PROPERTIES CXX_STANDARD 20 LANGUAGE CXX LINKER_LANGUAGE CXX)
target_include_directories(catch2tests PUBLIC "." "../" "../include"
							"../directx" "../directx/common" "../directx/common/inc" "../directx/2_Graphics/simpleD3D12"
							"${COMMON_INCLUDE_DIRS}")
target_link_libraries(catch2tests PRIVATE dx12lib) #cuda17 d3d12 d3dcompiler dxgi odbc32 odbccp32 fmt::fmt)
#target_link_directories(catch2tests PUBLIC "." "../directx/2_Graphics/simpleD3D12" "${CMAKE_CURRENT_BINARY_DIR}")
# Microsoft.GSL::GSL
target_precompile_headers(catch2tests PUBLIC ../include/stdafx.h)

#if(MSVC)
	target_compile_options(catch2tests PUBLIC "${WIN64_COMPILE_OPTIONS}")
	target_compile_definitions(catch2tests PUBLIC "${COMMON_DEFINITIONS}")
#else()
	# other compilers
#endif()
