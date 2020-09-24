/*==================================================================
DIRECTX11 三校合同 UI_time.h
Author: Sim Luigi
Last Updated: 2020.08.24
===================================================================*/

#pragma once
#include "game_object.h"

class CUITime : public CGameObject
{

private:

	ID3D11Buffer*						m_TimeVertexBuffer;			// Time display buffer
	ID3D11Buffer*						m_CountdownVertexBuffer;		// Countdown display buffer
	// number UV Map
	static ID3D11ShaderResourceView*	m_NumberUVMap;			//250x250px per icon, 1250px width


public:

	CUITime() {}		//コンストラクタ		Constructor
	~CUITime() {}		//デストラクタ			Destructor

	static void Load();
	static void Unload();

	void Init();
	void Uninit();
	void Update();
	void Draw();

};