#pragma once

// <UserControl x:Class="xaml_audio.MainPage">
class __declspec(uuid("{c5d8e366-7b5e-4991-9b70-cb6b1cf5f847}")) MainPage
    : public XRCustomUserControlImpl<MainPage>
{
public:
    static HRESULT GetXamlSource(__in XRXamlSource* pXamlSource)
    {
        HRESULT hr = E_INVALIDARG;

        if (pXamlSource)
        {
            pXamlSource->SetResource (App::GetHInstance(), IDR_XAML_AUDIO_MAINPAGE);
            hr = S_OK;
        }
        
        return hr;
    }

    static HRESULT Register()
    {
        return XRCustomUserControlImpl<MainPage>::Register (__uuidof(MainPage), L"MainPage", L"clr-namespace:xaml_audio");
    }

    HRESULT change_music_previous (IXRDependencyObject* pSender, XRMouseButtonEventArgs* pArgs);
    HRESULT change_music_next (IXRDependencyObject* pSender, XRMouseButtonEventArgs* pArgs);
    HRESULT change_playingtime_previous (IXRDependencyObject* pSender, XRMouseButtonEventArgs* pArgs);
    HRESULT pause_music (IXRDependencyObject* pSender, XRMouseButtonEventArgs* pArgs);
    HRESULT change_playingtime_next (IXRDependencyObject* pSender, XRMouseButtonEventArgs* pArgs);
    HRESULT change_music_nex (IXRDependencyObject* pSender, XRMouseButtonEventArgs* pArgs);
    HRESULT show_list_music (IXRDependencyObject* pSender, XRRoutedEventArgs* pArgs);
    HRESULT stop_music (IXRDependencyObject* pSender, XRMouseButtonEventArgs* pArgs);
    HRESULT start_music (IXRDependencyObject* pSender, XRMouseButtonEventArgs* pArgs);
    HRESULT change_volume_up (IXRDependencyObject* pSender, XRMouseButtonEventArgs* pArgs);
    HRESULT change_volume_down (IXRDependencyObject* pSender, XRMouseButtonEventArgs* pArgs);
    HRESULT open_filedialog (IXRDependencyObject* pSender, XRMouseButtonEventArgs* pArgs);
    HRESULT exit_app (IXRDependencyObject* pSender, XRMouseButtonEventArgs* pArgs);

#pragma region GeneratedCode
    // ============================================================================
    //  WARNING: DO NOT EDIT THIS ALWAYS-GENERATED CODE
    // ============================================================================
public:
    HRESULT OnLoaded(__in IXRDependencyObject* pRoot);
    HRESULT InitializeComponent();

    IXRGridPtr                 m_pLayoutRoot;                 // <Grid x:Name="LayoutRoot">
    IXRProgressBarPtr          m_pprogress_playingtime;       // <ProgressBar x:Name="progress_playingtime">
    IXRButtonPtr               m_pbutton_music_previous;      // <Button x:Name="button_music_previous">
    IXRButtonPtr               m_pbutton_playtime_previous;   // <Button x:Name="button_playtime_previous">
    IXRButtonPtr               m_pbutton_pause;               // <Button x:Name="button_pause">
    IXRButtonPtr               m_pbutton_playtime_next;       // <Button x:Name="button_playtime_next">
    IXRButtonPtr               m_pbutton_music_next;          // <Button x:Name="button_music_next">
    IXRListBoxPtr              m_plist_music_name;            // <ListBox x:Name="list_music_name">
    IXRButtonPtr               m_pbutton_stop;                // <Button x:Name="button_stop">
    IXRButtonPtr               m_pbutton_start;               // <Button x:Name="button_start">
    IXRButtonPtr               m_pbutton_music_next_Copy;     // <Button x:Name="button_music_next_Copy">
    IXRButtonPtr               m_pbutton_volume_up;           // <Button x:Name="button_volume_up">
    IXRButtonPtr               m_pbutton_volume_down;         // <Button x:Name="button_volume_down">
    IXRButtonPtr               m_pbutton_filedialog;          // <Button x:Name="button_filedialog">
    IXRButtonPtr               m_pbutton_exit;                // <Button x:Name="button_exit">
    // ============================================================================
    //  WARNING: DO NOT EDIT THIS ALWAYS-GENERATED CODE
    // ============================================================================
#pragma endregion GeneratedCode

    QI_IDENTITY_MAPPING(MainPage, XRCustomUserControlImpl)
};