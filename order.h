/*==================================================================
DIRECTX11 éOçZçáìØ order.h
Author: Sim Luigi
Last Updated: 2020.08.27
===================================================================*/

#pragma once
#include <queue>		//queue implementation of orders

#define DIFFICULTY_START		2		// initialize difficulty level	

class COrder
{
private:

	// 2020.08.23
	// static for all variables
	// queue implementation
	static std::queue<int> m_CustomerQueue;
	static std::queue<int> m_PlayerQueue;		
	
	static int m_Index;				//current place in queue	
	static int m_OrderLength;		//current order length (increments as player progresses)

public:

	COrder()	{}
	~COrder()	{}

	static void EmptyCustomerQueue();
	static void InitCustomerQueue();
	static void InitPlayerQueue();
	static void RefreshQueues();
	static void PushDonutToPlayerQueue(int donutType);
	static void CompareQueues();
	static bool CheckCustomerQueueIfEmpty();

	static int GetIndex()			{ return m_Index; }
	static int GetOrderLength()		{ return m_OrderLength; }
	
	static void SetIndex(int index) { m_Index = index; }
	static void SetOrderLength(int orderLength) { m_OrderLength = orderLength; }

	static void Init();
	static void Update();
};