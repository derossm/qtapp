/* ************************************************************************************************************************************************ *\

\* ************************************************************************************************************************************************ */

#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

#include "..\QtApp\QtApp.h"

#include <charconv>
#include <new>

static int argc_;
static char** argv_;

int main(int argc, char* argv[])
{
	argc_ = argc;
	argv_ = argv;

	int result = Catch::Session().run(argc, argv);
}

TEST_CASE("Test", "[QtApp]")
{
	auto argc = argc_;
	auto argv = new char*(*argv_);
	QApplication app(argc, argv);
	QtApp obj;
	REQUIRE(obj.isEnabled());
	delete argv;
}
