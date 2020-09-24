/*==================================================================
DIRECTX11 三校合同 UI_time.cpp
Author: Sim Luigi
Last Updated: 2020.08.24

UI Display class for timer.

2020.08.23
-UI_time.cpp, header file created.
2020.08.24
-finished implementation.
2020.08.29
-Countdown display added.
===================================================================*/

#include <math.h>
#include "main.h"
#include "renderer.h"
#include "light.h"
#include "scene.h"
#include "game.h"
#include "order.h"
#include "UI_time.h"

#define UI_NUMBER_UV_SLICE		(0.2f)		// 250px per UV /1250px  = 0.2f

#define UI_TIMER_SIZE			(80.0f)		// Each score digit size
#define UI_TIMER_START_X		(623.0f)	// starting digit offset X
#define UI_TIMER_START_Y		(20.0f)		// starting digit offset Y

#define UI_COUNTDOWN_SIZE		(150.0f)	
#define UI_COUNTDOWN_START_X	(645.0f)	// starting digit offset X
#define UI_COUNTDOWN_START_Y	(220.0f)	// starting digit offset Y


ID3D11ShaderResourceView*	CUITime::m_NumberUVMap = NULL;		//1250x750 UV Map

void CUITime::Init()
{

}

void CUITime::Uninit()
{
	m_TimeVertexBuffer->Release();
}

void CUITime::Update()
{

}

void CUITime::Draw()
{
	//=========================================
	// 共通設定
	// Common Settings

	CLight::SetLightOff();
	CRenderer::SetWorldViewProjection2D();
	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;

	// ゲームタイマーとカウントダウンが同じテクスチャーファイルを使用する
	// Use same texture for both countdown and timer display
	assert(m_NumberUVMap);
	CRenderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_NumberUVMap);

	// 表示によってデイフューズが変わる
	// Change diffuse color based on display type
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));

	//=========================================
	// ゲームタイマーを描画
	// Game Timer Draw

	int time = (int)CGame::GetTime();
	int digit = 0;
	int work = time % 10;

	VERTEX_DATA timeData;
	do
	{
		// position/UV offset
		timeData.PosOffsetX = UI_TIMER_START_X - (digit * UI_TIMER_SIZE / 2.0f);
		timeData.PosOffsetY = UI_TIMER_START_Y;
		timeData.UVOffsetX = (float)(work % 5) * UI_NUMBER_UV_SLICE;
		timeData.UVOffsetY = (float)(work / 5) * UI_NUMBER_UV_SLICE;

		// 1桁の場合、表示を真ん中に合わせて調整する
		// adjust for single digit
		if ((int)(CGame::GetTime() < 10))
			timeData.PosOffsetX -= 17.0f;

		timeData.Vertex[0].Position = D3DXVECTOR3(timeData.PosOffsetX, timeData.PosOffsetY, 0.0f);
		timeData.Vertex[0].Normal	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		timeData.Vertex[0].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		timeData.Vertex[0].TexCoord = D3DXVECTOR2(timeData.UVOffsetX, timeData.UVOffsetY);

		timeData.Vertex[1].Position = D3DXVECTOR3(timeData.PosOffsetX + UI_TIMER_SIZE, timeData.PosOffsetY, 0.0f);
		timeData.Vertex[1].Normal	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		timeData.Vertex[1].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		timeData.Vertex[1].TexCoord = D3DXVECTOR2(timeData.UVOffsetX + UI_NUMBER_UV_SLICE, timeData.UVOffsetY);

		timeData.Vertex[2].Position = D3DXVECTOR3(timeData.PosOffsetX, timeData.PosOffsetY + UI_TIMER_SIZE, 0.0f);
		timeData.Vertex[2].Normal	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		timeData.Vertex[2].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		timeData.Vertex[2].TexCoord = D3DXVECTOR2(timeData.UVOffsetX, timeData.UVOffsetY + UI_NUMBER_UV_SLICE);

		timeData.Vertex[3].Position = D3DXVECTOR3(timeData.PosOffsetX + UI_TIMER_SIZE, timeData.PosOffsetY + UI_TIMER_SIZE, 0.0f);
		timeData.Vertex[3].Normal	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		timeData.Vertex[3].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		timeData.Vertex[3].TexCoord = D3DXVECTOR2(timeData.UVOffsetX + UI_NUMBER_UV_SLICE, timeData.UVOffsetY + UI_NUMBER_UV_SLICE);

		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));				//clears memory for bd
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(VERTEX_3D) * 4;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));				//clears memory for sd
		sd.pSysMem = timeData.Vertex;

		CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_TimeVertexBuffer);

		// タイマーマテリアルディフューズ設定
		// Timer Material Diffuse Settings
		material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		CRenderer::SetMaterial(material);

		CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_TimeVertexBuffer, &stride, &offset);
		CRenderer::GetDeviceContext()->Draw(4, 0);

		// 描画計算（次の桁）
		// Draw computation (next digit)
		time /= 10;
		digit++;
		work = time % 10;

	} while (time > 0);

	//=========================================
	// カウントダウンーを描画 (ゲームタイマーの上に描画する）
	// Countdown Draw (after Timer so it overlaps it while scaling)

	VERTEX_DATA countdownData;

	if (CGame::GetGameStartFlag() == false && CGame::GetCountdown() > 0.0f)
	{
		// 一秒ディスプレイオフセット　		
		// one second display offset
		int countdown = (int)CGame::GetCountdown() + 1;
		int work = countdown % 10;

		// 数字の大きさは時間に合わせる
		// number size scales with timer
		float scale = (fmod(CGame::GetCountdown(), 1.0f) + 1.0f) * 0.75f;
		float scaleOffset = UI_COUNTDOWN_SIZE * scale;

		// position/UV offset
		countdownData.PosOffsetX = UI_COUNTDOWN_START_X;
		countdownData.PosOffsetY = UI_COUNTDOWN_START_Y;
		countdownData.UVOffsetX = (float)(work % 5) * UI_NUMBER_UV_SLICE;
		countdownData.UVOffsetY = (float)(work / 5) * UI_NUMBER_UV_SLICE;

		countdownData.Vertex[0].Position = D3DXVECTOR3(countdownData.PosOffsetX - scaleOffset, countdownData.PosOffsetY - scaleOffset, 0.0f);
		countdownData.Vertex[0].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		countdownData.Vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		countdownData.Vertex[0].TexCoord = D3DXVECTOR2(countdownData.UVOffsetX, countdownData.UVOffsetY);

		countdownData.Vertex[1].Position = D3DXVECTOR3(countdownData.PosOffsetX + scaleOffset, countdownData.PosOffsetY - scaleOffset, 0.0f);
		countdownData.Vertex[1].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		countdownData.Vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		countdownData.Vertex[1].TexCoord = D3DXVECTOR2(countdownData.UVOffsetX + UI_NUMBER_UV_SLICE, countdownData.UVOffsetY);

		countdownData.Vertex[2].Position = D3DXVECTOR3(countdownData.PosOffsetX - scaleOffset, countdownData.PosOffsetY + scaleOffset, 0.0f);
		countdownData.Vertex[2].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		countdownData.Vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		countdownData.Vertex[2].TexCoord = D3DXVECTOR2(countdownData.UVOffsetX, countdownData.UVOffsetY + UI_NUMBER_UV_SLICE);

		countdownData.Vertex[3].Position = D3DXVECTOR3(countdownData.PosOffsetX + scaleOffset, countdownData.PosOffsetY + scaleOffset, 0.0f);
		countdownData.Vertex[3].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		countdownData.Vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		countdownData.Vertex[3].TexCoord = D3DXVECTOR2(countdownData.UVOffsetX + UI_NUMBER_UV_SLICE, countdownData.UVOffsetY + UI_NUMBER_UV_SLICE);

		D3D11_BUFFER_DESC bd_Countdown;
		ZeroMemory(&bd_Countdown, sizeof(bd_Countdown));
		bd_Countdown.Usage = D3D11_USAGE_DEFAULT;
		bd_Countdown.ByteWidth = sizeof(VERTEX_3D) * 4;
		bd_Countdown.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd_Countdown.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd_Countdown;
		ZeroMemory(&sd_Countdown, sizeof(sd_Countdown));
		sd_Countdown.pSysMem = countdownData.Vertex;

		CRenderer::GetDevice()->CreateBuffer(&bd_Countdown, &sd_Countdown, &m_CountdownVertexBuffer);

		// カウントダウンマテリアルディフューズ設定
		// Countdown Material Diffuse Settings
		material.Diffuse = D3DXCOLOR(1.3f, 1.3f, 1.0f, 1.0f);
		CRenderer::SetMaterial(material);

		CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_CountdownVertexBuffer, &stride, &offset);
		CRenderer::GetDeviceContext()->Draw(4, 0);
	}

	D3DXMATRIX world;							// 3Dワールドマトリックス設定に戻る
	CRenderer::SetWorldMatrix(&world);
	CLight::SetLightOn();						// ライト有効
}

void CUITime::Load()
{
	// テキスチャー読み込み Read Texture
	// number UV map
	D3DX11CreateShaderResourceViewFromFile(CRenderer::GetDevice(),
		"Asset/Texture/AD_UV_Number_Map_250_Umber.png",
		NULL,
		NULL,
		&m_NumberUVMap,
		NULL);
	assert(m_NumberUVMap);
}

void CUITime::Unload()
{
	m_NumberUVMap->Release();
}
