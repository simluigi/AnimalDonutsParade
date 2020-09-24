/*==================================================================
DIRECTX11 �O�Z���� explosion.cpp
Author: Sim Luigi
Last Updated: 2020.08.26

2020.08.26
-edited Explosion .png file (added variants)
2020.08.27
-modified position of explosion to appear in front of player
 (more visible)
===================================================================*/

#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "camera.h"
#include "scene.h"
#include "light.h"
#include "player.h"
#include "explosion.h"


ID3D11Buffer*					CExplosion::m_VertexBuffer = NULL;
ID3D11ShaderResourceView*		CExplosion::m_Texture = NULL;

void CExplosion::Init()
{
	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale =	 D3DXVECTOR3(1.0f, 1.0f, 1.0f);
}

void CExplosion::Uninit()
{

}

void CExplosion::Update()
{
	//Frame Counter++
	//�t���[���J�E���^�[�C���N�������g
	m_Count++;
	if (m_Count > 16)
	{
		SetDestroy();
		return;
	}
}

void CExplosion::Draw()
{
	//turn off light
	CLight::SetLightOff();

	//Animation Frame UV Calculation
	//�A�j���[�V������UV�v�Z
	float x = m_Count % 4 * (1.0f / 4);			
	float y = m_Count / 4 * (1.0f / 4);

	//Animation Basic Structure Settings
	//�A�j���[�V������{�݌v
	D3D11_MAPPED_SUBRESOURCE msr;
	CRenderer::GetDeviceContext()->Map(m_VertexBuffer, 0,				//map, unmap: DirectX9 lock, unlock
		D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

	//Animation Frame Update (UV for 16 frames)
	//�t���[���X�V�i�v�Z�AUV16�t���[���j
	vertex[0].Position		= D3DXVECTOR3(-1.0f, 1.0f, 0.0f);
	vertex[0].Normal		= D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse		= D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord		= D3DXVECTOR2(x, y);

	vertex[1].Position		= D3DXVECTOR3(1.0f, 1.0f, 0.0f);
	vertex[1].Normal		= D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse		= D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord		= D3DXVECTOR2(x + (1.0f / 4), y);

	vertex[2].Position		= D3DXVECTOR3(-1.0f, -1.0f, 0.0f);
	vertex[2].Normal		= D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse		= D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord		= D3DXVECTOR2(x, y + (1.0f / 4));

	vertex[3].Position		= D3DXVECTOR3(1.0f, -1.0f, 0.0f);
	vertex[3].Normal		= D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[3].Diffuse		= D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord		= D3DXVECTOR2(x + (1.0f / 4), y + (1.0f / 4));

	CRenderer::GetDeviceContext()->Unmap(m_VertexBuffer, 0);		//map, unmap: DirectX9 lock, unlock

	CCamera* camera = CManager::GetScene()->GetGameObject<CCamera>(0);
	D3DXMATRIX view = camera->GetViewMatrix();				//camera.h�ɒǉ�
	D3DXMATRIX invView;
	D3DXMatrixInverse(&invView, NULL, &view);				//reverse view

	//set to face camera: world matrix values
	//�J�����Ɍ����鏈��
	invView._41 = 0.0f;
	invView._42 = 0.0f;
	invView._43 = 0.0f;

	//Matrix Settings
	//�}�g���b�N�X�ݒ�
	D3DXMATRIX	world, scale, translate;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixTranslation(&translate, m_Position.x, m_Position.y, m_Position.z);
	
	//invView: face point of explosion
	//invView: �Փˈʒu�Ɍ����ď�������
	world = scale * invView * translate;
	CRenderer::SetWorldMatrix(&world);

	//Vertex Buffer Settings
	//���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	//Material Settings
	//�}�e���A���ݒ�
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	CRenderer::SetMaterial(material);

	//Texture Settings
	//�e�L�X�`���[�ݒ�
	CRenderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);

	//Primitive Topology Settings
	//�v���~�e�B�u�g�|���W�[�ݒ�
	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//Draw Polygon (4: # of vertices)
	//�`��i���_���F�S�j
	CRenderer::GetDeviceContext()->Draw(4, 0);

	CLight::SetLightOn();	//���C�g�L��
}


//2017.07.13
//Load(), Unload()
void CExplosion::Load()
{
	VERTEX_3D	vertex[4];

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));	
	bd.Usage = D3D11_USAGE_DYNAMIC;						
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;	//animation setting �@ (allow editing vertex buffer)�@���_�o�b�t�@�[��ҏW�ł���悤��

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;				

	CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);

	//�e�L�X�`���[�ǂݍ��� Read Texture
	D3DX11CreateShaderResourceViewFromFile(CRenderer::GetDevice(),
		"Asset/Texture/AD_Explosion_01.png",
		NULL,
		NULL,
		&m_Texture,
		NULL);

	assert(m_Texture);
}

void CExplosion::Unload()
{
	m_VertexBuffer->Release();
	m_Texture->Release();
}