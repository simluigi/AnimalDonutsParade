/*==================================================================
DIRECTX11 三校合同 load_screen.cpp
Author: Sim Luigi
Last Updated: 2020.08.25
===================================================================*/
#include "main.h"
#include "manager.h"
#include "scene.h"
#include "input.h"
#include "light.h"
#include "load_screen.h"

#define ICON_START_X	(725.0f)
#define ICON_START_Y	(520.0f)
#define ICON_SIZE       (130.0f)

bool						CLoadScreen::m_FadeFlag;
bool						CLoadScreen::m_UpDown;
float						CLoadScreen::m_FadeCount;
float						CLoadScreen::m_AnimCount;
ID3D11Buffer*				CLoadScreen::m_LoadingScreenBuffer		= NULL;
ID3D11Buffer*				CLoadScreen::m_LoadingAnimationBuffer[ICON_COUNT];
ID3D11ShaderResourceView*	CLoadScreen::m_LoadingScreenTexture		= NULL;
ID3D11ShaderResourceView*	CLoadScreen::m_LoadingAnimationTexture	= NULL;


void CLoadScreen::FadeIn()
{
	m_FadeFlag = 1;
	m_FadeCount = 0.0f;
}

void CLoadScreen::FadeOut()
{
	m_FadeFlag = 0;
	m_FadeCount = 1.5f;

}

void CLoadScreen::Init()
{

	VERTEX_DATA	loadingScreenData;
	m_FadeFlag = 0;
	m_FadeCount = 0.0f;
	m_UpDown = 0;
	m_AnimCount = 0.0f;

	// Loading Screen Frame
	loadingScreenData.Vertex[0].Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	loadingScreenData.Vertex[0].Normal	 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	loadingScreenData.Vertex[0].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	loadingScreenData.Vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

	loadingScreenData.Vertex[1].Position = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	loadingScreenData.Vertex[1].Normal   = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	loadingScreenData.Vertex[1].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	loadingScreenData.Vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);

	loadingScreenData.Vertex[2].Position = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	loadingScreenData.Vertex[2].Normal   = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	loadingScreenData.Vertex[2].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	loadingScreenData.Vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);

	loadingScreenData.Vertex[3].Position = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
	loadingScreenData.Vertex[3].Normal   = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	loadingScreenData.Vertex[3].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	loadingScreenData.Vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);

	D3D11_BUFFER_DESC bd_LoadingScreen;
	ZeroMemory(&bd_LoadingScreen, sizeof(bd_LoadingScreen));
	bd_LoadingScreen.Usage = D3D11_USAGE_DEFAULT;
	bd_LoadingScreen.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd_LoadingScreen.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd_LoadingScreen.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd_LoadingScreen;
	ZeroMemory(&sd_LoadingScreen, sizeof(sd_LoadingScreen));
	sd_LoadingScreen.pSysMem = loadingScreenData.Vertex;

	CRenderer::GetDevice()->CreateBuffer(&bd_LoadingScreen, &sd_LoadingScreen, &m_LoadingScreenBuffer);

	// Loading Screen Animation
	VERTEX_DATA loadingAnimationData[ICON_COUNT];
	D3D11_BUFFER_DESC bd_LoadingAnimation[ICON_COUNT];
	D3D11_SUBRESOURCE_DATA sd_LoadingAnimation[ICON_COUNT];

	for (int i = 0; i < ICON_COUNT; i++)
	{

		ZeroMemory(&bd_LoadingAnimation[i], sizeof(bd_LoadingAnimation[i]));
		bd_LoadingAnimation[i].Usage = D3D11_USAGE_DEFAULT;
		bd_LoadingAnimation[i].ByteWidth = sizeof(VERTEX_3D) * 4;
		bd_LoadingAnimation[i].BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd_LoadingAnimation[i].CPUAccessFlags = 0;

		ZeroMemory(&sd_LoadingAnimation[i], sizeof(sd_LoadingAnimation[i]));
		sd_LoadingAnimation[i].pSysMem = loadingAnimationData[i].Vertex;

		CRenderer::GetDevice()->CreateBuffer(&bd_LoadingAnimation[i], &sd_LoadingAnimation[i], &m_LoadingAnimationBuffer[i]);
	}

}

void CLoadScreen::Uninit()
{

	m_LoadingScreenBuffer->Release();
	for (int i = 0; i < ICON_COUNT; i++)
	{
		m_LoadingAnimationBuffer[i]->Release();
	}
}

void CLoadScreen::Update()
{
	//excess of 1.0f to give computer extra time to load screen fully
	if (m_FadeFlag == 1 && m_FadeCount < 1.5f)
	{
		m_FadeCount += 0.05f;
	}
	
	if (m_FadeFlag == 0 && m_FadeCount > 0.0f)
	{
		m_FadeCount -= 0.05f;
	}

	//bounce up and down
	if (m_UpDown == 0 && m_AnimCount < 20.0f)
	{
		m_AnimCount += 1.0f;
		if (m_AnimCount >= 20.0f)
		{
			m_UpDown = 1;
		}
	}

	if (m_UpDown == 1 && m_AnimCount > 0.0f)
	{
		m_AnimCount -= 1.0f;
		if (m_AnimCount <= 0.0f)
		{
			m_UpDown = 0;
		}
	}
}

void CLoadScreen::Draw()
{
	//VERTEX_DATA loadingAnimationData;
	CLight::SetLightOff();

	//Change Matrix Settings to 2D
	//マトリックス設定
	CRenderer::SetWorldViewProjection2D();

	//Material Settings
	//マテリアル設定
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_FadeCount);	// Fade Alpha
	CRenderer::SetMaterial(material);

	//Primitive Topology Settings
	//プリミティブトポロジー設定
	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//==================
	// Title Draw

	//Vertex Buffer Settings
	//頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_LoadingScreenBuffer, &stride, &offset);

	//Texture Settings
	//テキスチャー設定
	CRenderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_LoadingScreenTexture);

	//Draw Polygon (4: # of vertices)
	//描画（頂点数：４）
	CRenderer::GetDeviceContext()->Draw(4, 0);

	//====================
	// Animation Draw
	//VERTEX_DATA loadingAnimationData;

	// Loading Screen Animation
	VERTEX_DATA loadingAnimationData[ICON_COUNT];
	D3D11_BUFFER_DESC bd_LoadingAnimation[ICON_COUNT];
	D3D11_SUBRESOURCE_DATA sd_LoadingAnimation[ICON_COUNT];

	for (int i = 0; i < ICON_COUNT; i++)
	{
		float offsetY = (float)i * -20.0f;

		loadingAnimationData[i].Vertex[0].Position = D3DXVECTOR3(ICON_START_X - (ICON_SIZE * i), ICON_START_Y + offsetY + m_AnimCount, 0.0f);
		loadingAnimationData[i].Vertex[0].Normal   = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		loadingAnimationData[i].Vertex[0].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		loadingAnimationData[i].Vertex[0].TexCoord = D3DXVECTOR2(0.2f + (i * 0.2f), 0.0f);

		loadingAnimationData[i].Vertex[1].Position = D3DXVECTOR3(ICON_START_X + ICON_SIZE - (ICON_SIZE * i), ICON_START_Y + offsetY + m_AnimCount, 0.0f);
		loadingAnimationData[i].Vertex[1].Normal   = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		loadingAnimationData[i].Vertex[1].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		loadingAnimationData[i].Vertex[1].TexCoord = D3DXVECTOR2(0.4f + (i * 0.2f), 0.0f);

		loadingAnimationData[i].Vertex[2].Position = D3DXVECTOR3(ICON_START_X - (ICON_SIZE * i), ICON_START_Y + ICON_SIZE + offsetY + m_AnimCount, 0.0f);
		loadingAnimationData[i].Vertex[2].Normal   = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		loadingAnimationData[i].Vertex[2].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		loadingAnimationData[i].Vertex[2].TexCoord = D3DXVECTOR2(0.2f + (i * 0.2f), 1.0f);

		loadingAnimationData[i].Vertex[3].Position = D3DXVECTOR3(ICON_START_X + ICON_SIZE - (ICON_SIZE * i), ICON_START_Y + ICON_SIZE + offsetY + m_AnimCount, 0.0f);
		loadingAnimationData[i].Vertex[3].Normal   = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		loadingAnimationData[i].Vertex[3].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		loadingAnimationData[i].Vertex[3].TexCoord = D3DXVECTOR2(0.4f + (i * 0.2f), 1.0f);

		ZeroMemory(&bd_LoadingAnimation[i], sizeof(bd_LoadingAnimation[i]));
		bd_LoadingAnimation[i].Usage = D3D11_USAGE_DEFAULT;
		bd_LoadingAnimation[i].ByteWidth = sizeof(VERTEX_3D) * 4;
		bd_LoadingAnimation[i].BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd_LoadingAnimation[i].CPUAccessFlags = 0;

		ZeroMemory(&sd_LoadingAnimation[i], sizeof(sd_LoadingAnimation[i]));
		sd_LoadingAnimation[i].pSysMem = loadingAnimationData[i].Vertex;

		CRenderer::GetDevice()->CreateBuffer(&bd_LoadingAnimation[i], &sd_LoadingAnimation[i], &m_LoadingAnimationBuffer[i]);

		stride = sizeof(VERTEX_3D);
		offset = 0;
		CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_LoadingAnimationBuffer[i], &stride, &offset);

		CRenderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_LoadingAnimationTexture);

		//Draw Polygon (4: # of vertices)
		//描画（頂点数：４）
		CRenderer::GetDeviceContext()->Draw(4, 0);
	}
}

void CLoadScreen::Load()
{
	// Loading Screen Texture
	D3DX11CreateShaderResourceViewFromFile(CRenderer::GetDevice(),
		//"Asset/Texture/AD_Loading_Screen.png",
		"Asset/Texture/AD_Loading_Screen_No_Icons.png",
		NULL,
		NULL,
		&m_LoadingScreenTexture,
		NULL);
	assert(m_LoadingScreenTexture);

	// Loading Animation Texture
	D3DX11CreateShaderResourceViewFromFile(CRenderer::GetDevice(),
		"Asset/Texture/AD_Grease_Pencil_Icons_Lineart_Brown.png",
		NULL,
		NULL,
		&m_LoadingAnimationTexture,
		NULL);
	assert(m_LoadingAnimationTexture);
}

void CLoadScreen::Unload()
{
	m_LoadingScreenTexture->Release();
	m_LoadingAnimationTexture->Release();
}