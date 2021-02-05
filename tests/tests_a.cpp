/**********************************************************************************************************************************************\
	Copyright© 2021 Mason DeRoss

	Released under either the GNU All-permissive License or MIT license. You pick.

	Copying and distribution of this file, with or without modification, are permitted in any medium without royalty,
	provided the copyright notice and this notice are preserved. This file is offered as-is, without any warranty.

	DESCRIPTION:

\**********************************************************************************************************************************************/
#include "stdafx.h"

#include <catch2/catch.hpp>

//#include "DX12Widget.h"
//#include "simpleD3D12.h"

#include "random.h"
#include "tests.h"

namespace uge::testing
{

TEST_CASE("DX12Widget", "[DX12]")
{
	//DX12CudaInterop cudaSample(1280, 720, L"Arbitrary");
	//DX12Widget* cudaPtr = &cudaSample; // abstract base class `DX12Widget` can't be directly constructed

	//::spdlog::info(cudaPtr->GetHeight());
	//::spdlog::info(cudaPtr->GetWidth());
	//::spdlog::info(cudaPtr->GetTitle());

	//REQUIRE(cudaPtr->GetWidth() == 1280);
	//REQUIRE(cudaPtr->GetHeight() == 720);
	//REQUIRE(::std::wstring_view(L"Arbitrary").compare(cudaPtr->GetTitle()) == 0);
	//REQUIRE(::std::wstring_view(L"Arbitrary").compare(cudaPtr->GetTitleView()) == 0);

	//auto wstr{cudaPtr->string2wstring("Arbitrary")};
	//::fmt::print(L"{}", wstr);
	//::spdlog::info(wstr);
	//auto k = ::fmt::format(L"{}", wstr);
	//auto wpath{cudaPtr->GetAssetFullPath("")};

	//void GetHardwareAdapter(_In_ IDXGIFactory2* pFactory, _Outptr_result_maybenull_ IDXGIAdapter1** ppAdapter);
	//void SetCustomWindowText(const char* text);

	//virtual void OnInit() = 0;
	//virtual void OnRender() = 0;
	//virtual void OnDestroy() = 0;

	//cudaPtr->OnKeyDown(0);
	//cudaPtr->OnKeyUp(0);
//
	Random obj;
	auto k = obj.roll<5>(1.0, -1.0);
	for (auto& iter : k)
	{
		std::cout << iter << '\n';
	}

	//void ParseCommandLineArgs(std::span<WCHAR*> argv);

	//::spdlog::info("========================================");
	//::std::cout	<< "\t\t\t\t| "
	//			<< ::fmt::format("red: 0b {:02b} | ", testObjNone.red)
	//			<< ::fmt::format("green: 0b {:02b} | ", testObjNone.green)
	//			<< ::fmt::format("blue: 0b {:02b}", testObjNone.blue)
	//			<< "\n";
	//::spdlog::info("========================================\n");
}

} // end namespace uge::testing
