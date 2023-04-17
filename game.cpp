/*==================================================================
DIRECTX11 三校合同 game.cpp
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

#define TIME_DECREMENT	(0.015f)		// 時間経過率
#define TIME_START		(99.9f)			// 時間制限 Game Timer
#define TIME_COUNTDOWN  (3.0f)			// ゲーム前のカウントダウン	

bool	CGame::m_GameStartFlag;
float	CGame::m_Time;
float   CGame::m_Countdown;
float	CGame::m_TransitionOffset;
int		CGame::m_DifficultyScaling;

void CGame::Init()
{
	m_ExitFlag = false;						// ゲーム終了（リザルトに移動フラッグ）

	m_Time				= TIME_START;		// タイマー初期化 (UI_time.h)	
	m_DifficultyScaling = 0;				// 難易度上昇カウンター
	m_Countdown			= TIME_COUNTDOWN;	// GameStartの前のカウントダウン
	m_TransitionOffset	= 1.0f;				// 時間切れから画面遷移処理の時間(delay)
	m_GameStartFlag		= false;			// GameStartフラッグを「偽」	

	// ライト設定をオンにする
	// Turn on lignting for scene
	CLight::SetLightOn();

	// 2020.08.27
	COrder::Init();
	CScore::Init();
	CSound::LoadGameBGM();

	// 2020.08.29
	// 最初のプレイのみ
	// GetFirstPlay() conditional
	if (CManager::GetFirstPlay() == true)

	{	// テクスチャーとSFXをロードする(ドーナツ・プレイヤー以外）
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
	// 重いアセットを最後にロードして、フェイド画面のタイミングに合わせる
	// Load heavy assets last to match with Fade timing

	// 2020.08.29
	// 最初のプレイのみ
	// GetFirstPlay() conditional
	if (CManager::GetFirstPlay() == true)
	{
		CPlayer::Load();
		CDonut::Load();
		CManager::SetFirstPlay(false);
	}
	
	// プレイヤーオブジェクト
	// Player Object
	AddGameObject<CPlayer>(1);

	// 最後のドーナツラインアップ：乱数（難易度上限まで）
	// rand() % DIFFICULTY_START; starting difficulty
	AddGameObjectWithID<CDonut>(1, rand() % DIFFICULTY_START)->SetPosition(D3DXVECTOR3(-3.0f, 1.0f, 5.0f));
	AddGameObjectWithID<CDonut>(1, rand() % DIFFICULTY_START)->SetPosition(D3DXVECTOR3(0.0f, 1.0f, 5.0f));
	AddGameObjectWithID<CDonut>(1, rand() % DIFFICULTY_START)->SetPosition(D3DXVECTOR3(3.0f, 1.0f, 5.0f));
	AddGameObjectWithID<CDonut>(1, rand() % DIFFICULTY_START)->SetPosition(D3DXVECTOR3(-3.0f, 1.0f, 8.0f));
	AddGameObjectWithID<CDonut>(1, rand() % DIFFICULTY_START)->SetPosition(D3DXVECTOR3(0.0f, 1.0f, 8.0f));
	AddGameObjectWithID<CDonut>(1, rand() % DIFFICULTY_START)->SetPosition(D3DXVECTOR3(3.0f, 1.0f, 8.0f));

	// 2020.08.28
	// ゲーム画面をロードしてからTitleBGMの再生を止める （ロード画面で再生を続けるため）
	// StopTitleBGM after assets load (let TitleBGM play while loading screen is up)
	// (will result in error if called before LoadTitleBGM() is called in Title.cpp
	CSound::StopTitleBGM();

	// 2020.08.30
	// カウントダウンSFX再生
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

	// ゲームスタートカウントダウン
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

	// ゲーム時間中
	// while clock is ticking (in-game)
	if (m_GameStartFlag == true && m_Time > 0.0f)
	{
		m_Time -= TIME_DECREMENT;
	}
	
	// 画面遷移 delay
	// Screen Transition delay
	if (m_ExitFlag == true && m_TransitionOffset > 0.0f)
	{
		m_TransitionOffset -= TIME_DECREMENT;
		if (m_TransitionOffset <= 0.0f)
		{
			AddGameObject<CLoadScreen>(2)->FadeIn();
		}
	}

	// 時間切れ (終了フラッグをオンに設定）
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

	//// 画面遷移
	//// Screen Transition Test
	//if (CInput::GetKeyTrigger('M'))
	//{
	//	m_GameStartFlag = false;
	//	COrder::EmptyCustomerQueue();
	//	CSound::StopGameBGM();
	//	CSound::PlaySfxEnterKey();
	//	AddGameObject<CLoadScreen>(2)->FadeIn();
	//}

	// 全ての条件を満たしてから画面遷移を処理する
	// Exit Flag is true, Fade Screen is fully loaded, Time Delay complete　-> process next scene
	if (m_ExitFlag == true && GetGameObject<CLoadScreen>(2)->GetFadeCount() >= 1.5f)
	{
		CManager::SetScene<CResult>();
	}
}

// 2020.08.29
// 後片付け：メモリー開放
// Free up memory after game exits
void CGame::UnloadGameResources(bool firstPlay)
{
	// ロードされた場合のみ
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

