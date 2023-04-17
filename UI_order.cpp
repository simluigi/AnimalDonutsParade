/*==================================================================
DIRECTX11 三校合同 UI_order.cpp
Author: Sim Luigi
Last Updated: 2020.08.17

UI Display for order class.

2020.08.17
-cpp, header file created.
2020.08.18
-instead of one texture per icon,
created a UV map (250x250px per icon) for all donuts.
2020.08.29
-cleaned up code.

===================================================================*/

#include "main.h"
#include "renderer.h"
#include "light.h"
#include "scene.h"
#include "donut.h"
#include "order.h"
#include "UI_order.h"

// UV計算用
// for UV coordinate calculation
#define UI_ORDER_BOX_SIZE  (80.0f)		// Each donut icon's size
#define UI_ORDER_UV_SLICE  (0.2f)		// 250/1250 = 0.2	

//static variables
ID3D11ShaderResourceView*	CUIOrder::m_DonutIconUVMap = NULL;		//1250x250 UV Map

void CUIOrder::Init(int donutType, int queueType)
{
	// Icon type and position based on passed parameters
	m_DonutType = donutType;
	m_QueueType = queueType;	//customer(type 0) above, player (type 1) below

	//for getting m_Index of ingame <COrder>
	CScene* scene = CManager::GetScene();
	m_Index = scene->GetGameObject<COrder>(0)->GetIndex();

	// position/UV offset
	float posOffsetX = (float) 85.0f + m_Index * UI_ORDER_BOX_SIZE;						// 60.0f: indent 
	float posOffsetY = (float) -5.0f + (m_QueueType) * UI_ORDER_BOX_SIZE / 1.8f;		// 3.0f: indent	
	float UVOffsetX	 = (float) (m_DonutType) * UI_ORDER_UV_SLICE;

	VERTEX_3D	vertex[4];

	vertex[0].Position	= D3DXVECTOR3(posOffsetX, posOffsetY, 0.0f);
	vertex[0].Normal	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);			
	vertex[0].Diffuse	= D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord	= D3DXVECTOR2(UVOffsetX, 0.0f);

	vertex[1].Position	= D3DXVECTOR3(posOffsetX + UI_ORDER_BOX_SIZE, posOffsetY, 0.0f);
	vertex[1].Normal	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[1].Diffuse	= D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord	= D3DXVECTOR2(UVOffsetX + UI_ORDER_UV_SLICE, 0.0f);

	vertex[2].Position	= D3DXVECTOR3(posOffsetX, posOffsetY + UI_ORDER_BOX_SIZE, 0.0f);
	vertex[2].Normal	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[2].Diffuse	= D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord	= D3DXVECTOR2(UVOffsetX, 1.0f);

	vertex[3].Position	= D3DXVECTOR3(posOffsetX + UI_ORDER_BOX_SIZE, posOffsetY + UI_ORDER_BOX_SIZE, 0.0f);
	vertex[3].Normal	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[3].Diffuse	= D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord	= D3DXVECTOR2(UVOffsetX + UI_ORDER_UV_SLICE, 1.0f);

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));				//clears memory for bd
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));				//clears memory for sd
	sd.pSysMem = vertex;

	CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);
}

void CUIOrder::Uninit()
{
	m_VertexBuffer->Release();
}

void CUIOrder::Update()
{

}

void CUIOrder::Draw()
{
	CLight::SetLightOff();						// ライト無効
	CRenderer::SetWorldViewProjection2D();		// 2Dプロジェクションワールド設定
	
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	
	CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	CRenderer::SetMaterial(material);
	
	CRenderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_DonutIconUVMap);
	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	CRenderer::GetDeviceContext()->Draw(4, 0);

	D3DXMATRIX world;						// 3Dワールドマトリックス設定に戻る
	CRenderer::SetWorldMatrix(&world);
	CLight::SetLightOn();					// ライト有効
}

void CUIOrder::Load()
{
	D3DX11CreateShaderResourceViewFromFile(CRenderer::GetDevice(),
		"Asset/Texture/AD_Grease_Pencil_Icons_1250x250.png",
		NULL,
		NULL,
		&m_DonutIconUVMap,
		NULL);
	assert(m_DonutIconUVMap);
}

void CUIOrder::Unload()
{
	m_DonutIconUVMap->Release();
}
