/* ************************************************************************************************************************************************ *\

\* ************************************************************************************************************************************************ */
#include "stdafx.h"
#include "QtHeaders.h"

#include "QtApp.h"
#include "QtTablet.h"

#define CATCH_CONFIG_RUNNER
#pragma warning(push, 0)
#include <catch2\catch.hpp>
#pragma warning(pop)

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);

	return Catch::Session().run(argc, argv);
}

//static_assert(std::has_unique_object_representations_v<QtApp>, "Non-standard object representation for QtApp");

TEST_CASE("Test QtApp default constructor", "[QtApp]")
{
	QtApp obj;
	REQUIRE(obj.isEnabled());
}
