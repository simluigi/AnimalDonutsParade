/*==================================================================
DIRECTX11 �O�Z���� light.h
Author: Sim Luigi
Last Updated: 2020.08.17
===================================================================*/

#pragma once
#include "game_object.h"

class CLight : public CGameObject
{
public:
	CLight() {}		//constructor	�R���X�g���N�^
	~CLight() {}		//destructor		�f�X�g���N�^

	static void SetLightOn();
	static void SetLightOff();
};