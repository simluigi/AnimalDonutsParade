/*==================================================================
DIRECTX11 三校合同 title.cpp
Author: Sim Luigi
Last Updated: 2020.08.26
===================================================================*/
#include "main.h"
#include "manager.h"
#include "scene.h"
#include "input.h"
#include "sound.h"
#include "light.h"
#include "UI_title.h"
#include "load_screen.h"
#include "game.h"
#include "title.h"

void CTitle::Init()
{
	// Scene終了フラグ
	m_ExitFlag = false;

	CLight::SetLightOff();
	CUITitle::Load();
	CSound::LoadTitleAudio();

	AddGameObject<CUITitle>(2);
	AddGameObject<CLoadScreen>(2)->FadeOut();
	CSound::PlayBGMTitle();
}

void CTitle::Uninit()
{
	CScene::Uninit();
}

void CTitle::Update()
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
		CManager::SetScene<CGame>();
	}
}

void CTitle::UnloadTitleResources()
{
	CUITitle::Unload();
}