/*==================================================================
DIRECTX11 �O�Z���� result.cpp
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
	// Scene�I���t���O
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
		CManager::SetScene<CTitle>();
	}
}

// 2020.08.29
// ��Еt���F�������[�J��
// Free up memory after game exits
void CResult::UnloadResultResources(bool firstResult)
{
	// ���[�h���ꂽ�ꍇ�̂�
	if (firstResult == false)
	{
		CUIResult::Unload();
	}
}
