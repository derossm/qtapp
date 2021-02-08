/**********************************************************************************************************************************************\
	Copyright© 2020-2021 Mason DeRoss

	Released under the MIT license.

	Copying and distribution of this file, with or without modification, are permitted in any medium without royalty,
	provided the copyright notice and this notice are preserved. This file is offered as-is, without any warranty.

	DESCRIPTION:

\**********************************************************************************************************************************************/
#include "stdafx.h"

#include "QtApp.h"

namespace UI
{
	enum class os
	{
		error = 0,
		// mobile
		android = 1,
		ios = 2,
		// desktop
		windows = 3,
		linux = 4,
		osx = 5,
		// other
		unknown = 7,
	};

	constexpr os osName()
	{
		// mobile
#if defined(Q_OS_ANDROID)
		return os::android;
#elif defined(Q_OS_IOS)
		return os::ios;
		// desktop
#elif defined(Q_OS_WIN)
		return os::windows;
#elif defined(Q_OS_LINUX)
		return os::linux;
#elif defined(Q_OS_MAC)
		return os::osx;
		// other
#else
		return os::unknown;
#endif
	}
}

//ENTRY:mainCRTStartup
int main(int argc, char* argv[])
{
	QApplication app(argc, argv);

	auto ptr = std::make_unique<char[]>(60);
	std::cout << sizeof(ptr);

	auto k0 = 1 << 0;
	auto k1 = 1 << 1;
	auto k2 = 1 << 2;

	if constexpr (UI::osName() == UI::os::windows || UI::osName() == UI::os::linux || UI::osName() == UI::os::osx)
	{
		// desktop
		QtApp widget;
		widget.show();

		//Examples::Editor<QtApp> e(&widget);
		//Examples::TextEditor<Examples::Editor<QtApp>> ted(std::move(e));
		//ted.InputHandler(std::string{"Test000ZYX"});

		return app.exec();
	}
	else if constexpr (UI::osName() == UI::os::android || UI::osName() == UI::os::ios)
	{
		// mobile
		QQmlApplicationEngine engine;
		engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
		if (engine.rootObjects().isEmpty())
		{
			return EXIT_FAILURE;
		}

		return app.exec();
	}
	else
	{
		// other
		return EXIT_SUCCESS;
	}
}
