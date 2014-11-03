#pragma once
#include <dshow.h>  //directshow ���� ��� ����
#include <math.h>
// directshow ���� ���̺귯�� ��ũ
#pragma comment(lib, "strmiids.lib")
#pragma comment(lib, "ole32.lib")

// COM ��ü�� Release 
#define SAFE_RELEASE(x) { if(x) x->Release(); x = NULL; }
#define RELEASE(x) { x->Release(); x = NULL; }

class SilviaAudioPlayer
{
public:
    IGraphBuilder *pGB; // Filter Graph �������̽� 
    IMediaControl *pMC; // Media Control �������̽� 
    IMediaEventEx *pME; // Media Event �������̽� 
    IBasicAudio   *pBA; // Basic Audio �������̽� 
    IMediaSeeking *pMS; // Media Seeking �������̽� 
    IMediaPosition *pMP; // Media Position �������̽� 

    HWND m_hWnd;

    int volume_level;
    static int isPlay;

    IVideoWindow  *pVW;
    IBasicVideo   *pBV;
    static TCHAR *filename;
    void Stop(void);
    void Pause(void);
    void Play(void);
    void fast_forward_ms(LONGLONG mSec); //��������
    void put_volume_level(int level); //�������� 0~100�ܰ�
    int get_current_time_level(); //100����� ����ð����� ���� ��ġ
    void put_current_time_level(int time_level); //���� ��ġ�� ����
    SilviaAudioPlayer(HWND);
    SilviaAudioPlayer();
    ~SilviaAudioPlayer();
};

