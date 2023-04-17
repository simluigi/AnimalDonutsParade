/*==================================================================
DIRECTX11 三校合同 order.cpp
Author: Sim Luigi
Last Updated: 2020.08.27

This class manages the customer/player donut order parameters
as well as other ingame mechanics.  It also manages the UI display
for the customer/donut order arrays.

2020.08.17
-cpp, header file created.

2020.08.18
-Update(): RefreshQueues() on key trigger 
(also workaround for starting the game)

2020.08.23
-changed member variables to static to allow 
function calls in game.cpp

2020.08.27
-migrated score elements to score.cpp
-added CheckCustomerQueueIfEmpty (to force initialization on game start)

2020.08.28
-added EmptyCustomerQueue() to facilitate initiation on repeat plays

2020.08.30
-added sound effects.
===================================================================*/

#include "main.h"
#include "manager.h"
#include "scene.h"
#include "input.h"
#include "sound.h"
#include "game.h"
#include "model.h"
#include "player.h"
#include "donut.h"
#include "UI_order.h"
#include "score.h"
#include "order.h"

#define DIFFICULTY_THRESHOLD	3		// number of completed orders before level up

// 静的メンバー変数の再定義
// static member variable redeclaration
int COrder::m_Index;
int COrder::m_OrderLength;
std::queue<int> COrder::m_CustomerQueue;
std::queue<int> COrder::m_PlayerQueue;

void COrder::EmptyCustomerQueue()
{
	// pop until empty
	while (!m_CustomerQueue.empty())
	{
		m_CustomerQueue.pop();
	}
}

// 注文キューの初期化処理
// Initialize customer queue pattern
void COrder::InitCustomerQueue()
{
	int donutType;
	CScene* scene = CManager::GetScene();

	EmptyCustomerQueue();

	for ( int i = 0; i < m_OrderLength; i++ )
	{
		donutType = rand() % m_OrderLength;		// more donut varieties introduced the further into the game
		m_CustomerQueue.push(donutType);

		//2D Object (Layer 2), donutType, CustomerQueue (value 0)
		scene->AddGameObjectWithTwoArguments<CUIOrder>(2, donutType, 0);
		m_Index++;
	}
	// reset to 0 for player use
	m_Index = 0;
}

// プレイヤーキューの初期化処理
// Initialize player queue pattern
void COrder::InitPlayerQueue()
{
	// pop until empty
	while ( !m_PlayerQueue.empty() )
	{
		m_PlayerQueue.pop();
	}
}

// 全てのキューの初期化、アイコン処分処理
// Initialize all queues (start of game, after an order is completed)
// Includes cleaning up previous CUIOrder display
void COrder::RefreshQueues()
{
	// prepare to delete all existing icons; access CScene
	CScene* scene = CManager::GetScene();
	
	// vector of all CUIOrder objects (player and customer queues) -> setDestroy
	std::vector<CUIOrder*> UIOrderDestroy = scene->GetGameObjects<CUIOrder>(2);
	for (CUIOrder* UIOrder : UIOrderDestroy)
	{
		UIOrder->SetDestroy();
	}

	// insert POOF animation here
	m_Index = 0;
	InitPlayerQueue();
	InitCustomerQueue();
}

// 2020.08.18
// Change implementation - push until m_OrderLength, then compare.
// Score if completed, no score if failed, but refresh both queues regardless
void COrder::PushDonutToPlayerQueue(int donutType)
{
	//for adding UI Icon
	CScene* scene = CManager::GetScene();

	// push passed donut type into player queue
	m_PlayerQueue.push(donutType);

	// base score for taking one donut
	CScore::AddScore(SCORE_PER_DONUT);

	// 2020.08.27
	// donut tally per type for display in result scene
	CScore::AddDonutCount(donutType);

	// Add Icon to Player Queue (value 1)
	scene->AddGameObjectWithTwoArguments<CUIOrder>(2, donutType, 1);
	m_Index++;

	// Compare queues when length is maxed, only triggers with player queue
	if (m_Index == m_OrderLength)
	{
		CompareQueues();
	}
	else
	{
		// only plays if CompareQueues() is not called to prevent overlapping sounds
		CSound::PlaySfxGetDonut();		
	}
}

void COrder::CompareQueues()
{
	//for adding donuts on level up
	CScene* scene = CManager::GetScene();

	// if contents of queues are the same, resolve scoring and reinitialize both queues
	if (m_PlayerQueue == m_CustomerQueue)
	{
		// scoring process here
		CScore::AddScore(m_OrderLength * SCORE_BASE_MULTIPLIER);

		// Completed Orders Increment (used to check for difficulty scaling)
		//m_OrdersCompleted++;
		CScore::AddOrdersCompleted();

		// 2020.08.30
		// Play successful combo sound
		CSound::PlaySfxCombo();

		// if score threshold passes X, increment m_OrderLength (higher difficulty)
		if (CScore::GetOrdersCompleted() % DIFFICULTY_THRESHOLD == 0 && m_OrderLength < DONUT_TYPE_COUNT)
		{
			// Add two donuts of the new type to the scene
			scene->AddGameObjectWithID<CDonut>(1, m_OrderLength)->
				SetPosition(D3DXVECTOR3( (float)(m_OrderLength) * 3.0f, 1.0f, 13.0f));
			scene->AddGameObjectWithID<CDonut>(1, m_OrderLength)->
				SetPosition(D3DXVECTOR3( (float)(m_OrderLength) * -3.0f, 1.0f, 13.0f));

			// Add two additional donuts of random type (including the new type) behind the two new donuts
			scene->AddGameObjectWithID<CDonut>(1, rand () % m_OrderLength)->
				SetPosition(D3DXVECTOR3( (float)(m_OrderLength) * 3.0f, 1.0f, 16.0f));
			scene->AddGameObjectWithID<CDonut>(1, rand () % m_OrderLength)->
				SetPosition(D3DXVECTOR3( (float)(m_OrderLength) * -3.0f, 1.0f, 16.0f));

			// Extend Order Length and advance difficulty one stage
			m_OrderLength++;
			CGame::IncreaseDifficulty();
		}
		//
	}
	else // not matching
	{
		// 2020.08.30
		CSound::PlaySfxMiss();
	}

	//regardless, reset both customer and player queues, and delete CUIOrder Icons
	// Add animation + delay before deleting CUIOrder objects, otherwise final icon will not be displayed 
	 RefreshQueues();
}

// 2020.08.27
// Check if customer queue is empty, return true if empty
bool COrder::CheckCustomerQueueIfEmpty()
{
	if (m_CustomerQueue.empty())
		return true;
	return false;
}

void COrder::Init()
{
	m_OrderLength = DIFFICULTY_START;		//starting difficulty
	m_Index = 0;							//initialize queue index
}

void COrder::Update()
{

}
