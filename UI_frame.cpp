/*==================================================================
DIRECTX11 三校合同 UI_frame.cpp
Author: Sim Luigi
Last Updated: 2020.08.29

UI Top bar base display.

2020.08.29
-assert() added to texture load methods.
-cleaned up code.
===================================================================*/
#include "main.h"
#include "renderer.h"
#include "light.h"
#include "game.h"
#include "UI_frame.h"

#define TEXTURE_HEIGHT		  (102.0f)
#define ANIM_TEXTURE_WIDTH	  (145.0f)
#define ANIM_TEXTURE_OFFSET_X (0.0f)

ID3D11ShaderResourceView*	CUIFrame::m_FrameTexture;
ID3D11ShaderResourceView*	CUIFrame::m_FrameAnimTexture;

void CUIFrame::Init()
{
	VERTEX_DATA	frameData, frameAnimData;
	m_AnimCount = 0.0f;

	// Frame
	frameData.Vertex[0].Position	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	frameData.Vertex[0].Normal		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);				
	frameData.Vertex[0].Diffuse		= D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	frameData.Vertex[0].TexCoord	= D3DXVECTOR2(0.0f, 0.0f);

	frameData.Vertex[1].Position	= D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	frameData.Vertex[1].Normal		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	frameData.Vertex[1].Diffuse		= D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	frameData.Vertex[1].TexCoord	= D3DXVECTOR2(1.0f, 0.0f);

	frameData.Vertex[2].Position	= D3DXVECTOR3(0.0f, TEXTURE_HEIGHT, 0.0f);
	frameData.Vertex[2].Normal		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	frameData.Vertex[2].Diffuse		= D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	frameData.Vertex[2].TexCoord	= D3DXVECTOR2(0.0f, 1.0f);

	frameData.Vertex[3].Position	= D3DXVECTOR3(SCREEN_WIDTH, TEXTURE_HEIGHT, 0.0f);
	frameData.Vertex[3].Normal		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	frameData.Vertex[3].Diffuse		= D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	frameData.Vertex[3].TexCoord	= D3DXVECTOR2(1.0f, 1.0f);

	D3D11_BUFFER_DESC bd_Frame;
	ZeroMemory(&bd_Frame, sizeof(bd_Frame));				//clears memory for bd
	bd_Frame.Usage = D3D11_USAGE_DEFAULT;
	bd_Frame.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd_Frame.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd_Frame.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd_Frame;
	ZeroMemory(&sd_Frame, sizeof(sd_Frame));					//clears memory for sd
	sd_Frame.pSysMem = frameData.Vertex;

	CRenderer::GetDevice()->CreateBuffer(&bd_Frame, &sd_Frame, &m_FrameVertexBuffer);
}

void CUIFrame::Uninit()
{
	m_FrameVertexBuffer->Release();
	m_FrameAnimVertexBuffer->Release();
}

void CUIFrame::Update()
{
	// アニメーション再描画・延長設定
	// animation repeat, delay settings 
	if (m_AnimCount > 3000.0f)
	{
		m_AnimCount = 0.0f;
	}
	m_AnimCount += 30.0f;
}

void CUIFrame::Draw()
{

	//=========================================
	// 共通設定
	// Common Settings
	
	CLight::SetLightOff();
	CRenderer::SetWorldViewProjection2D();
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	CRenderer::SetMaterial(material);
	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;

	//=====================================
	// ベースフレーム描画 (アップデートなし）
	// Base Frame (no update)

	CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_FrameVertexBuffer, &stride, &offset);
	CRenderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_FrameTexture);
	CRenderer::GetDeviceContext()->Draw(4, 0);

	//=====================================
	// フレームアニメーション描画 
	// Animation Frame settings

	VERTEX_DATA frameAnimData;
	
	// m_AnimCountが範囲内に入っている限り描画する
	// Draw only if within animation range
	if (m_AnimCount < 1120.0f && m_AnimCount > 0.0f)
	{
		frameAnimData.Vertex[0].Position = D3DXVECTOR3(m_AnimCount + ANIM_TEXTURE_OFFSET_X, 0.0f, 0.0f);
		frameAnimData.Vertex[0].Normal	 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		frameAnimData.Vertex[0].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		frameAnimData.Vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

		frameAnimData.Vertex[1].Position = D3DXVECTOR3(m_AnimCount + ANIM_TEXTURE_OFFSET_X + ANIM_TEXTURE_WIDTH, 0.0f, 0.0f);
		frameAnimData.Vertex[1].Normal	 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		frameAnimData.Vertex[1].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		frameAnimData.Vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);

		frameAnimData.Vertex[2].Position = D3DXVECTOR3(m_AnimCount + ANIM_TEXTURE_OFFSET_X, TEXTURE_HEIGHT, 0.0f);
		frameAnimData.Vertex[2].Normal	 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		frameAnimData.Vertex[2].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		frameAnimData.Vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);

		frameAnimData.Vertex[3].Position = D3DXVECTOR3(m_AnimCount + ANIM_TEXTURE_OFFSET_X + ANIM_TEXTURE_WIDTH, TEXTURE_HEIGHT, 0.0f);
		frameAnimData.Vertex[3].Normal	 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		frameAnimData.Vertex[3].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		frameAnimData.Vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);

		D3D11_BUFFER_DESC bd_Anim;
		ZeroMemory(&bd_Anim, sizeof(bd_Anim));				//clears memory for bd
		bd_Anim.Usage = D3D11_USAGE_DEFAULT;
		bd_Anim.ByteWidth = sizeof(VERTEX_3D) * 4;
		bd_Anim.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd_Anim.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd_Anim;
		ZeroMemory(&sd_Anim, sizeof(sd_Anim));					//clears memory for sd
		sd_Anim.pSysMem = frameAnimData.Vertex;

		CRenderer::GetDevice()->CreateBuffer(&bd_Anim, &sd_Anim, &m_FrameAnimVertexBuffer);
		CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_FrameAnimVertexBuffer, &stride, &offset);
		CRenderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_FrameAnimTexture);
		CRenderer::GetDeviceContext()->Draw(4, 0);
	}

	D3DXMATRIX world;							// 3Dワールドマトリックス設定に戻る
	CRenderer::SetWorldMatrix(&world);	
	CLight::SetLightOn();						// ライト有効
}

void CUIFrame::Load()
{
	D3DX11CreateShaderResourceViewFromFile(CRenderer::GetDevice(),
		"Asset/Texture/AD_UI_Frame_720_Cropped.png",
		NULL,
		NULL,
		&m_FrameTexture,
		NULL);
	assert(m_FrameTexture);

	D3DX11CreateShaderResourceViewFromFile(CRenderer::GetDevice(),
		"Asset/Texture/AD_UI_Frame_Animation.png",
		NULL,
		NULL,
		&m_FrameAnimTexture,
		NULL);
	assert(m_FrameAnimTexture);
}

void CUIFrame::Unload()
{
	m_FrameTexture->Release();
	m_FrameAnimTexture->Release();
}
