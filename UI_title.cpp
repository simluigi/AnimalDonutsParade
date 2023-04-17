/*==================================================================
DIRECTX11 三校合同 UI_title.cpp
Author: Sim Luigi
Last Updated: 2020.08.29

2020.08.29
-cleaned up code.

2020.08.30
-High Score display + update implemented (second play onwards)
-Fade in/out process for Enter: Game Start text
===================================================================*/
#include "main.h"
#include "manager.h"
#include "scene.h"
#include "input.h"
#include "game.h"
#include "score.h"
#include "UI_title.h"

#define UI_ENTER_SIZE_X		(520.0f)
#define UI_ENTER_SIZE_Y		(55.0f)
#define UI_ENTER_START_X	(380.0f)
#define UI_ENTER_START_Y	(470.0f)

#define UI_HIGH_SCORE_SIZE_X	(250.0f)
#define UI_HIGH_SCORE_SIZE_Y	(50.0f)
#define UI_HIGH_SCORE_START_X	(480.0f)
#define UI_HIGH_SCORE_START_Y	(550.0f)

#define UI_NUMBER_UV_SLICE		(0.2f)		// 250/1250 = 0.2	
#define UI_NUMBER_START_X		(710.0f)
#define UI_SCORE_NUMBER_SIZE	(50.0f)

ID3D11ShaderResourceView*	CUITitle::m_TitleTexture = NULL;
ID3D11ShaderResourceView*	CUITitle::m_SpaceTexture = NULL;
ID3D11ShaderResourceView*	CUITitle::m_HighScoreTextTexture = NULL;
ID3D11ShaderResourceView*	CUITitle::m_ScoreTexture = NULL;

void CUITitle::Init()
{
	m_FadeFlag = 0;
	m_FadeCount = 1.0f;
	m_AnimCount = 0.0f;

	//==================
	// タイトル画面の設定
	// Title Settings

	VERTEX_DATA	titleData;

	titleData.Vertex[0].Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	titleData.Vertex[0].Normal	 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	titleData.Vertex[0].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	titleData.Vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

	titleData.Vertex[1].Position = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	titleData.Vertex[1].Normal   = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	titleData.Vertex[1].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	titleData.Vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);

	titleData.Vertex[2].Position = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	titleData.Vertex[2].Normal   = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	titleData.Vertex[2].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	titleData.Vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);

	titleData.Vertex[3].Position = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
	titleData.Vertex[3].Normal   = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	titleData.Vertex[3].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	titleData.Vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);

	D3D11_BUFFER_DESC bd_Title;
	ZeroMemory(&bd_Title, sizeof(bd_Title));
	bd_Title.Usage = D3D11_USAGE_DEFAULT;
	bd_Title.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd_Title.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd_Title.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd_Title;
	ZeroMemory(&sd_Title, sizeof(sd_Title));
	sd_Title.pSysMem = titleData.Vertex;

	CRenderer::GetDevice()->CreateBuffer(&bd_Title, &sd_Title, &m_TitleVertexBuffer);


	//==================
	// 「Enter: Game Start」表示の設定
	// Enter: Game Start Display Settings

	VERTEX_DATA spaceData;

	// Frame
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
	
	//===================================
	// ハイスコアテキスト表示の設定
	// 「High Score」Text Display Settings

	VERTEX_DATA highScoreTextData;

	highScoreTextData.Vertex[0].Position = D3DXVECTOR3(UI_HIGH_SCORE_START_X, UI_HIGH_SCORE_START_Y, 0.0f);
	highScoreTextData.Vertex[0].Normal	 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	highScoreTextData.Vertex[0].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	highScoreTextData.Vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

	highScoreTextData.Vertex[1].Position = D3DXVECTOR3(UI_HIGH_SCORE_START_X + UI_HIGH_SCORE_SIZE_X, UI_HIGH_SCORE_START_Y, 0.0f);
	highScoreTextData.Vertex[1].Normal	 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	highScoreTextData.Vertex[1].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	highScoreTextData.Vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);

	highScoreTextData.Vertex[2].Position = D3DXVECTOR3(UI_HIGH_SCORE_START_X, UI_HIGH_SCORE_START_Y + UI_HIGH_SCORE_SIZE_Y, 0.0f);
	highScoreTextData.Vertex[2].Normal	 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	highScoreTextData.Vertex[2].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	highScoreTextData.Vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);

	highScoreTextData.Vertex[3].Position = D3DXVECTOR3(UI_HIGH_SCORE_START_X + UI_HIGH_SCORE_SIZE_X, UI_HIGH_SCORE_START_Y + UI_HIGH_SCORE_SIZE_Y, 0.0f);
	highScoreTextData.Vertex[3].Normal	 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	highScoreTextData.Vertex[3].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	highScoreTextData.Vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);

	D3D11_BUFFER_DESC bd_HighScoreText;
	ZeroMemory(&bd_HighScoreText, sizeof(bd_HighScoreText));
	bd_HighScoreText.Usage = D3D11_USAGE_DEFAULT;
	bd_HighScoreText.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd_HighScoreText.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd_HighScoreText.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd_HighScoreText;
	ZeroMemory(&sd_HighScoreText, sizeof(sd_HighScoreText));
	sd_HighScoreText.pSysMem = highScoreTextData.Vertex;

	CRenderer::GetDevice()->CreateBuffer(&bd_HighScoreText, &sd_HighScoreText, &m_HighScoreTextVertexBuffer);
}

void CUITitle::Uninit()
{
	m_TitleVertexBuffer->Release();
	m_SpaceVertexBuffer->Release();
	m_HighScoreTextVertexBuffer->Release();

	if (CManager::GetFirstPlay == false)
	{
		m_ScoreVertexBuffer->Release();
	}
}

void CUITitle::Update()
{

	// 「Enter: Game Start」フェイド処理 （見ずらくならないため、不透明に戻す速度の方が速い)
	// Fade in and out process for Enter: Game Start Text (Return to opaque is faster for visibility purposes)
	if (m_FadeFlag == 1 && m_FadeCount < 1.5f)
	{
		// フェイドイン Fade In (Fast)
		m_FadeCount += 0.025f;	
		if (m_FadeCount >= 1.5f)
		{
			m_FadeFlag = 0;
		}
	}

	if (m_FadeFlag == 0 && m_FadeCount > 0.0f)
	{
		// フェイドイン Fade Out (Slow)
		m_FadeCount -= 0.01f;
		if (m_FadeCount <= 0.0f)
		{
			m_FadeFlag = 1;
		}
	}
}

void CUITitle::Draw()
{
	VERTEX_DATA donutAnimData;

	CRenderer::SetWorldViewProjection2D();
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	CRenderer::SetMaterial(material);
	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;

	//==================
	// タイトル画面を描画
	// Title Draw

	CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_TitleVertexBuffer, &stride, &offset);
	CRenderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_TitleTexture);
	CRenderer::GetDeviceContext()->Draw(4, 0);

	//==================
	// 「Enter: Game Start」テキストを描画 (アニメーション)
	// Enter: Game Start Draw (animation: blink)

	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_FadeCount);
	CRenderer::SetMaterial(material);
	CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_SpaceVertexBuffer, &stride, &offset);
	CRenderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_SpaceTexture);
	CRenderer::GetDeviceContext()->Draw(4, 0);


	//==================
	// ハイスコアを描画（ゲームを一回以上プレイした場合のみ）
	// High Score Draw (only if game has been played at least once)
	if (CManager::GetFirstPlay() == false)
	{
		// フェイド中止
		material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		CRenderer::SetMaterial(material);

		//===================================
		// 「High Score:」テキストの描画
		// High Score Text
		CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_HighScoreTextVertexBuffer, &stride, &offset);
		CRenderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_HighScoreTextTexture);
		CRenderer::GetDeviceContext()->Draw(4, 0);

		//===================================
		// 実際のハイスコア（数字）の描画
		// Actual High Score　Draw

		int score = CScore::GetHighScore();
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

		do
		{
			// 位置・UVオフセット計算
			// Position, UV Offset Calculation
			scoreData.PosOffsetX = UI_NUMBER_START_X - (digit * UI_SCORE_NUMBER_SIZE / 2.0f) + (temp * UI_SCORE_NUMBER_SIZE / 2.5f);
			scoreData.PosOffsetY = UI_HIGH_SCORE_START_Y;
			scoreData.UVOffsetX = (float)(work % 5) * UI_NUMBER_UV_SLICE;
			scoreData.UVOffsetY = (float)(work / 5) * UI_NUMBER_UV_SLICE;

			scoreData.Vertex[0].Position = D3DXVECTOR3(scoreData.PosOffsetX, scoreData.PosOffsetY, 0.0f);
			scoreData.Vertex[0].Normal	 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			scoreData.Vertex[0].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
			scoreData.Vertex[0].TexCoord = D3DXVECTOR2(scoreData.UVOffsetX, scoreData.UVOffsetY);

			scoreData.Vertex[1].Position = D3DXVECTOR3(scoreData.PosOffsetX + UI_SCORE_NUMBER_SIZE, scoreData.PosOffsetY, 0.0f);
			scoreData.Vertex[1].Normal	 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			scoreData.Vertex[1].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
			scoreData.Vertex[1].TexCoord = D3DXVECTOR2(scoreData.UVOffsetX + UI_NUMBER_UV_SLICE, scoreData.UVOffsetY);

			scoreData.Vertex[2].Position = D3DXVECTOR3(scoreData.PosOffsetX, scoreData.PosOffsetY + UI_SCORE_NUMBER_SIZE, 0.0f);
			scoreData.Vertex[2].Normal	 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			scoreData.Vertex[2].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
			scoreData.Vertex[2].TexCoord = D3DXVECTOR2(scoreData.UVOffsetX, scoreData.UVOffsetY + UI_NUMBER_UV_SLICE);

			scoreData.Vertex[3].Position = D3DXVECTOR3(scoreData.PosOffsetX + UI_SCORE_NUMBER_SIZE, scoreData.PosOffsetY + UI_SCORE_NUMBER_SIZE, 0.0f);
			scoreData.Vertex[3].Normal   = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			scoreData.Vertex[3].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
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
}

void CUITitle::Load()
{
	// タイトル画面テクスチャー
	// Title Page Texture
	D3DX11CreateShaderResourceViewFromFile(CRenderer::GetDevice(),
		"Asset/Texture/AD_Title_No_Text.png",
		NULL,
		NULL,
		&m_TitleTexture,
		NULL);
	assert(m_TitleTexture);

	// 「Enter: Game Start] (アニメーション)テクスチャー
	// Title Page Texture
	D3DX11CreateShaderResourceViewFromFile(CRenderer::GetDevice(),
		"Asset/Texture/AD_Title_Space_Game_Start.png",
		NULL,
		NULL,
		&m_SpaceTexture,
		NULL);
	assert(m_SpaceTexture);

	// ハイスコアテキストテクスチャー
	// High Score TextTexture
	D3DX11CreateShaderResourceViewFromFile(CRenderer::GetDevice(),
		"Asset/Texture/AD_Title_High_Score.png",
		NULL,
		NULL,
		&m_HighScoreTextTexture,
		NULL);
	assert(m_HighScoreTextTexture);

	// 実際のハイスコアテクスチャー
	// Actual High Score TextTexture
	D3DX11CreateShaderResourceViewFromFile(CRenderer::GetDevice(),
		"Asset/Texture/AD_UV_Number_Map_250_Umber.png",
		NULL,
		NULL,
		&m_ScoreTexture,
		NULL);
	assert(m_ScoreTexture);
}

void CUITitle::Unload()
{
	m_TitleTexture->Release();
	m_SpaceTexture->Release();
	m_HighScoreTextTexture->Release();
	m_ScoreTexture->Release();
}