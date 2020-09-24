/*==================================================================
DIRECTX11 �O�Z���� player.cpp
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

//�@�ړ����x
#define PLAYER_SPEED	(0.05f)

//�p���@inheritance from CGameObject
class CPlayer : public CGameObject
{
private:
	
	//�O���錾
	static class CModel* m_PlayerModel;

public:

	CPlayer() {}		//constructor	�R���X�g���N�^
	~CPlayer() {}		//destructor		�f�X�g���N�^

	void GetDonut();

	static void Load();
	static void Unload();

	void Init();
	void Uninit();
	void Update();
	void Draw();
};