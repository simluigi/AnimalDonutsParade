/*==================================================================
DIRECTX11 �O�Z���� explosion.h
Author: Sim Luigi
Last Updated: 2020.08.26
===================================================================*/
#pragma once
#include "game_object.h"

class CExplosion : public CGameObject
{
private:


	static ID3D11Buffer*					m_VertexBuffer;
	static ID3D11ShaderResourceView*		m_Texture;

	int m_Count = 0;		//frame count

public:

	CExplosion() {}			//�R���X�g���N�^		Constructor
	~CExplosion() {}		//�f�X�g���N�^			Destructor

	//2017.07.13
	//Load/Unload texture (static: one texture for all instances)
	static void Load();
	static void Unload();

	void Init();
	void Uninit();
	void Update();
	void Draw();
};