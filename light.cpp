/*==================================================================
DIRECTX11 三校合同 light.cpp
Author: Sim Luigi
Last Updated: 2020.08.17
===================================================================*/

#include "main.h"
#include "renderer.h"
#include "light.h"

// ライティング有効
void CLight::SetLightOn()
{
	LIGHT light;
	light.Enable = true;
	light.Direction = D3DXVECTOR4(1.0f, -1.0f, 0.0f, 0.0f);
	D3DXVec4Normalize(&light.Direction, &light.Direction);
	light.Ambient = D3DXCOLOR(0.3f, 0.3f, 0.4f, 1.0f);
	light.Diffuse = D3DXCOLOR(1.4f, 1.4f, 1.4f, 1.0f);			//Light intensity 明るさ
	CRenderer::SetLight(light);
}

// ライティング無効
void CLight::SetLightOff()
{
	LIGHT light;
	light.Enable = false;
	light.Direction = D3DXVECTOR4(1.0f, -1.0f, 0.0f, 0.0f);
	D3DXVec4Normalize(&light.Direction, &light.Direction);
	light.Ambient = D3DXCOLOR(0.3f, 0.3f, 0.4f, 1.0f);
	light.Diffuse = D3DXCOLOR(1.4f, 1.4f, 1.4f, 1.0f);			//Light intensity 明るさ
	CRenderer::SetLight(light);
}