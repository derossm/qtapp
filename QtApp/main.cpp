/* ************************************************************************************************************************************************ *\

\* ************************************************************************************************************************************************ */
#include "stdafx.h"
#include "QtHeaders.h"
#include "QtApp.h"

#include "Pattern_Command.h"

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
		unknown = 6,
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

	if constexpr (UI::osName() == UI::os::windows || UI::osName() == UI::os::linux || UI::osName() == UI::os::osx)
	{
		// desktop
		QtApp widget;
		widget.show();

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
