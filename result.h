/*==================================================================
DIRECTX11 éOçZçáìØ result.h
Author: Sim Luigi
Last Updated: 2020.08.25
===================================================================*/
#pragma once
#include "scene.h"

class CResult : public CScene
{
	bool	m_ExitFlag;				// if exiting scene

public:

	CResult() {}		
	~CResult() {}		

	static void UnloadResultResources(bool firstResult);

	void Init();
	void Uninit();
	void Update();
};