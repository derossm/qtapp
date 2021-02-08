/**********************************************************************************************************************************************\
	Copyright© 2020-2021 Mason DeRoss

	Released under the MIT License.

	Copying and distribution of this file, with or without modification, are permitted in any medium without royalty,
	provided the copyright notice and this notice are preserved. This file is offered as-is, without any warranty.

	DESCRIPTION:

\**********************************************************************************************************************************************/
#pragma once
#pragma system_header

#ifdef _WIN32
	#ifndef WIN32_LEAN_AND_MEAN
		#define WIN32_LEAN_AND_MEAN
	#endif
	#ifndef NOMINMAX
		#define NOMINMAX
	#endif

#pragma warning(push, 0)
	#include <windows.h>
	#include <wrl.h>
	#include <shellapi.h> // for ExtractIcon()
	#include <aclapi.h>

	#include <tchar.h>
	#include <shlobj.h>
	#include <process.h>
	#include <io.h>
	#include <winioctl.h>
	#include <sys/stat.h>
	#include <sys/types.h>

	#include <strsafe.h>
	#include <sddl.h>
	#include <winternl.h>
	#include <initguid.h>
	#include <wchar.h>
	#include <mmsystem.h>
	#include <commctrl.h> // for InitCommonControls() 
	#include <new.h> // for placement new

// CRT's memory leak detection
#if defined(DEBUG) || defined(_DEBUG)
	#include <crtdbg.h>
#endif
#pragma warning(pop)

#endif // #ifdef _WIN32
