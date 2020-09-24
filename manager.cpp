/*==================================================================
DIRECTX11 三校合同 manager.cpp
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

// stdのlist構造の使用の際に必要
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

// .hファイルの静的変数をもう一回宣言
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

	// ゲーム起動のスタート画面
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
// メモリー開放
void CManager::UnloadAllResources()
{
	// 共通リソースをアンロード
	// Unload universal resources
	CLoadScreen::Unload();

	// タイトルリソースをアンロード（必ずロードされたのでチェック不要）
	// Unload Title Resources (automatically loaded at the start so no check required)
	CTitle::UnloadTitleResources();

	// ゲームリソースをアンロード（ロードされた場合のみ）
	// unload game assets (only if loaded)
	CGame::UnloadGameResources(m_FirstPlay);

	// リザルトリソースをアンロード（ロードされた場合のみ）
	// unload result assets (only if loaded)
	CResult::UnloadResultResources(m_FirstResult);
}