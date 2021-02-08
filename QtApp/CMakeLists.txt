################################################################################
# Copyright© 2020-2021 Mason DeRoss 
# Released under the MIT license.
#
#
################################################################################

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_PREFIX_PATH G:/dev/Qt6/6.0.1/msvc2019_64)

find_package(QT NAMES Qt6 COMPONENTS Concurrent Core Gui Qml Svg Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Concurrent Core Gui Qml Svg Widgets REQUIRED)

set(PROJECT_SOURCES
	stdafx.cpp				../include/stdafx.h
	QtApp.cpp				QtApp.h
	SettingsDialog.cpp		SettingsDialog.h
	QtTablet.cpp			QtTablet.h
	QtApp.ui
	main.cpp
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
