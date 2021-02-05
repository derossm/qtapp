################################################################################
#
#
#
################################################################################

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

cmake_minimum_required(VERSION 3.7.2)
project("Untitled Game Engine" VERSION 0.0.1 LANGUAGES CXX)

set(top_srcdir "${CMAKE_CURRENT_SOURCE_DIR}")
set(top_builddir "${CMAKE_CURRENT_BINARY_DIR}")

set(PACKAGE_NAME "${PROJECT_NAME}")
string(REGEX REPLACE "${PROJECT_NAME}" "UGE" PACKAGE_SHORTNAME "${PACKAGE_NAME}")

set(PACKAGE_TARNAME "${PACKAGE_SHORTNAME}")
set(PACKAGE_VERSION "${PROJECT_VERSION}")
set(PACKAGE_STRING "${PROJECT_NAME} v${PROJECT_VERSION}")
set(PACKAGE_BUGREPORT "https://github.com/derossm/UGE")

set(PACKAGE_COPYRIGHT "Copyright© 2021")
set(PACKAGE_LICENSE "MIT License")

string(CONCAT WINDOWS_RC_VERSION "${PROJECT_VERSION_MAJOR}, " "${PROJECT_VERSION_MINOR}, ${PROJECT_VERSION_PATCH}, 0")

# sans-hyphen: used by bash-completion scripts.
string(TOLOWER "${PACKAGE_SHORTNAME}" PROGRAM_SPREFIX)
# hyphenated: used almost everywhere else.
set(PROGRAM_PREFIX "${PROGRAM_SPREFIX}-")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_language(CUDA)

set(ARCHITECTURE "x64")
set(PLATFORM "windows")

set(VCPKG_DIR "G:/dev/vcpkg/installed")
set(VCPKG_INCLUDE_DIR "${VCPKG_DIR}/${ARCHITECTURE}-${PLATFORM}/include")
set(VCPKG_LIBRARY_DIR "${VCPKG_DIR}/${ARCHITECTURE}-${PLATFORM}/lib")

set(CUDA_DIR "G:/dev/cuda/toolkit")
set(CUDA_INCLUDE_DIR "${CUDA_DIR}/include")
set(CUDA_LIBRARY_DIR "${CUDA_DIR}/lib")

set(COMMON_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}" "${VCPKG_INCLUDE_DIR}" "${CUDA_INCLUDE_DIR}")
set(COMMON_DEFINITIONS "WIN32_LEAN_AND_MEAN" "NOMINMAX" "UNICODE" "_UNICODE")
set(WIN64_COMPILE_OPTIONS
	"/Zc:__cplusplus" "/Zc:inline" "/Zc:wchar_t"
	"/fp:precise" "/GS" "/Gd" "/Gm-" "/FC" "/EHsc" "/nologo" "/WX-" "/MDd" "/MP"
	"/W4" "/Od"
	"/arch:AVX2"
	"/permissive-" "/Zc:preprocessor"
	"/experimental:external" "/external:anglebrackets" "/external:W0"
	#"/analyze" "/analyze:plugin EspXEngine.dll"
	#"/analyze:ruleset ../rulesets/CppCoreCheckRules.ruleset"
	#"/RunCodeAnalysis=true" "/CodeAnalysisRuleSet=CppCoreCheckRules.ruleset"
	#"/fsanitize=address"
	#"-Wno-microsoft-template-shadow"
	#"/wd4514"
)

#set_property(GLOBAL APPEND PROPERTY CXX_STANDARD 20)
#set_property(GLOBAL APPEND PROPERTY LANGUAGE CXX)
#set_property(GLOBAL APPEND PROPERTY LINKER_LANGUAGE CXX)

# windows C++ wrappers
find_package(WIL CONFIG REQUIRED)
if(WIL_FOUND)
	set(HAVE_WIL TRUE)
endif()

# directxmath : DirectXMath SIMD C++ math library
find_package(directxmath CONFIG REQUIRED)
if(directxmath_FOUND)
	set(HAVE_DIRECTXMATH TRUE)
endif()

# directxtk12 : A collection of helper classes for writing DirectX12
find_package(directxtk12 CONFIG REQUIRED)
if(directxtk12_FOUND)
	set(HAVE_DIRECTXTK12 TRUE)
endif()

find_package(Microsoft.GSL CONFIG REQUIRED)
if(Microsoft.GSL_FOUND)
	set(HAVE_MS_GSL TRUE)
endif()

find_package(Catch2 CONFIG REQUIRED)
if(Catch2_FOUND)
	set(HAVE_CATCH2 TRUE)
endif()

find_package(fmt CONFIG REQUIRED)
if(fmt_FOUND)
	set(HAVE_FMT TRUE)
endif()

find_package(spdlog CONFIG REQUIRED)
if(spdlog_FOUND)
	set(HAVE_SPDLOG TRUE)
endif()

find_package(rapidjson CONFIG REQUIRED)
if(rapidjson_FOUND)
	set(HAVE_RAPIDJSON TRUE)
endif()

configure_file(cmake/config.h.cin config.h)
configure_file(src/resource.rc.in src/resource.rc)

foreach(SUBDIR include QtApp tests)
	add_subdirectory("${SUBDIR}")
endforeach()
