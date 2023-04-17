/*==================================================================
DIRECTX11 �O�Z���� game.cpp
Author: Sim Luigi
Last Updated: 2020.08.17

2020.08.17:
-game.cpp : Game Object <COrder> added

2020.08.23
-time elements <CUITime>, m_Timer added

2020.08.24
-score elements <CUIScore> added
-game start countdown/ game end implemented (via m_Time)

2020.08.27
-removed bullet implementation
-replaced with player front collision]

2020.08.30
-all game sounds implemented
-transition delay + process added (option: add Enter Key to proceed)
===================================================================*/

#include <ctime>
#include "main.h"
#include "manager.h"
#include "scene.h"
#include "sound.h"
#include "input.h"
#include "title.h"
#include "result.h"
#include "load_screen.h"
#include "model.h"
#include "player.h"
#include "donut.h"
#include "explosion.h"
#include "camera.h"
#include "field.h"
#include "light.h"
#include "order.h"
#include "score.h"
#include "UI_frame.h"
#include "UI_order.h"
#include "UI_time.h"
#include "UI_score.h"
#include "game.h"

#define TIME_DECREMENT	(0.015f)		// ���Ԍo�ߗ�
#define TIME_START		(99.9f)			// ���Ԑ��� Game Timer
#define TIME_COUNTDOWN  (3.0f)			// �Q�[���O�̃J�E���g�_�E��	

bool	CGame::m_GameStartFlag;
float	CGame::m_Time;
float   CGame::m_Countdown;
float	CGame::m_TransitionOffset;
int		CGame::m_DifficultyScaling;

void CGame::Init()
{
	m_ExitFlag = false;						// �Q�[���I���i���U���g�Ɉړ��t���b�O�j

	m_Time				= TIME_START;		// �^�C�}�[������ (UI_time.h)	
	m_DifficultyScaling = 0;				// ��Փx�㏸�J�E���^�[
	m_Countdown			= TIME_COUNTDOWN;	// GameStart�̑O�̃J�E���g�_�E��
	m_TransitionOffset	= 1.0f;				// ���Ԑ؂ꂩ���ʑJ�ڏ����̎���(delay)
	m_GameStartFlag		= false;			// GameStart�t���b�O���u�U�v	

	// ���C�g�ݒ���I���ɂ���
	// Turn on lignting for scene
	CLight::SetLightOn();

	// 2020.08.27
	COrder::Init();
	CScore::Init();
	CSound::LoadGameBGM();

	// 2020.08.29
	// �ŏ��̃v���C�̂�
	// GetFirstPlay() conditional
	if (CManager::GetFirstPlay() == true)

	{	// �e�N�X�`���[��SFX�����[�h����(�h�[�i�c�E�v���C���[�ȊO�j
		// Load textures to be used in scene (except donuts and player)
		CSound::LoadGameSFX();
		CField::Load();
		CExplosion::Load();
		CUIFrame::Load();
		CUIOrder::Load();
		CUITime::Load();
		CUIScore::Load();
	}

	AddGameObject<CCamera>(0);
	AddGameObject<CField>(1);

	// 2020.08.25
	// FadeIn succcessfully implemented.
	AddGameObject<CLoadScreen>(2)->FadeOut();
	AddGameObject<CUIFrame>(2);
	AddGameObject<CUIScore>(2);
	AddGameObject<CUITime>(2);

	

	// 2020.08.28
	// �d���A�Z�b�g���Ō�Ƀ��[�h���āA�t�F�C�h��ʂ̃^�C�~���O�ɍ��킹��
	// Load heavy assets last to match with Fade timing

	// 2020.08.29
	// �ŏ��̃v���C�̂�
	// GetFirstPlay() conditional
	if (CManager::GetFirstPlay() == true)
	{
		CPlayer::Load();
		CDonut::Load();
		CManager::SetFirstPlay(false);
	}
	
	// �v���C���[�I�u�W�F�N�g
	// Player Object
	AddGameObject<CPlayer>(1);

	// �Ō�̃h�[�i�c���C���A�b�v�F�����i��Փx����܂Łj
	// rand() % DIFFICULTY_START; starting difficulty
	AddGameObjectWithID<CDonut>(1, rand() % DIFFICULTY_START)->SetPosition(D3DXVECTOR3(-3.0f, 1.0f, 5.0f));
	AddGameObjectWithID<CDonut>(1, rand() % DIFFICULTY_START)->SetPosition(D3DXVECTOR3(0.0f, 1.0f, 5.0f));
	AddGameObjectWithID<CDonut>(1, rand() % DIFFICULTY_START)->SetPosition(D3DXVECTOR3(3.0f, 1.0f, 5.0f));
	AddGameObjectWithID<CDonut>(1, rand() % DIFFICULTY_START)->SetPosition(D3DXVECTOR3(-3.0f, 1.0f, 8.0f));
	AddGameObjectWithID<CDonut>(1, rand() % DIFFICULTY_START)->SetPosition(D3DXVECTOR3(0.0f, 1.0f, 8.0f));
	AddGameObjectWithID<CDonut>(1, rand() % DIFFICULTY_START)->SetPosition(D3DXVECTOR3(3.0f, 1.0f, 8.0f));

	// 2020.08.28
	// �Q�[����ʂ����[�h���Ă���TitleBGM�̍Đ����~�߂� �i���[�h��ʂōĐ��𑱂��邽�߁j
	// StopTitleBGM after assets load (let TitleBGM play while loading screen is up)
	// (will result in error if called before LoadTitleBGM() is called in Title.cpp
	CSound::StopTitleBGM();

	// 2020.08.30
	// �J�E���g�_�E��SFX�Đ�
	// Play Countdown SFX
	CSound::PlaySfxCountdown();
}

void CGame::Uninit()
{
	CScene::Uninit();
}

void CGame::Update()
{
	CScene::Update();

	// �Q�[���X�^�[�g�J�E���g�_�E��
	// Game Start Countdown
	if (m_GameStartFlag == false && m_Countdown > 0.0f)
	{
		if (COrder::CheckCustomerQueueIfEmpty())
		{
			COrder::InitCustomerQueue();	// first CustomerQueue
		}

		m_Countdown -= TIME_DECREMENT;
		if (m_Countdown < 0.0f)
		{
			//destroy old loading screen
			GetGameObject<CLoadScreen>(2)->SetDestroy();

			m_GameStartFlag = true;			// start game
			m_Countdown = 0.0f;				// fix value to 0.0f (stop processing)
			CSound::PlayBGMGame();
		}
	}

	// �Q�[�����Ԓ�
	// while clock is ticking (in-game)
	if (m_GameStartFlag == true && m_Time > 0.0f)
	{
		m_Time -= TIME_DECREMENT;
	}
	
	// ��ʑJ�� delay
	// Screen Transition delay
	if (m_ExitFlag == true && m_TransitionOffset > 0.0f)
	{
		m_TransitionOffset -= TIME_DECREMENT;
		if (m_TransitionOffset <= 0.0f)
		{
			AddGameObject<CLoadScreen>(2)->FadeIn();
		}
	}

	// ���Ԑ؂� (�I���t���b�O���I���ɐݒ�j
	// Time's Up!
	if (m_Time < 0.0f)
	{
		m_Time = 0.0f;
		m_GameStartFlag = false;
		m_ExitFlag = true;
		COrder::EmptyCustomerQueue();
		CSound::StopGameBGM();
		CSound::PlaySfxTimeUp();
	}

	//// ��ʑJ��
	//// Screen Transition Test
	//if (CInput::GetKeyTrigger('M'))
	//{
	//	m_GameStartFlag = false;
	//	COrder::EmptyCustomerQueue();
	//	CSound::StopGameBGM();
	//	CSound::PlaySfxEnterKey();
	//	AddGameObject<CLoadScreen>(2)->FadeIn();
	//}

	// �S�Ă̏����𖞂����Ă����ʑJ�ڂ���������
	// Exit Flag is true, Fade Screen is fully loaded, Time Delay complete�@-> process next scene
	if (m_ExitFlag == true && GetGameObject<CLoadScreen>(2)->GetFadeCount() >= 1.5f)
	{
		CManager::SetScene<CResult>();
	}
}

// 2020.08.29
// ��Еt���F�������[�J��
// Free up memory after game exits
void CGame::UnloadGameResources(bool firstPlay)
{
	// ���[�h���ꂽ�ꍇ�̂�
	if (firstPlay == false)
	{
		CPlayer::Unload();
		CDonut::Unload();
		CField::Unload();
		CExplosion::Unload();
		CUIFrame::Unload();
		CUIOrder::Unload();
		CUITime::Unload();
		CUIScore::Unload();
		CSound::UnloadGameSFX();
	}
}

