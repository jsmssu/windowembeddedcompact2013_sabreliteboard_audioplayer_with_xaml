#pragma once

#include <XamlRuntime.h>
#include <XRInteractions.h>

//
// This function pointer type is used to declare a table of
// registration functions in App.cpp
//
typedef HRESULT (*PFN_XRCUC_REGISTER)();

// 
// This is the main application class.
//
class App
{
public:

    //
    // Intialize member variables that cannot fail initialization in the constructor.
    //
    App():
        m_bInitialized(FALSE),
        m_nResult(0)
    {
    }

    //
    // Destructor
    //
    ~App() {}

    // Intialize the XamlRuntime API, a VisualHost, and initialize the application
    HRESULT Initialize(HINSTANCE hInstance);

    // Create the VisualHost.
    HRESULT CreateHost(XRWindowCreateParams* pCreateParams);

    // Run the application until the message pump exits.
    HRESULT Run();

    // Register the UserControls implemented in this module
    HRESULT RegisterUserControls();

    // Get the host window creation parameters
    HRESULT GetWindowParameters(XRWindowCreateParams* pWindowParameters);

    // Get the result code to be returned from WinMain
    int GetWinMainResultCode();

    // Set the result code to be returned from WinMain
    void SetWinMainResultCode(int nResult);

    // Get the application HINSTANCE
    static HINSTANCE GetHInstance();

    // Exit the application
    HRESULT Exit();

    // OnStartup is called after the visual host is created
    // and before the message loop is entered
    HRESULT OnStartup();

    // OnExit is called after the message pump is exited
    // and before the visual host, and IXRApplication are destroyed.
    HRESULT OnExit();

    // Register the resource dictionary for this application
    HRESULT InitializeComponent();  

    // Gets the visual host for this application
    static HRESULT GetVisualHost(IXRVisualHost** ppHost);

    // Gets IXRApplication for this class
    static HRESULT GetApplication(IXRApplication ** ppApp);


    static void CreateListBoxItem(IXRListBox* pListBox, WCHAR* pObject) {
        RETAILMSG(1, (TEXT("test\n\r\n\r\n\r")));
        IXRItemCollectionPtr pCollection;
        HRESULT hr = pListBox->GetItems(&pCollection);
        RETAILMSG(1, (TEXT("test\n\r\n\r\n\r")));
        if (SUCCEEDED(hr))
        {
            for (int x = 0; x < 20; x++)
            {
                IXRListBoxItemPtr itemPtr;
                if (SUCCEEDED(pCollection->GetItem(x, &itemPtr)))
                {
                    XRValue value;
                    value.vType = VTYPE_READONLY_STRING;
                    value.bstrStringVal = _T("Test");
                    itemPtr->SetContent(&value);

                    RETAILMSG(1, (TEXT("test\n\r\n\r\n\r")));
                }
            }
        }

        /*
        IXRListBoxItemPtr pLocationBasedItem;
        IXRImageBrushPtr pImageBrush;


        float itemHeight = 50;
        float itemWidth = 100;
        XRValue itemValue;
        itemValue.vType = VTYPE_READONLY_STRING;
        itemValue.pReadOnlyStringVal = L"Ninth Avenue Diner";

        // Create new XR objects

        m_pApplication->CreateObject(&pLocationBasedItem);
        m_pApplication->CreateObject(&pImageBrush);

        pLocationBasedItem->SetHeight(itemHeight);
        pLocationBasedItem->SetWidth(itemWidth);
        pLocationBasedItem->SetContent(&itemValue);
        pLocationBasedItem->SetBackground((IXRBrush*)&pImageBrush);

        // Add the new list-box item to the item collection

        IXRItemCollectionPtr pItemCollection;
        UINT index = 0;
        XRValue xrValue;
        xrValue.vType = VTYPE_OBJECT;
        xrValue.pObjectVal = pLocationBasedItem;
        pItemCollection->Insert(index, &xrValue);
        pListBox->GetItems(&pItemCollection);*/

    }


private:
    // Sets the visual host for this application
    static void SetVisualHost(IXRVisualHost* pHost);

    // Sets IXRApplication for this class
    static void SetApplication(IXRVisualHost* pApp);

protected:
    // member variables
    BOOL                            m_bInitialized; // Initialization succeeded
    int                             m_nResult;      // WinMain result code

    // static member variables
    static HINSTANCE                m_hInstance;    // The HINSTANCE of this process
    static IXRApplicationPtr        m_pApplication; // IXRApplication for this process
    static IXRVisualHostPtr         m_pVisualHost;  // IXRVisualHost for this process
};


// ============================================================================
//  Initialize
// 
//  Description: Intialize the XamlRuntime API, and the XRApplication and then 
//               create a visual host.
//
//  Parameters:  hInstance - The HINSTANCE from WinMain
// ============================================================================
inline HRESULT App::Initialize(HINSTANCE hInstance)
{
    HRESULT hr = E_FAIL;

    XRWindowCreateParams    WindowParameters = {0};

    m_hInstance = hInstance;

    m_bInitialized = XamlRuntimeInitialize();

    if (m_bInitialized)
    {
        m_bInitialized = InteractionsInitialize();
    }

    // Create IXRApplication instance
    if (m_bInitialized)
    {
        hr = GetXRApplicationInstance(&m_pApplication);
    }

    if (SUCCEEDED(hr))
    {
        hr = m_pApplication->AddResourceModule(m_hInstance);    
    }

    if (SUCCEEDED(hr))
    {
        hr = RegisterUserControls();
    }

    if (SUCCEEDED(hr))
    {
        hr = InitializeComponent();
    }

    if (SUCCEEDED(hr))
    {
        hr = GetWindowParameters(&WindowParameters);
    }

    if (SUCCEEDED(hr))
    {
        hr = CreateHost(&WindowParameters);
    }

    if (SUCCEEDED(hr))
    {
        hr = OnStartup();
    }

    return hr;
} // Initialize

// ============================================================================
//  Run
// 
//  Description: Run the application until the message pump exits.
// ============================================================================
inline HRESULT App::Run()
{
    HRESULT hr = E_FAIL;
    UINT uiExitCode = 0;

    if (m_pVisualHost != NULL)
    {
        // save the exit code for WinMain
        hr = m_pVisualHost->StartDialog(&uiExitCode);
        SetWinMainResultCode(uiExitCode);  
    }

    // Allow user to cleanup resources.
    OnExit();

    //
    // XamlRuntime interfaces must be released in the 
    // following order: IXRVisualHost, IXRApplication.
    // After these interfaces are released the runtime
    // can be uninitialized.
    //

    // First release IXRVisualHost
    m_pVisualHost = NULL;

    // Second release IXRApplication
    m_pApplication = NULL;

    // If XamlRuntime was initialized, uninitialize it
    if (m_bInitialized)
    {
        m_bInitialized = FALSE;
        InteractionsUninitialize();
        XamlRuntimeUninitialize();
    }

    m_hInstance=NULL;

    return hr;
} // Run


// ============================================================================
//  GetWinMainResultCode
// 
//  Description: Get the result code to be returned from WinMain
// ============================================================================
inline int App::GetWinMainResultCode()
{ 
    return m_nResult; 
} // GetWinMainResultCode

// ============================================================================
//  SetWinMainResultCode
// 
//  Description: Set the result code to be returned from WinMain
//
//  Parameters:  nResult - The result code to be returned from WinMain
// ============================================================================
inline void App::SetWinMainResultCode(int nResult)
{ 
    m_nResult = nResult; 
} // SetWinMainResultCode

// ============================================================================
//  GetHInstance
// 
//  Description: Get the application HINSTANCE
// ============================================================================
inline HINSTANCE App::GetHInstance()
{ 
    return m_hInstance; 
} // GetHInstance

// ============================================================================
//  Exit
// 
//  Description: Exit the application
// ============================================================================
inline HRESULT App::Exit() 
{
    HRESULT hr = E_FAIL;

    if (NULL != m_pVisualHost)
    {
        hr = m_pVisualHost->EndDialog(0);
    }

    return hr; 
} // Exit

// ============================================================================
// GetVisualHost
//
// Gets the visual host for this application
// ============================================================================
inline HRESULT App::GetVisualHost(IXRVisualHost ** ppHost)
{
    if (!ppHost)
        return E_INVALIDARG;

    if (m_pVisualHost)
    {
        *ppHost = m_pVisualHost;
        (*ppHost)->AddRef();
        return S_OK;
    }

    return E_FAIL;
} 

// ============================================================================
// SetVisualHost
//
// Sets the visual host for this application
// ============================================================================
inline void App::SetVisualHost(IXRVisualHost* pHost)
{
    // Smart pointer automatically calls AddRef
    m_pVisualHost = pHost;
}

// ============================================================================
// GetApplication
//
// Gets IXRApplication for this class
// ============================================================================
inline HRESULT App::GetApplication(IXRApplication ** ppApp)
{
    HRESULT hr = E_FAIL;

    if (!ppApp)
      return E_INVALIDARG;

    if (m_pApplication)
    {
        *ppApp = m_pApplication;
        (*ppApp)->AddRef();
        hr = S_OK;
    }

    return hr;
}

// ============================================================================
// SetApplication
//
// Sets IXRApplication for this class
// ============================================================================
inline void App::SetApplication(IXRVisualHost* pApp)
{
    // Smart pointer automatically calls AddRef
    m_pApplication = pApp;
}
 