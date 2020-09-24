/*==================================================================
DIRECTX11 三校合同 UI_order.h
Author: Sim Luigi
Last Updated: 2020.08.17

UI Display for order class.

2020.08.17
-cpp, header file created.
2020.08.18
-instead of one texture per icon, 
created a UV map (1250x250px) for all donuts.
250x250 per donut, 5 donuts
===================================================================*/

#pragma once
#include "game_object.h"

class CUIOrder : public CGameObject
{

private:

	ID3D11Buffer*						m_VertexBuffer;			//non-static; each instance has its own buffer

	//replace individual textures with UV map containing all icons, 
	//saving load time and removing conditionals from Draw()
	static ID3D11ShaderResourceView*	m_DonutIconUVMap;		

	int m_DonutType;					// for drawing, to match donut type
	int m_Index;						// current position in queue
	int m_QueueType;					// 0: CustomerQueue, 1: PlayerQueue 


public:

	CUIOrder() {}		//コンストラクタ		Constructor
	~CUIOrder() {}		//デストラクタ			Destructor

	int  GetQueueType() { return m_QueueType; }
	void SetQueueType(int n) { m_QueueType = n; }

	static void Load();
	static void Unload();

	void Init(int donutType, int queueType);
	void Uninit();
	void Update();
	void Draw();

};