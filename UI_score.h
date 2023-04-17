/*==================================================================
DIRECTX11 三校合同 UI_score.h
Author: Sim Luigi
Last Updated: 2020.08.24
===================================================================*/

#pragma once
#include "game_object.h"

class CUIScore : public CGameObject
{

private:

	ID3D11Buffer*						m_ScoreVertexBuffer;	//non-static; each instance has its own buffer

	// number UV Map
	static ID3D11ShaderResourceView*	m_NumberUVMap;			//250x250px per icon, 1250px width
	
public:

	CUIScore() {}		//コンストラクタ		Constructor
	~CUIScore() {}		//デストラクタ			Destructor

	static void Load();
	static void Unload();

	void Init();
	void Uninit();
	void Update();
	void Draw();

};