/*==================================================================
DIRECTX11 �O�Z���� camera.h
Author: Sim Luigi
Last Updated: 2020.08.26
===================================================================*/

#pragma once
#include "game_object.h"

class CCamera : public CGameObject
{
private:

	//m_Position etc inherited from CGameObject
	static D3DXVECTOR3		m_Target;				// Camera�̒��ӎ��_	Camera's viewpoint
	static D3DXVECTOR3		m_Position;				// override game_object.h
	static D3DXVECTOR3		m_VecDir;
	static D3DXVECTOR3		m_VecFront;
	static D3DXVECTOR3		m_VecRight;

	D3DXMATRIX		m_ViewMatrix;
	D3DXMATRIX		m_ProjectionMatrix;

public:

	CCamera() {}			//�R���X�g���N�^		Constructor
	~CCamera() {}			//�f�X�g���N�^			Destructor

	static D3DXVECTOR3 GetPosition() { return m_Position; }
	static D3DXVECTOR3 GetVecFront() { return m_VecFront; }

	// �ǉ��֐��i�r���{�[�h�E�A�j���[�V�����p�j
	// For billboard (explosion.cpp)
	D3DXMATRIX GetViewMatrix() { return m_ViewMatrix; }

	void Init();
	void Uninit();
	void Update();
	void Draw();

};