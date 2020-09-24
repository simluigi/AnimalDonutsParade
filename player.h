/*==================================================================
DIRECTX11 三校合同 player.cpp
Author: Sim Luigi
Last Updated: 2020.08.27

2020.08.26
-added player model (tongs)

2020.08.27
-removed bullet implementation
-implemented forward area donut pickup GetDonut()
===================================================================*/

#pragma once
#include "game_object.h"

//　移動速度
#define PLAYER_SPEED	(0.05f)

//継承　inheritance from CGameObject
class CPlayer : public CGameObject
{
private:
	
	//前方宣言
	static class CModel* m_PlayerModel;

public:

	CPlayer() {}		//constructor	コンストラクタ
	~CPlayer() {}		//destructor		デストラクタ

	void GetDonut();

	static void Load();
	static void Unload();

	void Init();
	void Uninit();
	void Update();
	void Draw();
};