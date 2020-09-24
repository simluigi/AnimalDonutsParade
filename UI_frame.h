/*==================================================================
DIRECTX11 éOçZçáìØ UI_frame.h
Author: Sim Luigi
Last Updated: 2020.08.29
===================================================================*/

#pragma once
#include "game_object.h"

class CUIFrame : public CGameObject
{
private:

	ID3D11Buffer*								m_FrameVertexBuffer = NULL;
	ID3D11Buffer*								m_FrameAnimVertexBuffer = NULL;

	static ID3D11ShaderResourceView*			m_FrameTexture;
	static ID3D11ShaderResourceView*			m_FrameAnimTexture;

	float m_AnimCount;

public:

	CUIFrame() {}	
	~CUIFrame() {}		

	static void Load();
	static void Unload();

	void Init();
	void Uninit();
	void Update();
	void Draw();

};