/*==================================================================
DIRECTX11 éOçZçáìØ UI_result.h
Author: Sim Luigi
Last Updated: 2020.09.01
===================================================================*/
#pragma once
#include "game_object.h"

class CUIResult : public CGameObject
{
	ID3D11Buffer*								m_ResultFrameVertexBuffer = NULL;
	ID3D11Buffer*								m_ScoreVertexBuffer = NULL;
	ID3D11Buffer*								m_HighScoreVertexBuffer = NULL;
	ID3D11Buffer*								m_SpaceVertexBuffer = NULL;



	static ID3D11ShaderResourceView*			m_ResultFrameTexture;
	static ID3D11ShaderResourceView*			m_ScoreTexture;
	static ID3D11ShaderResourceView*			m_HighScoreTexture;
	static ID3D11ShaderResourceView*			m_SpaceTexture;

	float	m_AnimCount;			// staged display
	bool	m_HighScoreUpdate;		// if high score will be updated


public:

	CUIResult() {}
	~CUIResult() {}

	static void Load();
	static void Unload();

	void Init();
	void Uninit();
	void Update();
	void Draw();
};