/* ************************************************************************************************************************************************ *\

\* ************************************************************************************************************************************************ */

#include "stdafx.h"

#include "QtApp.h"
#include "TypeErasure.h"
#include "P_1442E.h"
#include "P_1446E.h"

import P_1327G;

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
int main(int argc, char* argv[]) //, char** envp)
{
	Problem_1446E obj1446e;
	Problem_1442E<int,int> obj1442e;
	ns::Problem_1327G obj1327g;

	QApplication app(argc, argv);

	QtApp widget;
	QQmlApplicationEngine engine;

	switch (UI::osName())
	{
	// mobile
	case UI::os::android: [[fallthrough]];
	case UI::os::ios:
		engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

		if (engine.rootObjects().isEmpty())
		{
			return EXIT_FAILURE;
		}

		break;
	// desktop
	[[likely]] case UI::os::windows: [[fallthrough]];
	case UI::os::linux: [[fallthrough]];
	case UI::os::osx:
		widget.show();
		break;
	// other
	[[unlikely]] case UI::os::unknown: [[fallthrough]];
	[[unlikely]] default:
		return EXIT_SUCCESS;
	}

	return app.exec();
}
