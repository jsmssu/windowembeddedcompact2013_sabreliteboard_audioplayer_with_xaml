#include "stdafx.h"
#include "sabre_audio_with_xamlGenerated.h"
#include "App.h"
#include "MainPage.h"

// The MAX_LOADSTRING constant needs to be equal to or greater
// than the length of the string referenced by IDS_APP_TITLE
#define MAX_LOADSTRING 100

// ============================================================================
// Static class member instantiation.
// ============================================================================
HINSTANCE App::m_hInstance;                 // HINSTANCE of this process
IXRApplicationPtr App::m_pApplication;      // IXRApplication for this process
IXRVisualHostPtr App::m_pVisualHost;        // IXRVisualHost for this process

// ============================================================================
//  InitializeComponent
// 
//  Description: Load the Application resource dictionary if one exists.
// ============================================================================
HRESULT App::InitializeComponent()
{
    XRXamlSource appXaml(GetHInstance(), IDR_XAML_AUDIO_APP);
    HRESULT hr = m_pApplication->LoadResourceDictionary(&appXaml,NULL);
    return hr;
} // InitializeComponent

// ============================================================================
//  GetWindowParameters
// 
//  Description: Set the window creation parameters for this application.
//
//  Parameters:  pWindowParameters - Window creation parameters.
// ============================================================================
HRESULT App::GetWindowParameters(XRWindowCreateParams* pWindowParameters)
{
    static WCHAR szTitle[MAX_LOADSTRING];        // title bar text

    HRESULT hr = E_INVALIDARG;
    if (pWindowParameters)
    {
        pWindowParameters->Style       = WS_VISIBLE;
        pWindowParameters->ExStyle     = WS_EX_TOPMOST;

        // Set the title bar text
        LoadString(m_hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING); 
        pWindowParameters->pTitle      = szTitle;

        // Set window position
        pWindowParameters->Left        = 0;
        pWindowParameters->Top         = 0;

        // TODO: To specify a window size for the visual host set Width and Height
        // If Width and Height are zero the Width and Height specified in the
        // XAML are used

        //pWindowParameters->Width       = GetSystemMetrics(SM_CXSCREEN);
        //pWindowParameters->Height      = GetSystemMetrics(SM_CYSCREEN);

        hr = S_OK;
    }
    return hr;
} // GetWindowParameters

// ============================================================================
//  OnStartup
// 
//  Description: OnStartup is called after the visual host is created.
//               and before the message loop is entered.
// ============================================================================
HRESULT App::OnStartup()
{
    HRESULT hr = S_OK;

    IXRFrameworkElementPtr pRoot;

    hr = m_pVisualHost->GetRootElement(&pRoot);
    if (SUCCEEDED(hr))
    {
        // TODO: Add one time initialization code here.
    }

    return hr;
} // OnStartup

// ============================================================================
//  OnExit
// 
//  Description: OnExit is called after the message pump is exited
//               and before the visual host, and IXRApplication are destroyed.
// ============================================================================
HRESULT App::OnExit()
{
    // TODO: Add one-time cleanup code here.
    return S_OK;
} // OnExit

// ============================================================================
//  CreateHost
// 
//  Description: Create the visual host.
//
//  Parameters:  pCreateParams - The parameters used for creating the 
//               visual host's window
// ============================================================================
HRESULT App::CreateHost(XRWindowCreateParams* pCreateParams)
{
    XRPtr<IXRCustomUserControl>  pControl;
    HRESULT hr = E_FAIL;

    hr = m_pApplication->CreateObject(__uuidof(MainPage),&pControl);
    if (SUCCEEDED(hr))
    {
        hr = m_pApplication->CreateHostFromElementTree(pControl, pCreateParams, &m_pVisualHost);
    }

    return hr;
}

#pragma region RegisterUserControls Generated Code
// ============================================================================
//  RegisterUserControls
// 
//  Description: Register all XRCustomUserControl implemenations here.
//
//  WARNING: DO NOT EDIT THIS ALWAYS-GENERATED FUNCTION
// ============================================================================
HRESULT App::RegisterUserControls()
{
    HRESULT hr = S_OK;

    static PFN_XRCUC_REGISTER pfn[] = 
    {
        &MainPage::Register,
    };

    for (int i=0; i<_countof(pfn) && SUCCEEDED(hr); i++)
    {
        hr = pfn[i]();

        if (FAILED(hr))
        {
            RETAILMSG(1,(L"RegisterUserControls failed."));
        }

    }
    
    return hr;
} // RegisterUserControls

// ============================================================================
//  WARNING: DO NOT EDIT THIS ALWAYS-GENERATED FUNCTION
// ============================================================================
#pragma endregion RegisterUserControls Generated Code