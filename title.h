/*==================================================================
DIRECTX11 éOçZçáìØ title.h
Author: Sim Luigi
Last Updated: 2020.08.25
===================================================================*/
#pragma once
#include "scene.h"

class CTitle : public CScene
{
	bool	m_ExitFlag;				//if exiting scene

public:

	CTitle() {}	
	~CTitle() {}

	void Init();
	void Uninit();
	void Update();

	static void UnloadTitleResources();
};