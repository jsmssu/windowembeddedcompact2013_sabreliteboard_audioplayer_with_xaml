#pragma once
#include <dshow.h>  //directshow 관련 헤더 파일
#include <math.h>
// directshow 관련 라이브러리 링크
#pragma comment(lib, "strmiids.lib")
#pragma comment(lib, "ole32.lib")

// COM 객체를 Release 
#define SAFE_RELEASE(x) { if(x) x->Release(); x = NULL; }
#define RELEASE(x) { x->Release(); x = NULL; }

class SilviaAudioPlayer
{
public:
    IGraphBuilder *pGB; // Filter Graph 인터페이스 
    IMediaControl *pMC; // Media Control 인터페이스 
    IMediaEventEx *pME; // Media Event 인터페이스 
    IBasicAudio   *pBA; // Basic Audio 인터페이스 
    IMediaSeeking *pMS; // Media Seeking 인터페이스 
    IMediaPosition *pMP; // Media Position 인터페이스 

    HWND m_hWnd;

    int volume_level;
    static int isPlay;

    IVideoWindow  *pVW;
    IBasicVideo   *pBV;
    static TCHAR *filename;
    void Stop(void);
    void Pause(void);
    void Play(void);
    void fast_forward_ms(LONGLONG mSec); //빨리감기
    void put_volume_level(int level); //볼륨조절 0~100단계
    int get_current_time_level(); //100등분한 재생시간중의 현재 위치
    void put_current_time_level(int time_level); //현재 위치를 넣음
    SilviaAudioPlayer(HWND);
    SilviaAudioPlayer();
    ~SilviaAudioPlayer();
};

