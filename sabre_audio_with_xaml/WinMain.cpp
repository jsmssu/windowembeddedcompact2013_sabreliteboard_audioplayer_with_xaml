#include "stdafx.h"
#include "App.h"

// ============================================================================
//  WinMain
//
//  Description: Set the window creation parameters for this application.
//
//  Parameters:  hInstance - Handle to the current instance of the application.
//               hInstPrev - This parameter is always NULL.
//               lpCmdLine - Command line for the application, excluding the program name.
//               nCmdShow - Specifies how the window is to be shown.
// ============================================================================


INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE /*hInstPrev*/, LPWSTR /*lpCmdLine*/, int /*nShowCmd*/)
{
    App AppInstance;
    HRESULT hr = AppInstance.Initialize(hInstance);
    if(SUCCEEDED(hr))
    {
        hr = AppInstance.Run();
    }
    return AppInstance.GetWinMainResultCode();
}