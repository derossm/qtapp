cmake_minimum_required(VERSION 3.0.0)
project(QtApp VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_PREFIX_PATH G:/dev/Qt/6.0.0/msvc2019_64)

find_package(QT NAMES Qt6 COMPONENTS Concurrent Core Gui Qml Svg Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Concurrent Core Gui Qml Svg Widgets REQUIRED)

set(PROJECT_SOURCES
		./QtApp/stdafx.h
		./QtApp/QtHeaders.h
		#./QtApp/P_1327G.ixx cmake doesn't support C++20 modules yet
		./QtApp/QtApp.h
		./QtApp/SettingsDialog.h
		./QtApp/QtTablet.h
		./QtApp/P_1442E.h
		./QtApp/P_1446E.h
		./QtApp/stdafx.cpp
		#./QtApp/P_1327G.cpp
		./QtApp/QtTablet.cpp
		./QtApp/QtApp.cpp
		./QtApp/SettingsDialog.cpp
		./QtApp/main.cpp
		./QtApp/QtApp.ui
		./QtApp/Pattern_Command.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
	qt_add_executable(QtApp
		${PROJECT_SOURCES}
	)
else()
	if(ANDROID)
		add_library(QtApp SHARED
			${PROJECT_SOURCES}
		)
	else()
		add_executable(QtApp
			${PROJECT_SOURCES}
		)
	endif()
endif()

target_link_libraries(QtApp PRIVATE
	Qt${QT_VERSION_MAJOR}::Concurrent
	Qt${QT_VERSION_MAJOR}::Core
	Qt${QT_VERSION_MAJOR}::Gui
	Qt${QT_VERSION_MAJOR}::Qml
	Qt${QT_VERSION_MAJOR}::Svg
	Qt${QT_VERSION_MAJOR}::Widgets
)

target_include_directories(QtApp
	PUBLIC G:/dev/Qt/6.0.0/msvc2019_64/include
	PUBLIC G:/dev/gsl/include
	PUBLIC ./QtApp
	PUBLIC ./build/QtApp_autogen/include_Debug
)

target_compile_options(QtApp PUBLIC
	"/Zc:__cplusplus" "/experimental:module" "/permissive-" "/Zc:preprocessor"
	"/Zc:wchar_t" "/W4" "/Zc:inline" "/Od" "/MDd" "/Zc:forScope" "/fp:precise"
	"/arch:AVX2" "/EHsc" "/GS" "/Gd" "/Gm-" "/FC" "/nologo" "/WX-"
)

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

include(CPack)
