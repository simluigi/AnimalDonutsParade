/*==================================================================
DIRECTX11 三校合同 donut.cpp
Author: Sim Luigi
Last Updated: 2020.08.24
===================================================================*/

#pragma once
#include "model.h"
#include "game_object.h"


// ドーナツの種類
// number of donut types
#define DONUT_TYPE_COUNT 5		

//継承　inheritance from CGameObject
//Donut: Base Class for all donut type child classes
class CDonut : public CGameObject
{

private:
	int m_DonutType;	//donut type ドーナツの種類

protected:
	//2020.08.13
	//set to protected so it can be accessed by child class
	//static class CModel* m_Model;
	static class CModel* m_Model[DONUT_TYPE_COUNT];

public:

	CDonut() {}			//constructor	コンストラクタ
	~CDonut() {}		//destructor	デストラクタ

	int  GetDonutType() { return m_DonutType; }
	void SetDonutType(int n) { m_DonutType = n; }
		
	static void Load();
	static void Unload();

	void Init(int donutType);
	void Uninit();
	void Update();
	void Draw();
};