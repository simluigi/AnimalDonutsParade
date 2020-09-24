
/*==================================================================
DIRECTX11 三校合同 UI_score.cpp
Author: Sim Luigi
Last Updated: 2020.08.28

UI Display class for score.

2020.08.24
-header, .cpp file created.

2020.08.28
-renamed bd_Score, sd_Score, vertexBuffer variables.
===================================================================*/

#include "main.h"
#include "renderer.h"
#include "light.h"
#include "scene.h"
#include "game.h"
#include "order.h"
#include "score.h"
#include "UI_score.h"

#define UI_NUMBER_UV_SLICE				(0.2f)		// 250/1250 = 0.2	

#define UI_SCORE_BOX_SIZE				(60.0f)		// Each score digit size
#define UI_SCORE_STARTING_PLACE_X		(1200.0f)	// starting digit offset X
#define UI_SCORE_STARTING_PLACE_Y		(25.0f)		// starting digit offset Y

//static variables
ID3D11ShaderResourceView*	CUIScore::m_NumberUVMap = NULL;		//1250x750 UV Map

void CUIScore::Init()
{
	int score = CScore::GetScore();
	int digit = 0;
	int work  = score % 10;
		
	// actual vertex data in Update()
	VERTEX_DATA scoreData;

	D3D11_BUFFER_DESC bd_Score;
	ZeroMemory(&bd_Score, sizeof(bd_Score));				//clears memory for bd_Score
	bd_Score.Usage = D3D11_USAGE_DEFAULT;
	bd_Score.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd_Score.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd_Score.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd_Score;
	ZeroMemory(&sd_Score, sizeof(sd_Score));				//clears memory for sd_Score
	sd_Score.pSysMem = scoreData.Vertex;

	CRenderer::GetDevice()->CreateBuffer(&bd_Score, &sd_Score, &m_ScoreVertexBuffer);
}

void CUIScore::Uninit()
{
	m_ScoreVertexBuffer->Release();
}

void CUIScore::Update()
{

}

void CUIScore::Draw()
{	
	// 描画計算変数
	// Draw calculation variables
	int score = CScore::GetScore();
	int digit = 0;
	int work = score % 10;
	VERTEX_DATA scoreData;

	CLight::SetLightOff();						//ライト無効
	CRenderer::SetWorldViewProjection2D();

	//Material Settings
	//マテリアル設定
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	CRenderer::SetMaterial(material);

	//single texture with UV mapping for all icons
	assert(m_NumberUVMap);
	CRenderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_NumberUVMap);

	//Primitive Topology Settings
	//プリミティブトポロジー設定
	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	do 
	{
		// position/UV offset
		scoreData.PosOffsetX = UI_SCORE_STARTING_PLACE_X - (digit * UI_SCORE_BOX_SIZE / 2.0f);
		scoreData.PosOffsetY = UI_SCORE_STARTING_PLACE_Y;
		scoreData.UVOffsetX = (float)(work % 5) * UI_NUMBER_UV_SLICE;
		scoreData.UVOffsetY = (float)(work / 5) * UI_NUMBER_UV_SLICE;

		scoreData.Vertex[0].Position = D3DXVECTOR3(scoreData.PosOffsetX, scoreData.PosOffsetY, 0.0f);
		scoreData.Vertex[0].Normal	 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		scoreData.Vertex[0].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		scoreData.Vertex[0].TexCoord = D3DXVECTOR2(scoreData.UVOffsetX, scoreData.UVOffsetY);

		scoreData.Vertex[1].Position = D3DXVECTOR3(scoreData.PosOffsetX + UI_SCORE_BOX_SIZE, scoreData.PosOffsetY, 0.0f);
		scoreData.Vertex[1].Normal	 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		scoreData.Vertex[1].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		scoreData.Vertex[1].TexCoord = D3DXVECTOR2(scoreData.UVOffsetX + UI_NUMBER_UV_SLICE, scoreData.UVOffsetY);

		scoreData.Vertex[2].Position = D3DXVECTOR3(scoreData.PosOffsetX, scoreData.PosOffsetY + UI_SCORE_BOX_SIZE, 0.0f);
		scoreData.Vertex[2].Normal	 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		scoreData.Vertex[2].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		scoreData.Vertex[2].TexCoord = D3DXVECTOR2(scoreData.UVOffsetX, scoreData.UVOffsetY + UI_NUMBER_UV_SLICE);

		scoreData.Vertex[3].Position = D3DXVECTOR3
		(scoreData.PosOffsetX + UI_SCORE_BOX_SIZE, scoreData.PosOffsetY + UI_SCORE_BOX_SIZE, 0.0f);
		scoreData.Vertex[3].Normal	 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		scoreData.Vertex[3].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		scoreData.Vertex[3].TexCoord = D3DXVECTOR2(scoreData.UVOffsetX + UI_NUMBER_UV_SLICE, scoreData.UVOffsetY + UI_NUMBER_UV_SLICE);

		D3D11_BUFFER_DESC bd_Score;
		ZeroMemory(&bd_Score, sizeof(bd_Score));				//clears memory for bd_Score
		bd_Score.Usage = D3D11_USAGE_DEFAULT;
		bd_Score.ByteWidth = sizeof(VERTEX_3D) * 4;
		bd_Score.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd_Score.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd_Score;
		ZeroMemory(&sd_Score, sizeof(sd_Score));				//clears memory for sd_Score
		sd_Score.pSysMem = scoreData.Vertex;

		//Create new Vertex Buffer per digit
		CRenderer::GetDevice()->CreateBuffer(&bd_Score, &sd_Score, &m_ScoreVertexBuffer);

		//Vertex Buffer Settings
		//頂点バッファ設定
		UINT stride = sizeof(VERTEX_3D);
		UINT offset = 0;
		CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_ScoreVertexBuffer, &stride, &offset);

		//Draw Polygon (4: # of vertices)
		//描画（頂点数：４）
		CRenderer::GetDeviceContext()->Draw(4, 0);

		score /= 10;
		digit++;
		work = score % 10;
	} while (score > 0);

	D3DXMATRIX world;						// 3Dワールドマトリックス設定に戻る
	CRenderer::SetWorldMatrix(&world);
	CLight::SetLightOn();					// ライト有効
}

void CUIScore::Load()
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

void CUIScore::Unload()
{
	m_NumberUVMap->Release();
}
