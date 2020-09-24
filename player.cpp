/*==================================================================
DIRECTX11 �O�Z���� player.cpp
Author: Sim Luigi
Last Updated: 2020.09.01

2020.08.26
-added player model (tongs)

2020.08.27
-removed bullet implementation
-implemented forward area donut pickup GetDonut()

2020.08.29
-added Load(), Unload() methods

2020.09.01
-IMPORTANT! added movement bounds.
===================================================================*/

#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "scene.h"
#include "game.h"
#include "input.h"
#include "order.h"
#include "model.h"
#include "explosion.h"
#include "donut.h"
#include "player.h"


class CModel*	CPlayer::m_PlayerModel;

void CPlayer::Init()
{
	m_Position	= D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_Rotation	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale		= D3DXVECTOR3(1.0f, 1.0f, 1.0f);
}

void CPlayer::Uninit()
{

}

// �X�V
// 2020.07.28: FPS�ݒ�
void CPlayer::Update()
{
	//�Փ˔��� Collision Detection
	CScene* scene = CManager::GetScene();

	D3DXVECTOR3 forward	= GetForward();

	// 2020.08.23
	// GetGameStartFlag
	if (CGame::GetGameStartFlag())
	{
		//2020.09.01
		// �ړ�����
		// Movement Limits
		if (m_Position.z < -18.0f)
			m_Position.z = -18.0f;
		if (m_Position.z > 18.0f)
			m_Position.z = 18.0f;
		if (m_Position.x < -18.0f)
			m_Position.x = -18.0f;
		if (m_Position.x > 18.0f)
			m_Position.x = 18.0f;

		if (CInput::GetKeyPress('A'))
		{
			m_Rotation.y -= PLAYER_SPEED;
		}
		if (CInput::GetKeyPress('D'))
		{
			m_Rotation.y += PLAYER_SPEED;
		}

		if (CInput::GetKeyPress('W'))
		{
			m_Position += forward * 0.1f;

		}
		if (CInput::GetKeyPress('S'))
		{
			m_Position -= forward * 0.1f;
		}

		//Bullet Spawn 
		//�e�̐��쏈��
		if (CInput::GetKeyTrigger(VK_SPACE))
		{
			GetDonut();
		}
	}
}

void CPlayer::Draw()
{
	//Matrix Settings
	//�}�g���b�N�X�ݒ�
	D3DXMATRIX	world, scale, rotate, translate;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);

	//���ӎ���: YawPitchRoll�̃x�N�g���̏��Ԃ�X-Y-Z����Ȃ��āAY-X-Z�ł��B 
	//YawPitchRoll: vertex order is Y-X-Z, not X-Y-Z
	D3DXMatrixRotationYawPitchRoll(&rotate, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&translate, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rotate * translate;
	CRenderer::SetWorldMatrix(&world);

	//Draw
	//���f���`��
	m_PlayerModel->Draw();
}

// 2020.08.27
// Removed Bullet, manually retrieve donut using tongs
void CPlayer::GetDonut()
{
	CScene* scene = CManager::GetScene();
	D3DXVECTOR3 forward = GetForward();

	std::vector<CDonut*> donutArray = scene->GetGameObjects<CDonut>(1);

	for (CDonut* donut : donutArray)
	{
		//�G�̈ʒu��Get		Get enemyPosition
		D3DXVECTOR3 donutPosition = donut->GetPosition();

		//�E����h�[�i�c�͈̔͂����i�v���C���[�̂�����ƑO�j
		D3DXVECTOR3 direction = m_Position + forward - donutPosition;
		float length = D3DXVec3Length(&direction);

		if (length < 1.5f)			//adjust based on enemy size		
		{
			//Explosion Effect, adjusted to appear a bit away from player (not too close)
			scene->AddGameObject<CExplosion>(1)->SetPosition(donutPosition + forward);

			//Enemy Respawn
			scene->AddGameObjectWithID<CDonut>(1, rand() % COrder::GetOrderLength())
				->SetPosition(D3DXVECTOR3(donutPosition.x, donutPosition.y, donutPosition.z + 5.0f));

			// 2020.08.17
			// Add Destroyed/Selected Donut Type to Player Queue
			scene->GetGameObject<COrder>(0)
				->PushDonutToPlayerQueue(donut->GetDonutType());

			//Enemy/Bullet cleanup
			donut->SetDestroy();		//destroy enemy flag

			return;		//�����𒆎~�i�����̃h�[�i�c���E���Ȃ����߁j	
		}
	}
}

void CPlayer::Load()
{
	// 2020.08.26
	// �g���O�̎���Ђ����猩���邽�߁A���f�����̂̈ʒu�ɃI�t�Z�b�g�ɒǉ�����
	// Added offset to model .obj file to show tong paws
	m_PlayerModel = new CModel();
	m_PlayerModel->Load("Asset\\Model\\Player_Tongs_Offset.obj");
}

void CPlayer::Unload()
{
	m_PlayerModel->Unload();
	delete m_PlayerModel;
}