/*==================================================================
DIRECTX11 三校合同 result.cpp
Author: Sim Luigi
Last Updated: 2020.08.28

2020.08.28
-.cpp, header file added
===================================================================*/
#include "main.h"
#include "manager.h"
#include "scene.h"
#include "input.h"
#include "sound.h"
#include "light.h"
#include "UI_result.h"
#include "load_screen.h"
#include "title.h"
#include "game.h"
#include "result.h"

void CResult::Init()
{
	// Scene終了フラグ
	m_ExitFlag = false;

	CLight::SetLightOff();
	CUIResult::Load();
	CSound::LoadResultAudio();

	if (CManager::GetFirstResult() == true)
	{
		CUIResult::Load();
		CManager::SetFirstResult(false);
	}

	AddGameObject<CUIResult>(2);
	AddGameObject<CLoadScreen>(2)->FadeOut();
	CSound::PlayBGMResult();
}

void CResult::Uninit()
{
	CScene::Uninit();
}

void CResult::Update()
{
	CScene::Update();

	// 画面遷移: GameStart
	// Screen Transition: Game Start
	if (CInput::GetKeyTrigger(VK_SPACE) && m_ExitFlag == false)
	{
		m_ExitFlag = true;
		CSound::PlaySfxEnterKey();
		GetGameObject<CLoadScreen>(2)->FadeIn();
	}

	// ローディング画面が完全に不透明になってから次のSceneに変更する
	// Process next scene after Loading Screen becomes fully transparent
	if (m_ExitFlag == true && GetGameObject<CLoadScreen>(2)->GetFadeCount() >= 1.5f)
	{
		CManager::SetScene<CTitle>();
	}
}

// 2020.08.29
// 後片付け：メモリー開放
// Free up memory after game exits
void CResult::UnloadResultResources(bool firstResult)
{
	// ロードされた場合のみ
	if (firstResult == false)
	{
		CUIResult::Unload();
	}
}
