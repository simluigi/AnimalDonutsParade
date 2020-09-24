/*==================================================================
DIRECTX11 三校合同 field.h
Author: Sim Luigi
Last Updated: 2020.08.26
===================================================================*/

#pragma once
#include "game_object.h"

class CField : public CGameObject
{
private:

	ID3D11Buffer*							m_FieldVertexBuffer = NULL;
	static ID3D11ShaderResourceView*		m_FieldTexture;

	ID3D11Buffer*							m_WallVertexBuffer[4];
	static ID3D11ShaderResourceView*		m_WallTexture;

public:

	CField() {}			//コンストラクタ		Constructor
	~CField() {}		//デストラクタ			Destructor

	static void Load();
	static void Unload();

	void Init();
	void Uninit();
	void Update();
	void Draw();

};