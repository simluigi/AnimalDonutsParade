/*==================================================================
DIRECTX11 �O�Z���� sound.h
Author: Sim Luigi
Last Updated: 2020.08.28
===================================================================*/
#pragma once
#include "audio_clip.h"

class CSound
{
	static class	CAudioClip*		m_BGMTitle;
	static class	CAudioClip*		m_BGMGame;
	static class	CAudioClip*		m_BGMResult;

	static class	CAudioClip*		m_SFXEnterKey;
	static class	CAudioClip*		m_SFXCountdown;
	static class	CAudioClip*		m_SFXGetDonut;
	static class	CAudioClip*		m_SFXCombo;
	static class	CAudioClip*		m_SFXMiss;
	static class	CAudioClip*		m_SFXTimeUp;

public:

	CSound() {}			//�R���X�g���N�^		Constructor
	~CSound() {}		//�f�X�g���N�^			Destructor

	// 2020.08.28
	// �I�[�f�B�I�֐�
	// Audio Functions

	// ���[�h���\�b�h
	// Load Methods
	static void LoadSystemSfx();
	static void LoadTitleAudio();
	static void LoadResultAudio();

	// BGM��SFX�ɕ����Ă���
	static void LoadGameBGM();
	static void LoadGameSFX();

	// �A�����[�h
	static void UnloadGameSFX();
	static void UnloadResultAudio();

	// BGM Title/Game : Loop (true)
	static void PlayBGMTitle()				{ m_BGMTitle->Play(true);	}
	static void PlayBGMGame()				{ m_BGMGame->Play(true);	}

	// BGM Result: Loop (false)
	static void PlayBGMResult()				{ m_BGMResult->Play();		}

	// SFX: Loop (false)
	static void PlaySfxEnterKey()			{ m_SFXEnterKey->Play();	}
	static void PlaySfxCountdown()			{ m_SFXCountdown->Play();	}
	static void PlaySfxGetDonut()			{ m_SFXGetDonut->Play();	}
	static void PlaySfxCombo()				{ m_SFXCombo->Play();		} 
	static void PlaySfxMiss()				{ m_SFXMiss->Play();		}
	static void PlaySfxTimeUp()				{ m_SFXTimeUp->Play();		}

	// Stop Looping BGM (Unload)
	static void StopTitleBGM()				{ m_BGMTitle->Unload();		}	
	static void StopGameBGM()				{ m_BGMGame->Unload();		}	

};