/*==================================================================
DIRECTX11 三校合同 light.h
Author: Sim Luigi
Last Updated: 2020.08.17
===================================================================*/

#pragma once
#include "game_object.h"

class CLight : public CGameObject
{
public:
	CLight() {}		//constructor	コンストラクタ
	~CLight() {}		//destructor		デストラクタ

	static void SetLightOn();
	static void SetLightOff();
};