/*==================================================================
DIRECTX11 三校合同 load_screen.h
Author: Sim Luigi
Last Updated: 2020.08.25
===================================================================*/
#pragma once
#include "scene.h"

#define ICON_COUNT		3

class CLoadScreen : public CGameObject
{
	static bool  m_FadeFlag;
	static bool  m_UpDown;
	static float m_FadeCount;		
	static float m_AnimCount;

	static ID3D11Buffer*						m_LoadingScreenBuffer;
	static ID3D11Buffer*						m_LoadingAnimationBuffer[ICON_COUNT];	// = ICON_COUNT

	static ID3D11ShaderResourceView*			m_LoadingScreenTexture;
	static ID3D11ShaderResourceView*			m_LoadingAnimationTexture;


public:

	CLoadScreen() {}		//コンストラクタ		Constructor
	~CLoadScreen() {}		//デストラクタ			Destructor

	static void FadeIn();
	static void FadeOut();
	static float GetFadeCount() { return m_FadeCount; }

	static void Load();
	static void Unload();

	void Init();
	void Uninit();
	void Update();
	void Draw();


};
