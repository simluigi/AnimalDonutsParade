/*==================================================================
DIRECTX11 �O�Z���� camera.cpp
Author: Sim Luigi
Last Updated: 2020.08.26

2020.08.26
-FPS mode implemented.
===================================================================*/

//���Ԃ͑厖�ł��I(�Ԉ������R���p�C���G���[)
//Order is VERY IMPORTANT (otherwise will result in compile error)
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "scene.h"
#include "player.h"
#include "model.h"
#include "camera.h"

D3DXVECTOR3		CCamera::m_Target;				// Camera�̒��ӎ��_	Camera's viewpoint
D3DXVECTOR3		CCamera::m_Position;			// override game_object.h�@(now static variable)
D3DXVECTOR3		CCamera::m_VecDir;
D3DXVECTOR3		CCamera::m_VecFront;
D3DXVECTOR3		CCamera::m_VecRight;

void CCamera::Init()
{
	// 2020.08.26
	// FPS�������ݒ�
	// FPS Implementation Initialization
	m_VecDir	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_VecFront	= D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	m_VecRight	= D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	m_Position	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Target	= m_Position + m_VecFront;
}

void CCamera::Uninit()
{

}

void CCamera::Update()
{
	// 2020.08.26
	// �X�V�FFPS�r���[�ݒ�
	// Changed to FPS View

	CPlayer* player = CManager :: GetScene()->GetGameObject<CPlayer>(1);

	// �ʒu�����iY���j
	// Slight Camera Position Adjust (Y Axis)
	m_Position = player->GetPosition() + D3DXVECTOR3(0.0, 0.5, 0.0f);
	m_VecFront = player->GetForward();
	m_VecRight = player->GetRight();

	D3DXVec3Normalize(&m_VecDir, &m_VecDir);
	D3DXVec3Normalize(&m_VecFront, &m_VecFront);
	D3DXVec3Normalize(&m_VecRight, &m_VecRight);

	m_Position += m_VecDir * PLAYER_SPEED;
	m_Target = m_Position + m_VecFront;
}

void CCamera::Draw()
{
	//�}�g���b�N�X�ݒ�	Matrix Setup
	//viewMatrix�������o�[�ϐ�m_ViewMatrix�ɕύX
	D3DXMatrixLookAtLH(&m_ViewMatrix, &m_Position, &m_Target, &D3DXVECTOR3(0.0f, 1.0f, 0.0f));

	CRenderer::SetViewMatrix(&m_ViewMatrix);
	//�v���W�F�N�g�V�����ݒ� Projection Setup
	//���e�@�Ƃ�����:	Projection
	D3DXMatrixPerspectiveFovLH(&m_ProjectionMatrix, 1.0f,			// 1.0f: radian (zoom)
		(float)SCREEN_WIDTH / SCREEN_HEIGHT, 0.1f, 1000.0f);		// 0.1 near clip, 1000.0 max clip
	CRenderer::SetProjectionMatrix(&m_ProjectionMatrix);
}







