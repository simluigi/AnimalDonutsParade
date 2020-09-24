/*==================================================================
DIRECTX11 三校合同 UI_title.cpp
Author: Sim Luigi
Last Updated: 2020.08.29

2020.08.29
-m_ResultAnimTimer: Staged Display animation

2020.08.30
-synced all staged displays with sound BGM_Result.wav
-added High Score donut icon

2020.09.01
-replaced Enter with Space key
===================================================================*/

#include "main.h"
#include "manager.h"
#include "scene.h"
#include "input.h"
#include "score.h"
#include "result.h"
#include "UI_result.h"

#define UI_NUMBER_UV_SLICE			(0.2f)		// 250/1250 = 0.2	

#define UI_SCORE_SIZE				(75.0f)		// Each score digit size
#define UI_SCORE_START_X			(625.0f)	// starting digit offset X
#define UI_SCORE_START_Y			(250.0f)	// starting digit offset Y

#define UI_ORDERS_SIZE				(60.0f)
#define UI_ORDERS_START_X			(720.0f)	// starting digit offset X
#define UI_ORDERS_START_Y			(330.0f)	// starting digit offset Y

#define UI_DONUT_COUNT_SIZE			(40.0f)
#define UI_DONUT_COUNT_START_X		(280.0f)	// starting digit offset X
#define UI_DONUT_COUNT_START_Y		(485.0f)	// starting digit offset Y
#define UI_DONUT_COUNT_SPACING		(168.0f)	// space between printing

#define UI_HIGH_SCORE_SIZE			(250.0f)
#define UI_HIGH_SCORE_START_X		(850.0f)	// starting digit offset X
#define UI_HIGH_SCORE_START_Y		(148.0f)	// starting digit offset Y

#define UI_ENTER_SIZE_X				(350.0f)
#define UI_ENTER_SIZE_Y				(60.0f)
#define UI_ENTER_START_X			(464.0f)	// starting digit offset X
#define UI_ENTER_START_Y			(530.0f)	// starting digit offset Y

ID3D11ShaderResourceView*	CUIResult::m_ResultFrameTexture = NULL;
ID3D11ShaderResourceView*	CUIResult::m_ScoreTexture		= NULL;
ID3D11ShaderResourceView*	CUIResult::m_HighScoreTexture	= NULL;
ID3D11ShaderResourceView*	CUIResult::m_SpaceTexture		= NULL;

void CUIResult::Init()
{
	m_AnimCount = 0.0f;
	m_HighScoreUpdate = CScore::UpdateHighScore(CScore::GetScore());

	//=========================================
	// リザルトバックグラウンドの頂点データ
	// Background (Frame) 

	VERTEX_DATA	resultData;

	resultData.Vertex[0].Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	resultData.Vertex[0].Normal	  = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	resultData.Vertex[0].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	resultData.Vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

	resultData.Vertex[1].Position = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	resultData.Vertex[1].Normal	  = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	resultData.Vertex[1].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	resultData.Vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);

	resultData.Vertex[2].Position = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	resultData.Vertex[2].Normal	  = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	resultData.Vertex[2].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	resultData.Vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);

	resultData.Vertex[3].Position = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
	resultData.Vertex[3].Normal	  = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	resultData.Vertex[3].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	resultData.Vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);

	D3D11_BUFFER_DESC bd_Result;
	ZeroMemory(&bd_Result, sizeof(bd_Result));
	bd_Result.Usage = D3D11_USAGE_DEFAULT;
	bd_Result.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd_Result.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd_Result.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd_Result;
	ZeroMemory(&sd_Result, sizeof(sd_Result));
	sd_Result.pSysMem = resultData.Vertex;

	CRenderer::GetDevice()->CreateBuffer(&bd_Result, &sd_Result, &m_ResultFrameVertexBuffer);

	VERTEX_DATA highScoreData;

	D3D11_BUFFER_DESC bd_HighScore;
	ZeroMemory(&bd_HighScore, sizeof(bd_HighScore));
	bd_HighScore.Usage = D3D11_USAGE_DEFAULT;
	bd_HighScore.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd_HighScore.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd_HighScore.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd_HighScore;
	ZeroMemory(&sd_HighScore, sizeof(sd_HighScore));
	sd_HighScore.pSysMem = highScoreData.Vertex;

	CRenderer::GetDevice()->CreateBuffer(&bd_HighScore, &sd_HighScore, &m_HighScoreVertexBuffer);
}


void CUIResult::Uninit()
{
	m_ResultFrameVertexBuffer->Release();
	m_ScoreVertexBuffer->Release();
	m_HighScoreVertexBuffer->Release();
}

void CUIResult::Update()
{

	if (m_AnimCount < 55.0f)
	{
		m_AnimCount += 0.1f;
	}
}

void CUIResult::Draw()
{	
	//=========================================
	// 共通設定
	// Common Settings

	CRenderer::SetWorldViewProjection2D();	
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	CRenderer::SetMaterial(material);
	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//=========================================
	// リザルトバックグラウンドを描画
	// Background (Frame) Draw

	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_ResultFrameVertexBuffer, &stride, &offset);

	//Texture Settings
	//テキスチャー設定
	CRenderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_ResultFrameTexture);

	//Draw Polygon (4: # of vertices)
	//描画（頂点数：４）
	CRenderer::GetDeviceContext()->Draw(4, 0);

	//=========================================
	// スコア（数字）描画
	// Score (Number) Display

	int score = CScore::GetScore();
	int work = score % 10;
	int digit = 0;
	int temp = score;

	// 桁数を特定する
	// determine digit count from the start
	while (temp > 0)
	{
		temp /= 10;
		digit++;
	}
	temp = digit;
	digit = 0;


	VERTEX_DATA scoreData;
	if (m_AnimCount > 2.0f)			//staged display
	{
		do
		{
			scoreData.PosOffsetX = UI_SCORE_START_X - (digit * UI_SCORE_SIZE / 2.0f) + (temp * UI_SCORE_SIZE / 2.5f);
			scoreData.PosOffsetY = UI_SCORE_START_Y;
			scoreData.UVOffsetX = (float)(work % 5) * UI_NUMBER_UV_SLICE;
			scoreData.UVOffsetY = (float)(work / 5) * UI_NUMBER_UV_SLICE;

			scoreData.Vertex[0].Position = D3DXVECTOR3(scoreData.PosOffsetX, scoreData.PosOffsetY, 0.0f);
			scoreData.Vertex[0].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			scoreData.Vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
			scoreData.Vertex[0].TexCoord = D3DXVECTOR2(scoreData.UVOffsetX, scoreData.UVOffsetY);

			scoreData.Vertex[1].Position = D3DXVECTOR3(scoreData.PosOffsetX + UI_SCORE_SIZE, scoreData.PosOffsetY, 0.0f);
			scoreData.Vertex[1].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			scoreData.Vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
			scoreData.Vertex[1].TexCoord = D3DXVECTOR2(scoreData.UVOffsetX + UI_NUMBER_UV_SLICE, scoreData.UVOffsetY);

			scoreData.Vertex[2].Position = D3DXVECTOR3(scoreData.PosOffsetX, scoreData.PosOffsetY + UI_SCORE_SIZE, 0.0f);
			scoreData.Vertex[2].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			scoreData.Vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
			scoreData.Vertex[2].TexCoord = D3DXVECTOR2(scoreData.UVOffsetX, scoreData.UVOffsetY + UI_NUMBER_UV_SLICE);

			scoreData.Vertex[3].Position = D3DXVECTOR3(scoreData.PosOffsetX + UI_SCORE_SIZE, scoreData.PosOffsetY + UI_SCORE_SIZE, 0.0f);
			scoreData.Vertex[3].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			scoreData.Vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
			scoreData.Vertex[3].TexCoord = D3DXVECTOR2(scoreData.UVOffsetX + UI_NUMBER_UV_SLICE, scoreData.UVOffsetY + UI_NUMBER_UV_SLICE);

			D3D11_BUFFER_DESC bd_Score;
			ZeroMemory(&bd_Score, sizeof(bd_Score));
			bd_Score.Usage = D3D11_USAGE_DEFAULT;
			bd_Score.ByteWidth = sizeof(VERTEX_3D) * 4;
			bd_Score.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			bd_Score.CPUAccessFlags = 0;

			D3D11_SUBRESOURCE_DATA sd_Score;
			ZeroMemory(&sd_Score, sizeof(sd_Score));
			sd_Score.pSysMem = scoreData.Vertex;

			CRenderer::GetDevice()->CreateBuffer(&bd_Score, &sd_Score, &m_ScoreVertexBuffer);
			CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_ScoreVertexBuffer, &stride, &offset);
			CRenderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_ScoreTexture);
			CRenderer::GetDeviceContext()->Draw(4, 0);

			score /= 10;
			digit++;
			work = score % 10;
		} while (score > 0);
	}
	//=========================================
	// 注文完了回数を描画
	// Orders Completed Display

	int orders = CScore::GetOrdersCompleted();
	digit = 0;
	work = orders % 10;

	VERTEX_DATA ordersData;
	if (m_AnimCount > 12.0f)			//staged display
	{
		do
		{
			// position/UV offset
			ordersData.PosOffsetX = UI_ORDERS_START_X - (digit * UI_ORDERS_SIZE / 2.0f);
			ordersData.PosOffsetY = UI_ORDERS_START_Y;
			ordersData.UVOffsetX = (float)(work % 5) * UI_NUMBER_UV_SLICE;
			ordersData.UVOffsetY = (float)(work / 5) * UI_NUMBER_UV_SLICE;

			// 2桁の場合、表示を真ん中に合わせて調整する
			// adjust for double digit
			if (CScore::GetOrdersCompleted() >= 10)
				ordersData.PosOffsetX += UI_ORDERS_SIZE / 2.0f;

			ordersData.Vertex[0].Position = D3DXVECTOR3(ordersData.PosOffsetX, ordersData.PosOffsetY, 0.0f);
			ordersData.Vertex[0].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			ordersData.Vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
			ordersData.Vertex[0].TexCoord = D3DXVECTOR2(ordersData.UVOffsetX, ordersData.UVOffsetY);

			ordersData.Vertex[1].Position = D3DXVECTOR3(ordersData.PosOffsetX + UI_ORDERS_SIZE, ordersData.PosOffsetY, 0.0f);
			ordersData.Vertex[1].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			ordersData.Vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
			ordersData.Vertex[1].TexCoord = D3DXVECTOR2(ordersData.UVOffsetX + UI_NUMBER_UV_SLICE, ordersData.UVOffsetY);

			ordersData.Vertex[2].Position = D3DXVECTOR3(ordersData.PosOffsetX, ordersData.PosOffsetY + UI_ORDERS_SIZE, 0.0f);
			ordersData.Vertex[2].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			ordersData.Vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
			ordersData.Vertex[2].TexCoord = D3DXVECTOR2(ordersData.UVOffsetX, ordersData.UVOffsetY + UI_NUMBER_UV_SLICE);

			ordersData.Vertex[3].Position = D3DXVECTOR3(ordersData.PosOffsetX + UI_ORDERS_SIZE, ordersData.PosOffsetY + UI_ORDERS_SIZE, 0.0f);
			ordersData.Vertex[3].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			ordersData.Vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
			ordersData.Vertex[3].TexCoord = D3DXVECTOR2(ordersData.UVOffsetX + UI_NUMBER_UV_SLICE, ordersData.UVOffsetY + UI_NUMBER_UV_SLICE);

			D3D11_BUFFER_DESC bd_Orders;
			ZeroMemory(&bd_Orders, sizeof(bd_Orders));
			bd_Orders.Usage = D3D11_USAGE_DEFAULT;
			bd_Orders.ByteWidth = sizeof(VERTEX_3D) * 4;
			bd_Orders.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			bd_Orders.CPUAccessFlags = 0;

			D3D11_SUBRESOURCE_DATA sd_Orders;
			ZeroMemory(&sd_Orders, sizeof(sd_Orders));
			sd_Orders.pSysMem = ordersData.Vertex;

			//Create new Vertex Buffer per digit
			CRenderer::GetDevice()->CreateBuffer(&bd_Orders, &sd_Orders, &m_ScoreVertexBuffer);
			CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_ScoreVertexBuffer, &stride, &offset);
			CRenderer::GetDeviceContext()->Draw(4, 0);

			orders /= 10;
			digit++;
			work = orders % 10;
		} while (orders > 0);
	}

	//=========================================
	// ドーナツ種類別の数を描画
	// Donuts by Type Display

	int donutCount;
	VERTEX_DATA donutCountData;

	for (int i = 0; i < DONUT_TYPE_COUNT; i++)
	{
		donutCount = CScore::GetDonutCount(i);
		digit = 0;
		work = donutCount % 10;

		if (m_AnimCount > 22.0f + (float)i* 3)			//staged display
		{
			do
			{
				// position/UV offset
				donutCountData.PosOffsetX = UI_DONUT_COUNT_START_X - (digit * UI_DONUT_COUNT_SIZE / 2.0f) + ((float)i * UI_DONUT_COUNT_SPACING);
				donutCountData.PosOffsetY = UI_DONUT_COUNT_START_Y;
				donutCountData.UVOffsetX = (float)(work % 5) * UI_NUMBER_UV_SLICE;
				donutCountData.UVOffsetY = (float)(work / 5) * UI_NUMBER_UV_SLICE;

				// 2桁の場合、表示を真ん中に合わせて調整する
				// adjust for double digit
				if (CScore::GetDonutCount(i) >= 10)
					donutCountData.PosOffsetX += UI_DONUT_COUNT_SIZE / 2.0f;

				donutCountData.Vertex[0].Position = D3DXVECTOR3(donutCountData.PosOffsetX, donutCountData.PosOffsetY, 0.0f);
				donutCountData.Vertex[0].Normal   = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				donutCountData.Vertex[0].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
				donutCountData.Vertex[0].TexCoord = D3DXVECTOR2(donutCountData.UVOffsetX, donutCountData.UVOffsetY);

				donutCountData.Vertex[1].Position = D3DXVECTOR3(donutCountData.PosOffsetX + UI_DONUT_COUNT_SIZE, donutCountData.PosOffsetY, 0.0f);
				donutCountData.Vertex[1].Normal   = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				donutCountData.Vertex[1].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
				donutCountData.Vertex[1].TexCoord = D3DXVECTOR2(donutCountData.UVOffsetX + UI_NUMBER_UV_SLICE, donutCountData.UVOffsetY);

				donutCountData.Vertex[2].Position = D3DXVECTOR3(donutCountData.PosOffsetX, donutCountData.PosOffsetY + UI_DONUT_COUNT_SIZE, 0.0f);
				donutCountData.Vertex[2].Normal   = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				donutCountData.Vertex[2].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
				donutCountData.Vertex[2].TexCoord = D3DXVECTOR2(donutCountData.UVOffsetX, donutCountData.UVOffsetY + UI_NUMBER_UV_SLICE);

				donutCountData.Vertex[3].Position = D3DXVECTOR3(donutCountData.PosOffsetX + UI_DONUT_COUNT_SIZE, donutCountData.PosOffsetY + UI_DONUT_COUNT_SIZE, 0.0f);
				donutCountData.Vertex[3].Normal   = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				donutCountData.Vertex[3].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
				donutCountData.Vertex[3].TexCoord = D3DXVECTOR2(donutCountData.UVOffsetX + UI_NUMBER_UV_SLICE, donutCountData.UVOffsetY + UI_NUMBER_UV_SLICE);

				D3D11_BUFFER_DESC bd_DonutCount;
				ZeroMemory(&bd_DonutCount, sizeof(bd_DonutCount));
				bd_DonutCount.Usage = D3D11_USAGE_DEFAULT;
				bd_DonutCount.ByteWidth = sizeof(VERTEX_3D) * 4;
				bd_DonutCount.BindFlags = D3D11_BIND_VERTEX_BUFFER;
				bd_DonutCount.CPUAccessFlags = 0;

				D3D11_SUBRESOURCE_DATA sd_DonutCount;
				ZeroMemory(&sd_DonutCount, sizeof(sd_DonutCount));
				sd_DonutCount.pSysMem = donutCountData.Vertex;

				//Create new Vertex Buffer per digit
				CRenderer::GetDevice()->CreateBuffer(&bd_DonutCount, &sd_DonutCount, &m_ScoreVertexBuffer);
				CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_ScoreVertexBuffer, &stride, &offset);
				CRenderer::GetDeviceContext()->Draw(4, 0);

				donutCount /= 10;
				digit++;
				work = donutCount % 10;
			} while (donutCount > 0);
		}
	}

	//=========================================
	// ハイスコアアイコンを描画（更新された場合）
	// High Score Icon (only if High Score is complete)

	if (m_AnimCount > 42.0f && m_HighScoreUpdate == true )
	{
		VERTEX_DATA	highScoreData;

		highScoreData.Vertex[0].Position = D3DXVECTOR3(UI_HIGH_SCORE_START_X, UI_HIGH_SCORE_START_Y, 0.0f);
		highScoreData.Vertex[0].Normal	 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		highScoreData.Vertex[0].Diffuse	 = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		highScoreData.Vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

		highScoreData.Vertex[1].Position = D3DXVECTOR3(UI_HIGH_SCORE_START_X + UI_HIGH_SCORE_SIZE, UI_HIGH_SCORE_START_Y, 0.0f);
		highScoreData.Vertex[1].Normal	 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		highScoreData.Vertex[1].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		highScoreData.Vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);

		highScoreData.Vertex[2].Position = D3DXVECTOR3(UI_HIGH_SCORE_START_X, UI_HIGH_SCORE_START_Y+ UI_HIGH_SCORE_SIZE, 0.0f);
		highScoreData.Vertex[2].Normal	 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		highScoreData.Vertex[2].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		highScoreData.Vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);

		highScoreData.Vertex[3].Position = D3DXVECTOR3(UI_HIGH_SCORE_START_X + UI_HIGH_SCORE_SIZE, UI_HIGH_SCORE_START_Y + UI_HIGH_SCORE_SIZE, 0.0f);
		highScoreData.Vertex[3].Normal	 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		highScoreData.Vertex[3].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		highScoreData.Vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);

		D3D11_BUFFER_DESC bd_HighScore;
		ZeroMemory(&bd_HighScore, sizeof(bd_HighScore));
		bd_HighScore.Usage = D3D11_USAGE_DEFAULT;
		bd_HighScore.ByteWidth = sizeof(VERTEX_3D) * 4;
		bd_HighScore.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd_HighScore.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd_HighScore;
		ZeroMemory(&sd_HighScore, sizeof(sd_HighScore));
		sd_HighScore.pSysMem = highScoreData.Vertex;

		CRenderer::GetDevice()->CreateBuffer(&bd_HighScore, &sd_HighScore, &m_HighScoreVertexBuffer);
		CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_HighScoreVertexBuffer, &stride, &offset);
		CRenderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_HighScoreTexture);
		CRenderer::GetDeviceContext()->Draw(4, 0);
	}

	//=========================================
	// PRESS ENTERを描画（画面遷移方法を教える）
	// PRESS ENTER (to proceed to title page)

	if (m_AnimCount > 50.0f)
	{
		VERTEX_DATA	spaceData;

		spaceData.Vertex[0].Position = D3DXVECTOR3(UI_ENTER_START_X, UI_ENTER_START_Y, 0.0f);
		spaceData.Vertex[0].Normal	 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		spaceData.Vertex[0].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		spaceData.Vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

		spaceData.Vertex[1].Position = D3DXVECTOR3(UI_ENTER_START_X + UI_ENTER_SIZE_X, UI_ENTER_START_Y, 0.0f);
		spaceData.Vertex[1].Normal	 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		spaceData.Vertex[1].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		spaceData.Vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);

		spaceData.Vertex[2].Position = D3DXVECTOR3(UI_ENTER_START_X, UI_ENTER_START_Y + UI_ENTER_SIZE_Y, 0.0f);
		spaceData.Vertex[2].Normal	 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		spaceData.Vertex[2].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		spaceData.Vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);

		spaceData.Vertex[3].Position = D3DXVECTOR3(UI_ENTER_START_X + UI_ENTER_SIZE_X, UI_ENTER_START_Y + UI_ENTER_SIZE_Y, 0.0f);
		spaceData.Vertex[3].Normal	 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		spaceData.Vertex[3].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		spaceData.Vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);

		D3D11_BUFFER_DESC bd_Space;
		ZeroMemory(&bd_Space, sizeof(bd_Space));
		bd_Space.Usage = D3D11_USAGE_DEFAULT;
		bd_Space.ByteWidth = sizeof(VERTEX_3D) * 4;
		bd_Space.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd_Space.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd_Space;
		ZeroMemory(&sd_Space, sizeof(sd_Space));
		sd_Space.pSysMem = spaceData.Vertex;

		CRenderer::GetDevice()->CreateBuffer(&bd_Space, &sd_Space, &m_SpaceVertexBuffer);
		CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_SpaceVertexBuffer, &stride, &offset);
		CRenderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_SpaceTexture);
		CRenderer::GetDeviceContext()->Draw(4, 0);
	}
}

void CUIResult::Load()
{
	//テキスチャー読み込み Read Texture
	D3DX11CreateShaderResourceViewFromFile(CRenderer::GetDevice(),
		"Asset/Texture/AD_Result.png",
		NULL,
		NULL,
		&m_ResultFrameTexture,
		NULL);
	assert(m_ResultFrameTexture);

	D3DX11CreateShaderResourceViewFromFile(CRenderer::GetDevice(),
		"Asset/Texture/AD_UV_Number_Map_80_Pink.png",
		NULL,
		NULL,
		&m_ScoreTexture,
		NULL);
	assert(m_ScoreTexture);

	D3DX11CreateShaderResourceViewFromFile(CRenderer::GetDevice(),
		"Asset/Texture/AD_High_Score_Stamp.png",
		NULL,
		NULL,
		&m_HighScoreTexture,
		NULL);
	assert(m_HighScoreTexture);

	D3DX11CreateShaderResourceViewFromFile(CRenderer::GetDevice(),
		"Asset/Texture/AD_Press_Space.png",
		NULL,
		NULL,
		&m_SpaceTexture,
		NULL);
	assert(m_SpaceTexture);
}

void CUIResult::Unload()
{
	m_ResultFrameTexture->Release();
	m_ScoreTexture->Release();
	m_HighScoreTexture->Release();
	m_SpaceTexture->Release();
}