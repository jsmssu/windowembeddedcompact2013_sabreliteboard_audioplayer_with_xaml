// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#pragma comment(linker, "/nodefaultlib:libc.lib")
#pragma comment(linker, "/nodefaultlib:libcd.lib")

// Windows Header Files:
#include <windows.h>

// Xaml Runtime Header Files
#include <XamlRuntime.h>
#include <XRDelegate.h>
#include <XRPtr.h>
#include <XRCustomControl.h>

// IUnknown
extern "C" const GUID __declspec(selectany)IID_IUnknown = __uuidof(IUnknown);

// Resource type for XAML files
#define RT_XAML L"XAML"

// Application headers
#include "App.h"
#include "resource.h"

// TODO: reference additional headers your program requires here
