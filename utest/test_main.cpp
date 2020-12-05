/* ************************************************************************************************************************************************ *\

\* ************************************************************************************************************************************************ */

#include "stdafx.h"

#define CATCH_CONFIG_RUNNER
#pragma warning(push, 0)
#include "catch.hpp"
#pragma warning(pop)

#include "..\QtApp\QtApp.h"

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);

	return Catch::Session().run(argc, argv);
}

TEST_CASE("Test QtApp default constructor", "[QtApp]")
{
	QtApp obj;
	REQUIRE(obj.isEnabled());
}
