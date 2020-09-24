/*==================================================================
DIRECTX11 三校合同 game_object.h
Author: Sim Luigi
Last Updated: 2020.08.13

This class handles all in-game objects.
===================================================================*/

#pragma once
#include "manager.h"

class CGameObject
{
protected:
	bool						m_Destroy = false;		//破壊フラッグ

	D3DXVECTOR3	m_Position;
	D3DXVECTOR3	m_Rotation;
	D3DXVECTOR3	m_Scale;

public:
	CGameObject() {}				//コンストラクタ		Constructor (does not require virtual tag: doing so results in an error)
	virtual ~CGameObject() {}		//	デストラクタ		Destructor (requires virtual tag since prior initialized functions were virtual functions)
	 
	virtual void Init() { /*code*/ };		//仮想関数			Virtual Function (can include code in method)
	virtual void Uninit() = 0;				//純粋仮想関数		Pure Virtual Function (initialized as doing nothing, hence = 0)
	virtual void Update() = 0;
	virtual void Draw() = 0;

	// Get, Set Position/Rotation/Scale
	D3DXVECTOR3 GetPosition() { return m_Position; }
	D3DXVECTOR3 GetRotation() { return m_Rotation; }
	D3DXVECTOR3 GetScale() { return m_Scale; }

	void SetPosition(D3DXVECTOR3 Position) { m_Position = Position; }
	void SetRotation(D3DXVECTOR3 Rotation) { m_Rotation = Rotation; }
	void SetScale(D3DXVECTOR3 Scale) { m_Scale = Scale; }

	// 処分予約処理（まだ処分されない、処分フラッグだけ）
	// SetDestroy: Flag for removal
	void SetDestroy() { m_Destroy = true; }

	// 実際に処分する関数
	// Destroy: Actual removal process 
	bool Destroy()
	{
		if (m_Destroy == true)
		{
			Uninit();			//自分自身のUninit
			delete this;		//自分自身メモリ上から解放 delete from memory
			return true;
		}
		else
		{
			return false;
		}
	}

	// 2020.07.17
	// Added GetForward Function
	// in Unity:: TransformForward function
	D3DXVECTOR3 GetForward()
	{
		D3DXMATRIX rotation;
		D3DXMatrixRotationYawPitchRoll
		(&rotation, m_Rotation.y, m_Rotation.x, m_Rotation.z);

		// D3DXMATRIX contents (DirectX11, OpenGL)
		// OpenGL: verticals reversed!
		//	11		12		13		14		(11-13: RIGHT, X Vectors)
		//	21		22		23		24		(21-23: UP, Y Vectors )
		//	31		32		33		34		(31-33: FORWARD, Z Vectors)
		//	41		42		43		44		(41-44: Position, unnecessary during Billboard projection)

		// D3DXVECTOR3 forward;
		// forward.x = rotation._31;
		// forward.y = rotation._32;
		// forward.z = rotation._33;

		// 31, 32, 33: D3DXMATRIX's  Z vectors (31, 32, 33)
		D3DXVECTOR3 forward = { rotation._31, rotation._32, rotation._33 };
		return forward;
	}

	D3DXVECTOR3 GetRight()
	{
		D3DXMATRIX rotation;
		D3DXMatrixRotationYawPitchRoll
		(&rotation, m_Rotation.y, m_Rotation.x, m_Rotation.z);

		// 11, 12, 13: D3DXMATRIX's  X vectors (11, 12, 13)
		D3DXVECTOR3 right = { rotation._11, rotation._12, rotation._13 };
		return right;
	}

	D3DXVECTOR3 GetUp()
	{
		D3DXMATRIX rotation;
		D3DXMatrixRotationYawPitchRoll
		(&rotation, m_Rotation.y, m_Rotation.x, m_Rotation.z);

		// 11, 12, 13: D3DXMATRIX's  Y vectors (21, 22, 23)
		D3DXVECTOR3 up = { rotation._21, rotation._22, rotation._23 };
		return up;
	}

};