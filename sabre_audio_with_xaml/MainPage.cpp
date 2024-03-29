#pragma once
#include "stdafx.h"
#include "sabre_audio_with_xamlGenerated.h"
#include "MainPage.h"
#include "App.h"
#include "resource.h"
#include "SilviaAudioPlayer.h" 
#include "OpenFileDialog.h" 
#include <thread>
#pragma comment(lib, "Shlwapi.lib") //파일검색
#include <Dmodshow.h> // DMO 관련 헤더 파일
#include <dmo.h>
#include <Shlwapi.h>
 

SilviaAudioPlayer m_player;
OpenFileDialog* openFileDialog1 = new OpenFileDialog(); 
// ============================================================================
//  OnLoaded
//
//  Description: Calls InitializeComponent to bind member variables to named
//               elements, and attach event handlers specified in XAML
//
//  Parameters:  pRoot - The root dependency object.
// ============================================================================
HRESULT MainPage::OnLoaded(__in IXRDependencyObject* pRoot)
{
    UNREFERENCED_PARAMETER(pRoot);

    HRESULT hr = InitializeComponent();
    CoInitialize(NULL);
    m_player = SilviaAudioPlayer();
    
    RETAILMSG(1, (TEXT("created player\n\r")));

    if (FAILED(hr))
    {
        goto Error;
    }
    // Add calls to FindName or Add___EventHandler() methods after this comment.
    if (m_pbutton_music_previous)
    {
        m_pbutton_music_previous->AddClickEventHandler(CreateDelegate(this, &MainPage::change_music_previous));
    }

    if (m_pbutton_music_next)
    {
        m_pbutton_music_next->AddClickEventHandler(CreateDelegate(this, &MainPage::change_music_next));
    }
    if (m_pbutton_playtime_previous)
    {
        m_pbutton_playtime_previous->AddClickEventHandler(CreateDelegate(this, &MainPage::change_playingtime_previous));
    }
    if (m_pbutton_pause)
    {
        m_pbutton_pause->AddClickEventHandler(CreateDelegate(this, &MainPage::pause_music));
    }
    if (m_pbutton_playtime_next)
    {
        m_pbutton_playtime_next->AddClickEventHandler(CreateDelegate(this, &MainPage::change_playingtime_next));
    }
    if (m_plist_music_name)
    {
        m_plist_music_name->AddLoadedEventHandler(CreateDelegate(this, &MainPage::show_list_music));
    }
    if (m_pbutton_stop)
    {
        m_pbutton_stop->AddClickEventHandler(CreateDelegate(this, &MainPage::stop_music));
    }
    if (m_pbutton_start)
    {
        m_pbutton_start->AddClickEventHandler(CreateDelegate(this, &MainPage::start_music));
    }
    if (m_pbutton_music_next_Copy)
    {
        m_pbutton_music_next_Copy->AddClickEventHandler(CreateDelegate(this, &MainPage::change_music_next));
    }
    if (m_pbutton_volume_up)
    {
        m_pbutton_volume_up->AddClickEventHandler(CreateDelegate(this, &MainPage::change_volume_up));
    }
    if (m_pbutton_volume_down)
    {
        m_pbutton_volume_down->AddClickEventHandler(CreateDelegate(this, &MainPage::change_volume_down));
    }
    if (m_pbutton_filedialog)
    {
        m_pbutton_filedialog->AddClickEventHandler(CreateDelegate(this, &MainPage::open_filedialog));
    }
    if (m_pbutton_exit)
    {
        m_pbutton_exit->AddClickEventHandler(CreateDelegate(this, &MainPage::exit_app));
    }


Error:
    return hr;
} // OnLoaded
 

// ============================================================================
//  change_music_previous
// 
//  Description: Event handler implementation
//
//  Parameters:  pSender - The dependency object that raised the click event.
//               pArgs - Event specific arguments.
// ============================================================================
HRESULT MainPage::change_music_previous (IXRDependencyObject* pSender, XRMouseButtonEventArgs* pArgs)
{
    HRESULT hr = E_NOTIMPL;

    if ((NULL == pSender) || (NULL == pArgs))
    {
        hr = E_INVALIDARG;
    }

    

    return hr;
}

// ============================================================================
//  change_playingtime_previous
// 
//  Description: Event handler implementation
//
//  Parameters:  pSender - The dependency object that raised the click event.
//               pArgs - Event specific arguments.
// ============================================================================
HRESULT MainPage::change_playingtime_previous (IXRDependencyObject* pSender, XRMouseButtonEventArgs* pArgs)
{
    HRESULT hr = E_NOTIMPL;

    if ((NULL == pSender) || (NULL == pArgs))
    {
        hr = E_INVALIDARG;
    }

    m_player.fast_forward_ms(-5000);

    return hr;
}

// ============================================================================
//  pause_music
// 
//  Description: Event handler implementation
//
//  Parameters:  pSender - The dependency object that raised the click event.
//               pArgs - Event specific arguments.
// ============================================================================
HRESULT MainPage::pause_music (IXRDependencyObject* pSender, XRMouseButtonEventArgs* pArgs)
{
    HRESULT hr = E_NOTIMPL;
    if ((NULL == pSender) || (NULL == pArgs))
    {
        hr = E_INVALIDARG;
    }
    m_player.Pause();
    return hr;
}

// ============================================================================
//  change_playingtime_next
// 
//  Description: Event handler implementation
//
//  Parameters:  pSender - The dependency object that raised the click event.
//               pArgs - Event specific arguments.
// ============================================================================
HRESULT MainPage::change_playingtime_next (IXRDependencyObject* pSender, XRMouseButtonEventArgs* pArgs)
{
    HRESULT hr = E_NOTIMPL;

    if ((NULL == pSender) || (NULL == pArgs))
    {
        hr = E_INVALIDARG;
    }

    m_player.fast_forward_ms(5000);


    return hr;
}

// ============================================================================
//  change_music_nex
// 
//  Description: Event handler implementation
//
//  Parameters:  pSender - The dependency object that raised the click event.
//               pArgs - Event specific arguments.
// ============================================================================
HRESULT MainPage::change_music_nex (IXRDependencyObject* pSender, XRMouseButtonEventArgs* pArgs)
{
    HRESULT hr = E_NOTIMPL;

    if ((NULL == pSender) || (NULL == pArgs))
    {
        hr = E_INVALIDARG;
    }
    return hr;
}




 
// ============================================================================
//  show_list_music
// 
//  Description: Event handler implementation
//
//  Parameters:  pSender - The dependency object that raised the click event.
//               pArgs - Event specific arguments.
// ============================================================================
HRESULT MainPage::show_list_music (IXRDependencyObject* pSender, XRRoutedEventArgs* pArgs)
{
    HRESULT hr = E_NOTIMPL;

    if ((NULL == pSender) || (NULL == pArgs))
    {
        hr = E_INVALIDARG;
    } 
     
     

    WIN32_FIND_DATA FileData; // Data structure describes the file found
    HANDLE hSearch; // Search handle returned by FindFirstFile
    const size_t cchDest = MAX_PATH;  // Set the buffer size for the file name
    TCHAR szMsg[cchDest]; // String to store the error message


    BOOL bFinished = FALSE;
    WCHAR tmp[260];
    // Start searching for .txt files in the root directory.
    hSearch = FindFirstFile(TEXT("\\SDMemory\\*.mp3"), &FileData);
    if (hSearch == INVALID_HANDLE_VALUE)
    {
        RETAILMSG(1, (TEXT("No .mp3 files found.\n\r")));
        return -1;
    }

    // Copy each .txt file to the new directory and change it to read-only, if it is not already read-only.
    int index = 0;
    while (!bFinished)
    {

        wcscpy(tmp, FileData.cFileName);
        RETAILMSG(1, (TEXT("file%s\n\r", tmp)));
       
  
        //App::CreateListBoxItem(m_plist_music_name,L"test");

        if (!FindNextFile(hSearch, &FileData))
        {
            bFinished = TRUE;
            if (GetLastError() == ERROR_NO_MORE_FILES)
            {
                RETAILMSG(1, (TEXT("Found all of the files.\n\r")));
            }
            else
            {
                RETAILMSG(1, (TEXT("Unable to find next file.\n\r")));
            }
        }
    }
    // Close the search handle.
    if (!FindClose(hSearch))
    {
        RETAILMSG(1, (TEXT("Unable to close search handle.\n\r")));
    }



    return hr;
}


// ============================================================================
//  stop_music
// 
//  Description: Event handler implementation
//
//  Parameters:  pSender - The dependency object that raised the click event.
//               pArgs - Event specific arguments.
// ============================================================================
HRESULT MainPage::stop_music (IXRDependencyObject* pSender, XRMouseButtonEventArgs* pArgs)
{
    HRESULT hr = E_NOTIMPL;
    if ((NULL == pSender) || (NULL == pArgs))
    {
        hr = E_INVALIDARG;
    }
    m_player.Stop();
    RETAILMSG(1, (TEXT("stop music.\n\r")));
    return hr;
}

// ============================================================================
//  start_music
// 
//  Description: Event handler implementation
//
//  Parameters:  pSender - The dependency object that raised the click event.
//               pArgs - Event specific arguments.
// ============================================================================
HRESULT MainPage::start_music (IXRDependencyObject* pSender, XRMouseButtonEventArgs* pArgs)
{
    HRESULT hr = E_NOTIMPL;
    
    if ((NULL == pSender) || (NULL == pArgs))
    {
        hr = E_INVALIDARG;
    }
    m_player.Play();
    RETAILMSG(1, (TEXT("play music.\n\r")));
    return hr;
}

// ============================================================================
//  change_music_next
// 
//  Description: Event handler implementation
//
//  Parameters:  pSender - The dependency object that raised the click event.
//               pArgs - Event specific arguments.
// ============================================================================
HRESULT MainPage::change_music_next (IXRDependencyObject* pSender, XRMouseButtonEventArgs* pArgs)
{
    HRESULT hr = E_NOTIMPL;

    if ((NULL == pSender) || (NULL == pArgs))
    {
        hr = E_INVALIDARG;
    }
    return hr;
}

// ============================================================================
//  change_volume_up
// 
//  Description: Event handler implementation
//
//  Parameters:  pSender - The dependency object that raised the click event.
//               pArgs - Event specific arguments.
// ============================================================================
HRESULT MainPage::change_volume_up (IXRDependencyObject* pSender, XRMouseButtonEventArgs* pArgs)
{
    HRESULT hr = E_NOTIMPL;

    if ((NULL == pSender) || (NULL == pArgs))
    {
        hr = E_INVALIDARG;
    }

    m_player.put_volume_level(m_player.volume_level + 5);
    RETAILMSG(1, (TEXT("volume up.\n\r")));

    return hr;
}

// ============================================================================
//  change_volume_down
// 
//  Description: Event handler implementation
//
//  Parameters:  pSender - The dependency object that raised the click event.
//               pArgs - Event specific arguments.
// ============================================================================
HRESULT MainPage::change_volume_down (IXRDependencyObject* pSender, XRMouseButtonEventArgs* pArgs)
{
    HRESULT hr = E_NOTIMPL;

    if ((NULL == pSender) || (NULL == pArgs))
    {
        hr = E_INVALIDARG;
    }

    m_player.put_volume_level(m_player.volume_level - 5);
    RETAILMSG(1, (TEXT("volume down.\n\r")));
    return hr;
}

// ============================================================================
//  open_filedialog
// 
//  Description: Event handler implementation
//
//  Parameters:  pSender - The dependency object that raised the click event.
//               pArgs - Event specific arguments.
// ============================================================================
HRESULT MainPage::open_filedialog (IXRDependencyObject* pSender, XRMouseButtonEventArgs* pArgs)
{
    HRESULT hr = E_NOTIMPL;

    if ((NULL == pSender) || (NULL == pArgs))
    {
        hr = E_INVALIDARG;
    }
    openFileDialog1->FilterIndex = 1;
    //openFileDialog1->Flags |= OFN_SHOWHELP;
    openFileDialog1->InitialDir = _T("\\SDMemory");
    openFileDialog1->Title = _T("Open Text File");
    if (openFileDialog1->ShowDialog()) {
        m_player.filename = openFileDialog1->FileName;
        //MessageBox(0, openFileDialog1->FileName, _T("openopen!"),MB_OK | MB_ICONINFORMATION);
    }

    return hr;
}

// ============================================================================
//  exit_app
// 
//  Description: Event handler implementation
//
//  Parameters:  pSender - The dependency object that raised the click event.
//               pArgs - Event specific arguments.
// ============================================================================
HRESULT MainPage::exit_app (IXRDependencyObject* pSender, XRMouseButtonEventArgs* pArgs)
{
    HRESULT hr = E_NOTIMPL;
    if ((NULL == pSender) || (NULL == pArgs))
    {
        hr = E_INVALIDARG;
    }
    return hr;
}


#pragma region GeneratedCode
// ============================================================================
//  WARNING: DO NOT EDIT THIS ALWAYS-GENERATED CODE
// ============================================================================
HRESULT MainPage::InitializeComponent()
{
    HRESULT hr = E_FAIL;

    FindName(L"LayoutRoot", &m_pLayoutRoot);
    FindName(L"progress_playingtime", &m_pprogress_playingtime);
    FindName(L"button_music_previous", &m_pbutton_music_previous);
    FindName(L"button_playtime_previous", &m_pbutton_playtime_previous);
    FindName(L"button_pause", &m_pbutton_pause);
    FindName(L"button_playtime_next", &m_pbutton_playtime_next);
    FindName(L"button_music_next", &m_pbutton_music_next);
    FindName(L"list_music_name", &m_plist_music_name);
    FindName(L"button_stop", &m_pbutton_stop);
    FindName(L"button_start", &m_pbutton_start);
    FindName(L"button_music_next_Copy", &m_pbutton_music_next_Copy);
    FindName(L"button_volume_up", &m_pbutton_volume_up);
    FindName(L"button_volume_down", &m_pbutton_volume_down);
    FindName(L"button_filedialog", &m_pbutton_filedialog);
    FindName(L"button_exit", &m_pbutton_exit);

    if (m_pLayoutRoot &&
        m_pprogress_playingtime &&
        m_pbutton_music_previous &&
        m_pbutton_playtime_previous &&
        m_pbutton_pause &&
        m_pbutton_playtime_next &&
        m_pbutton_music_next &&
        m_plist_music_name &&
        m_pbutton_stop &&
        m_pbutton_start &&
        m_pbutton_music_next_Copy &&
        m_pbutton_volume_up &&
        m_pbutton_volume_down &&
        m_pbutton_filedialog &&
        m_pbutton_exit
       )
    {
        hr = S_OK;
    }

    return hr;
}
// ============================================================================
//  WARNING: DO NOT EDIT THIS ALWAYS-GENERATED CODE
// ============================================================================
#pragma endregion GeneratedCode
