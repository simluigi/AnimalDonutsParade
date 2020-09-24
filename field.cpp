/*==================================================================
DIRECTX11 三校合同 field.cpp
Author: Sim Luigi
Last Updated: 2020.08.26

2020.08.26
-Load(), Unload() added
-Added Walls
===================================================================*/

#include "main.h"
#include "renderer.h"
#include "field.h"

ID3D11ShaderResourceView*		CField::m_FieldTexture;
ID3D11ShaderResourceView*		CField::m_WallTexture;

void CField::Init()
{
	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale	   = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	
	VERTEX_DATA	field;

	field.Vertex[0].Position	= D3DXVECTOR3(-20.0f, 0.0f, 20.0f);
	field.Vertex[0].Normal		= D3DXVECTOR3(0.0f, 1.0f, 0.0f);				
	field.Vertex[0].Diffuse		= D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	field.Vertex[0].TexCoord	= D3DXVECTOR2(-10.0f, 10.0f);

	field.Vertex[1].Position	= D3DXVECTOR3(20.0f, 0.0f, 20.0f);
	field.Vertex[1].Normal		= D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	field.Vertex[1].Diffuse		= D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	field.Vertex[1].TexCoord	= D3DXVECTOR2(10.0f, 10.0f);

	field.Vertex[2].Position	= D3DXVECTOR3(-20.0f, 0.0f, -20.0f);
	field.Vertex[2].Normal		= D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	field.Vertex[2].Diffuse		= D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	field.Vertex[2].TexCoord	= D3DXVECTOR2(-10.0f, -10.0f);

	field.Vertex[3].Position	= D3DXVECTOR3(20.0f, 0.0f, -20.0f);
	field.Vertex[3].Normal		= D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	field.Vertex[3].Diffuse		= D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	field.Vertex[3].TexCoord	= D3DXVECTOR2(10.0f, -10.0f);

	D3D11_BUFFER_DESC bd_Field;
	ZeroMemory(&bd_Field, sizeof(bd_Field));				
	bd_Field.Usage = D3D11_USAGE_DEFAULT;
	bd_Field.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd_Field.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd_Field.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd_Field;
	ZeroMemory(&sd_Field, sizeof(sd_Field));					
	sd_Field.pSysMem = field.Vertex;

	CRenderer::GetDevice()->CreateBuffer(&bd_Field, &sd_Field, &m_FieldVertexBuffer);

	// 2020.08.26
	// Added Walls
	VERTEX_DATA wall[4];

	// Wall 0 (back)
	
	wall[0].Vertex[0].Position	= D3DXVECTOR3(-20.0f, 20.0f, 20.0f);
	wall[0].Vertex[0].Normal	= D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	wall[0].Vertex[0].Diffuse	= D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	wall[0].Vertex[0].TexCoord	= D3DXVECTOR2(-10.0f, 5.0f);

	wall[0].Vertex[1].Position	= D3DXVECTOR3(20.0f, 20.0f, 20.0f);
	wall[0].Vertex[1].Normal	= D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	wall[0].Vertex[1].Diffuse	= D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	wall[0].Vertex[1].TexCoord	= D3DXVECTOR2(10.0f, 5.0f);

	wall[0].Vertex[2].Position	= D3DXVECTOR3(-20.0f, 0.0f, 20.0f);
	wall[0].Vertex[2].Normal	= D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	wall[0].Vertex[2].Diffuse	= D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	wall[0].Vertex[2].TexCoord	= D3DXVECTOR2(-10.0f, -5.0f);

	wall[0].Vertex[3].Position	= D3DXVECTOR3(20.0f, 0.0f, 20.0f);
	wall[0].Vertex[3].Normal	= D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	wall[0].Vertex[3].Diffuse	= D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	wall[0].Vertex[3].TexCoord	= D3DXVECTOR2(10.0f, -5.0f);

	// Wall 1 (left)

	wall[1].Vertex[0].Position	= D3DXVECTOR3(-20.0f, 20.0f, -20.0f);
	wall[1].Vertex[0].Normal	= D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	wall[1].Vertex[0].Diffuse	= D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	wall[1].Vertex[0].TexCoord	= D3DXVECTOR2(-10.0f, 5.0f);

	wall[1].Vertex[1].Position	= D3DXVECTOR3(-20.0f, 20.0f, 20.0f);
	wall[1].Vertex[1].Normal	= D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	wall[1].Vertex[1].Diffuse	= D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	wall[1].Vertex[1].TexCoord	= D3DXVECTOR2(10.0f, 5.0f);

	wall[1].Vertex[2].Position	= D3DXVECTOR3(-20.0f, 0.0f, -20.0f);
	wall[1].Vertex[2].Normal	= D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	wall[1].Vertex[2].Diffuse	= D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	wall[1].Vertex[2].TexCoord	= D3DXVECTOR2(-10.0f, -5.0f);

	wall[1].Vertex[3].Position	= D3DXVECTOR3(-20.0f, 0.0f, 20.0f);
	wall[1].Vertex[3].Normal	= D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	wall[1].Vertex[3].Diffuse	= D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	wall[1].Vertex[3].TexCoord	= D3DXVECTOR2(10.0f, -5.0f);
	
	// Wall 2 (front)

	wall[2].Vertex[0].Position	= D3DXVECTOR3(20.0f, 20.0f, -20.0f);
	wall[2].Vertex[0].Normal	= D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	wall[2].Vertex[0].Diffuse	= D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	wall[2].Vertex[0].TexCoord	= D3DXVECTOR2(-10.0f, 5.0f);

	wall[2].Vertex[1].Position	= D3DXVECTOR3(-20.0f, 20.0f, -20.0f);
	wall[2].Vertex[1].Normal	= D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	wall[2].Vertex[1].Diffuse	= D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	wall[2].Vertex[1].TexCoord	= D3DXVECTOR2(10.0f, 5.0f);

	wall[2].Vertex[2].Position	= D3DXVECTOR3(20.0f, 0.0f, -20.0f);
	wall[2].Vertex[2].Normal	= D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	wall[2].Vertex[2].Diffuse	= D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	wall[2].Vertex[2].TexCoord	= D3DXVECTOR2(-10.0f, -5.0f);

	wall[2].Vertex[3].Position	= D3DXVECTOR3(-20.0f, 0.0f, -20.0f);
	wall[2].Vertex[3].Normal	= D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	wall[2].Vertex[3].Diffuse	= D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	wall[2].Vertex[3].TexCoord	= D3DXVECTOR2(10.0f, -5.0f);

	// Wall 3 (right)

	wall[3].Vertex[0].Position	= D3DXVECTOR3(20.0f, 20.0f, 20.0f);
	wall[3].Vertex[0].Normal	= D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	wall[3].Vertex[0].Diffuse	= D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	wall[3].Vertex[0].TexCoord	= D3DXVECTOR2(-10.0f, 5.0f);

	wall[3].Vertex[1].Position	= D3DXVECTOR3(20.0f, 20.0f, -20.0f);
	wall[3].Vertex[1].Normal	= D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	wall[3].Vertex[1].Diffuse	= D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	wall[3].Vertex[1].TexCoord	= D3DXVECTOR2(10.0f, 5.0f);

	wall[3].Vertex[2].Position	= D3DXVECTOR3(20.0f, 0.0f, 20.0f);
	wall[3].Vertex[2].Normal	= D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	wall[3].Vertex[2].Diffuse	= D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	wall[3].Vertex[2].TexCoord	= D3DXVECTOR2(-10.0f, -5.0f);

	wall[3].Vertex[3].Position	= D3DXVECTOR3(20.0f, 0.0f, -20.0f);
	wall[3].Vertex[3].Normal	= D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	wall[3].Vertex[3].Diffuse	= D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	wall[3].Vertex[3].TexCoord	= D3DXVECTOR2(10.0f, -5.0f);

	D3D11_BUFFER_DESC bd_Wall[4];
	D3D11_SUBRESOURCE_DATA sd_Wall[4];

	for (int i = 0; i < 4; i++)
	{
		ZeroMemory(&bd_Wall[i], sizeof(bd_Wall[i]));
		bd_Wall[i].Usage = D3D11_USAGE_DEFAULT;
		bd_Wall[i].ByteWidth = sizeof(VERTEX_3D) * 4;
		bd_Wall[i].BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd_Wall[i].CPUAccessFlags = 0;

		ZeroMemory(&sd_Wall[i], sizeof(sd_Wall[i]));
		sd_Wall[i].pSysMem = wall[i].Vertex;

		CRenderer::GetDevice()->CreateBuffer(&bd_Wall[i], &sd_Wall[i], &m_WallVertexBuffer[i]);
	}
}

void CField::Uninit()
{
	m_FieldVertexBuffer->Release();
	for (int i = 0; i < 4; i++)
	{
		m_WallVertexBuffer[i]->Release();
	}
}

void CField::Update()
{

}

void CField::Draw()
{
	D3DXMATRIX	world, scale, rotate, translate;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rotate, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&translate, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rotate * translate;
	CRenderer::SetWorldMatrix( &world);

	//Material Settings
	//マテリアル設定
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	CRenderer::SetMaterial(material);

	//Primitive Topology Settings	
	//プリミティブトポロジー設定
	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// Draw Field
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_FieldVertexBuffer, &stride, &offset);
	CRenderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_FieldTexture);
	CRenderer::GetDeviceContext()->Draw(4, 0);

	// Draw Walls
	CRenderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_WallTexture);

	for (int i = 0; i < 4; i++)
	{
		stride = sizeof(VERTEX_3D);
		offset = 0;
		CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_WallVertexBuffer[i], &stride, &offset);
		CRenderer::GetDeviceContext()->Draw(4, 0);
	}
}

void CField::Load()
{
	D3DX11CreateShaderResourceViewFromFile(CRenderer::GetDevice(),
		"Asset/Texture/AD_Floor_Tile.png",
		NULL,
		NULL,
		&m_FieldTexture,
		NULL);
	assert(m_FieldTexture);

	D3DX11CreateShaderResourceViewFromFile(CRenderer::GetDevice(),
		"Asset/Texture/AD_Wall_Tile.png",
		NULL,
		NULL,
		&m_WallTexture,
		NULL);
	assert(m_WallTexture);
}

void CField::Unload()
{
	m_FieldTexture->Release();
	m_WallTexture->Release();
}