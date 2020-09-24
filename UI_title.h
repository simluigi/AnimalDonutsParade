/*==================================================================
DIRECTX11 éOçZçáìØ UI_result.h
Author: Sim Luigi
Last Updated: 2020.09.01

2020.09.01
-replaced enter with space key
===================================================================*/
#pragma once
#include "game_object.h"

class CUITitle : public CGameObject
{

	bool  m_FadeFlag;
	float m_FadeCount;
	float m_AnimCount;

	ID3D11Buffer*								m_TitleVertexBuffer = NULL;
	ID3D11Buffer*								m_SpaceVertexBuffer = NULL;
	ID3D11Buffer*								m_HighScoreTextVertexBuffer = NULL;
	ID3D11Buffer*								m_ScoreVertexBuffer = NULL;


	static ID3D11ShaderResourceView*			m_TitleTexture;
	static ID3D11ShaderResourceView*			m_SpaceTexture;
	static ID3D11ShaderResourceView*			m_HighScoreTextTexture;
	static ID3D11ShaderResourceView*			m_ScoreTexture;


public:

	CUITitle() {}			
	~CUITitle() {}			

	static void Load();
	static void Unload();

	void Init();
	void Uninit();
	void Update();
	void Draw();
};