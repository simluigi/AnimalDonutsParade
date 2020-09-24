/*==================================================================
DIRECTX11 �O�Z���� manager.cpp
Author: Sim Luigi
Last Updated: 2020.08.27

2020.08.27
-removed bullet implementation

2020.08.28
-audio_clip.h, sound.cpp: Audio implemented.

2020.08.29
-header file : m_FirstPlay, m_FirstResult added 
 (indicate first load for tutorial and texture loading optimization)
 -CLEANUP: UnloadAllResources() added.
===================================================================*/

// std��list�\���̎g�p�̍ۂɕK�v
// required for std :: list (list structure programming)
#include <list>		
#include <assert.h>
#include "main.h"
#include "manager.h"
#include "scene.h"
#include "renderer.h"
#include "game_object.h"
#include "audio_clip.h"
#include "sound.h"
#include "input.h"
#include "light.h"
#include "field.h"
#include "camera.h"
#include "model.h"
#include "player.h"
#include "donut.h"
#include "explosion.h"
#include "score.h"

// 2020.07.24: New scene files added
#include "title.h"
#include "game.h"
#include "result.h"

// 2020.08.25 Loading Screen
#include "load_screen.h"

// .h�t�@�C���̐ÓI�ϐ����������錾
// Must redeclare static class variables in header file
CScene* CManager::m_Scene = NULL;
bool	CManager::m_FirstPlay;
bool	CManager::m_FirstResult;

void CManager::Init()
{
	CRenderer::Init();
	CInput::Init();
	CAudioClip::Init();

	CScore::Init();
	CSound::LoadSystemSfx();
	CLoadScreen::Load();

	// �Q�[���N���̃X�^�[�g���
	// First Scene on executing program
	SetScene<CTitle>();
	m_FirstPlay = true;
	m_FirstResult = true;
}

void CManager::Uninit()
{
	m_Scene->Uninit();
	delete m_Scene;
	CRenderer::Uninit();
	CInput::Uninit();
}

void CManager::Update()
{
	CInput::Update();
	m_Scene->Update();
}

void CManager::Draw()
{
	CRenderer::Begin();
	m_Scene->Draw();
	CRenderer::End();
}

// 2020.08.29
// �������[�J��
void CManager::UnloadAllResources()
{
	// ���ʃ��\�[�X���A�����[�h
	// Unload universal resources
	CLoadScreen::Unload();

	// �^�C�g�����\�[�X���A�����[�h�i�K�����[�h���ꂽ�̂Ń`�F�b�N�s�v�j
	// Unload Title Resources (automatically loaded at the start so no check required)
	CTitle::UnloadTitleResources();

	// �Q�[�����\�[�X���A�����[�h�i���[�h���ꂽ�ꍇ�̂݁j
	// unload game assets (only if loaded)
	CGame::UnloadGameResources(m_FirstPlay);

	// ���U���g���\�[�X���A�����[�h�i���[�h���ꂽ�ꍇ�̂݁j
	// unload result assets (only if loaded)
	CResult::UnloadResultResources(m_FirstResult);
}