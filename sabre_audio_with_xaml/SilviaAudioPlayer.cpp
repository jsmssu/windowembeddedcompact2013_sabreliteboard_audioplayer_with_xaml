#include "stdafx.h"
#include "SilviaAudioPlayer.h"


int SilviaAudioPlayer::isPlay = 0;
TCHAR* SilviaAudioPlayer::filename = L"\\SDMemory\\DONTMOVE.mp3";

SilviaAudioPlayer::SilviaAudioPlayer()
{
}

SilviaAudioPlayer::SilviaAudioPlayer(HWND hWnd)
{
    m_hWnd = hWnd;
}
SilviaAudioPlayer::~SilviaAudioPlayer()
{
}

void SilviaAudioPlayer::Play(void){
    if (isPlay == 0) {
        isPlay = 1;
        // COM 객체 생성 함수
        // 생성할 COM 객체의 CLSID
        // IID
        // Filter Graph 인터페이스 변수 	
        CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, IID_IGraphBuilder, (void **)&pGB);
        HRESULT hr = pGB->RenderFile(filename, NULL);
        if (FAILED(hr)){
            return;
        }
        //pBA->put_Volume(0);
        // 오디오 파일을 재생하기 위한 인터페이스 생성 
        pGB->QueryInterface(IID_IMediaEventEx, (void **)&pME);
        pGB->QueryInterface(IID_IMediaControl, (void **)&pMC);
        pGB->QueryInterface(IID_IMediaPosition, (void **)&pMP);
        pGB->QueryInterface(IID_IBasicAudio, (void **)&pBA);
        pGB->QueryInterface(IID_IMediaSeeking, (void **)&pMS);

        RETAILMSG(1, (TEXT("HSCROLL ID : %s \r\n"), filename));

        pGB->QueryInterface(IID_IVideoWindow, (void **)&pVW); // 비디오 윈도우 인터페이스 얻어 옴.
        // pFilter->QueryInterface(IID_IVideoWindow,(void **)&pVW);
        pGB->QueryInterface(IID_IBasicVideo, (void **)&pBV); // 기본 비도오 인터페이스 얻어 옴.

        put_volume_level(50);
        //pME->SetNotifyWindow((OAHWND)GetSafeHwnd(), WM_GRAPHNOTIFY, 0);// 메시지 싱크 핸들 저장.

        hr = pMC->Run();
    }


}
void SilviaAudioPlayer::Pause(void) {

    if (isPlay) {
        pMC->Pause();
    }
    else {
        pMC->Run();
    }
    isPlay = !isPlay;
}
void SilviaAudioPlayer::Stop(void) {
    isPlay = 0;
    pMC->Stop();
    pME->Release(); pME = NULL;
    pMC->Release(); pMC = NULL;
    pMP->Release(); pMP = NULL;
    pMS->Release(); pMS = NULL;
    pBA->Release(); pBA = NULL;
    pGB->Release(); pGB = NULL;
}


void SilviaAudioPlayer::fast_forward_ms(LONGLONG mSec) {
    LONGLONG current_t, during_t;
    pMS->GetCurrentPosition(&current_t); //1sec = 10000000
    pMS->GetDuration(&during_t);
    current_t = current_t + mSec * 10000;
    if (current_t > during_t) {
        current_t = during_t;
    }
    else if (current_t < 0) {
        current_t = 0;
    }
    pMS->SetPositions(&current_t, AM_SEEKING_AbsolutePositioning, NULL, AM_SEEKING_NoPositioning);
    RETAILMSG(TRUE, (TEXT("current_t = %I64d during_t = %I64d \r\n"), current_t, during_t));
}
void SilviaAudioPlayer::put_volume_level(int level) {
    if (level < 0){
        level = 0;
    }
    if (level > 100){
        level = 100;
    }
    int res_sound = -powf(10, ((float)(100 - level) / (float)25)); //0~10000, 10^4
    volume_level = level;
    RETAILMSG(TRUE, (TEXT("sound %d %d \r\n"), level, res_sound));
    pBA->put_Volume(res_sound);
}

int SilviaAudioPlayer::get_current_time_level() {
    REFTIME time_present;
    REFTIME time_duration;
    pMP->get_CurrentPosition(&time_present);
    pMP->get_Duration(&time_duration);
    return (((float)time_present / time_duration) * 100);
}

void SilviaAudioPlayer::put_current_time_level(int time_level) {
    REFTIME time_present;
    REFTIME time_duration;
    pMP->get_CurrentPosition(&time_present);
    pMP->get_Duration(&time_duration);

    REFTIME time_result = ((float)time_duration / 100) * time_level;
    pMP->put_CurrentPosition(time_result);
}