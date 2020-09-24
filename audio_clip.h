#pragma once

#include <list>
#include "main.h"
#include <xaudio2.h>
#include "renderer.h"

const int SOUND_SOURCE_MAX = 20;


class CAudioClip
{

public:

	static void Init();
	static void Uninit();
	static void SetMasterVolume( float Volume );

	void Load(const char *FileName);
	void Unload();
	void Play(bool Loop=false);
		
private:
	static IXAudio2*				m_Xaudio;
	static IXAudio2MasteringVoice*	m_MasteringVoice;

	IXAudio2SourceVoice*	m_SourceVoice[SOUND_SOURCE_MAX];
	BYTE*					m_SoundData;

	int						m_Length;
	int						m_PlayLength;

};

