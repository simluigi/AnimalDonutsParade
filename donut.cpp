/*==================================================================
DIRECTX11 三校合同 donut.cpp
Author: Sim Luigi
Last Updated: 2020.08.28

This class handles donut assets.

2020.08.28
-fixed Unicorn donut tail in Blender, reimported to assets.
===================================================================*/

#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "scene.h"
#include "game.h"
#include "order.h"
#include "model.h"
#include "explosion.h"
#include "donut.h"

//2020.8.13
//Model Array
class CModel* CDonut::m_Model[DONUT_TYPE_COUNT];

void CDonut::Init(int donutType)
{
	m_DonutType = donutType;

	m_Position	= D3DXVECTOR3(0.0f, 1.0f, 5.0f);
	m_Rotation	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale		= D3DXVECTOR3(1.0f, 1.0f, 1.0f);
}

void CDonut::Uninit()
{

}

void CDonut::Update()
{
	int diffScaling = CGame::GetDifficultyScaling();
	
	//衝突判定 Collision Detection
	CScene* scene = CManager::GetScene();

	// 2020.08.23
	// GetGameStartFlag
	if (CGame::GetGameStartFlag())
	{
		// UI: slowly approach
		m_Position.z -= (0.02f + diffScaling * 0.02f);
	}

	// 場外
	// Out of Bounds
	if ( m_Position.z < -19.0f)
	{
		scene->AddGameObject<CExplosion>(1)->SetPosition(m_Position);
		scene->AddGameObjectWithID<CDonut>(1, rand() % COrder::GetOrderLength())
			->SetPosition(D3DXVECTOR3(m_Position.x, m_Position.y, 10.0f));
		SetDestroy();
	}
}

void CDonut::Draw()
{
	//Matrix Settings
	//マトリックス設定
	D3DXMATRIX	world, scale, rotate, translate;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rotate, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&translate, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rotate * translate;
	CRenderer::SetWorldMatrix(&world);

	//Call Draw function
	//m_Model->Draw();

	m_Model[m_DonutType]->Draw();

}

// 2020.08.13
// モデルデータを配列に格納する
// Store Model Data in array 
void CDonut::Load()
{
	for (int i = 0; i < DONUT_TYPE_COUNT; i++)
	{
		m_Model[i] = new CModel();
	}

	// 各ドーナツ種類のテクスチャー
	// All donut textures
	m_Model[0]->Load("Asset\\Model\\Donut_NekoGreyOrange.obj");
	m_Model[1]->Load("Asset\\Model\\Donut_Kuroneko.obj");
	m_Model[2]->Load("Asset\\Model\\Donut_Poseyduck.obj");
	m_Model[3]->Load("Asset\\Model\\Donut_Butachan.obj");
	m_Model[4]->Load("Asset\\Model\\Donut_Unicorn.obj");
}

void CDonut::Unload()
{
	for (int i = 0; i < DONUT_TYPE_COUNT; i++)
	{
		m_Model[i]->Unload();
		delete m_Model[i];
	}
}