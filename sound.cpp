/*==================================================================
DIRECTX11 三校合同 sound.cpp
Author: Sim Luigi
Last Updated: 2020.08.28

2020.08.28
-.cpp, header file created.
===================================================================*/
#include "sound.h"

class	CAudioClip*		CSound::m_BGMTitle;
class	CAudioClip*		CSound::m_BGMGame;
class	CAudioClip*		CSound::m_BGMResult;

class	CAudioClip*		CSound::m_SFXEnterKey;
class	CAudioClip*		CSound::m_SFXCountdown;
class	CAudioClip*		CSound::m_SFXGetDonut;
class	CAudioClip*		CSound::m_SFXCombo;
class	CAudioClip*		CSound::m_SFXMiss;
class	CAudioClip*		CSound::m_SFXTimeUp;

//========================================
// ロード関数
// Load Functions
void CSound::LoadSystemSfx()
{
	m_SFXEnterKey = new CAudioClip;
	m_SFXEnterKey->Load("Asset\\Audio\\SFX_EnterKey.wav");
	assert(m_SFXEnterKey);
}

void CSound::LoadTitleAudio()
{
	m_BGMTitle = new CAudioClip;
	m_BGMTitle->Load("Asset\\Audio\\BGM_Title.wav");
	assert(m_BGMTitle);
}

void CSound::LoadGameBGM()
{
	m_BGMGame = new CAudioClip;
	m_BGMGame->Load("Asset\\Audio\\BGM_Game.wav");
	assert(m_BGMGame);
}

void CSound::LoadGameSFX()
{
	m_SFXCountdown = new CAudioClip;
	m_SFXCountdown->Load("Asset\\Audio\\SFX_Countdown.wav");
	assert(m_SFXCountdown);

	m_SFXGetDonut = new CAudioClip;
	m_SFXGetDonut->Load("Asset\\Audio\\SFX_GetDonut.wav");
	assert(m_SFXGetDonut);

	m_SFXCombo = new CAudioClip;
	m_SFXCombo->Load("Asset\\Audio\\SFX_Combo.wav");
	assert(m_SFXCombo);

	m_SFXMiss = new CAudioClip;
	m_SFXMiss->Load("Asset\\Audio\\SFX_Miss.wav");
	assert(m_SFXMiss);

	m_SFXTimeUp = new CAudioClip;
	m_SFXTimeUp->Load("Asset\\Audio\\SFX_TimeUp.wav");
	assert(m_SFXTimeUp);
}

void CSound::LoadResultAudio()
{
	m_BGMResult = new CAudioClip;
	m_BGMResult->Load("Asset\\Audio\\BGM_Result.wav");
	assert(m_BGMResult);
}

//========================================
// アンロード関数
// Unload Functions
void CSound::UnloadGameSFX()
{
	m_SFXCountdown->Unload();
	m_SFXGetDonut->Unload();
	m_SFXCombo->Unload();
	m_SFXMiss->Unload();	
	m_SFXTimeUp->Unload();
}

void CSound::UnloadResultAudio()
{
	m_BGMResult->Unload();
}



