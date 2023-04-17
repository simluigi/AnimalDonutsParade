/*==================================================================
DIRECTX11 �O�Z���� title.cpp
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
	// Scene�I���t���O
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

	// ��ʑJ��: GameStart
	// Screen Transition: Game Start
	if (CInput::GetKeyTrigger(VK_SPACE) && m_ExitFlag == false)
	{
		m_ExitFlag = true;
		CSound::PlaySfxEnterKey();
		GetGameObject<CLoadScreen>(2)->FadeIn();
	}

	// ���[�f�B���O��ʂ����S�ɕs�����ɂȂ��Ă��玟��Scene�ɕύX����
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