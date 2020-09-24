/*==================================================================
DIRECTX11 三校合同 camera.cpp
Author: Sim Luigi
Last Updated: 2020.08.26

2020.08.26
-FPS mode implemented.
===================================================================*/

//順番は大事です！(間違ったらコンパイルエラー)
//Order is VERY IMPORTANT (otherwise will result in compile error)
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "scene.h"
#include "player.h"
#include "model.h"
#include "camera.h"

D3DXVECTOR3		CCamera::m_Target;				// Cameraの注意視点	Camera's viewpoint
D3DXVECTOR3		CCamera::m_Position;			// override game_object.h　(now static variable)
D3DXVECTOR3		CCamera::m_VecDir;
D3DXVECTOR3		CCamera::m_VecFront;
D3DXVECTOR3		CCamera::m_VecRight;

void CCamera::Init()
{
	// 2020.08.26
	// FPS初期か設定
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
	// 更新：FPSビュー設定
	// Changed to FPS View

	CPlayer* player = CManager :: GetScene()->GetGameObject<CPlayer>(1);

	// 位置調整（Y軸）
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
	//マトリックス設定	Matrix Setup
	//viewMatrixをメンバー変数m_ViewMatrixに変更
	D3DXMatrixLookAtLH(&m_ViewMatrix, &m_Position, &m_Target, &D3DXVECTOR3(0.0f, 1.0f, 0.0f));

	CRenderer::SetViewMatrix(&m_ViewMatrix);
	//プロジェクトション設定 Projection Setup
	//投影　とうえい:	Projection
	D3DXMatrixPerspectiveFovLH(&m_ProjectionMatrix, 1.0f,			// 1.0f: radian (zoom)
		(float)SCREEN_WIDTH / SCREEN_HEIGHT, 0.1f, 1000.0f);		// 0.1 near clip, 1000.0 max clip
	CRenderer::SetProjectionMatrix(&m_ProjectionMatrix);
}







