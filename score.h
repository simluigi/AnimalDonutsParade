/*==================================================================
DIRECTX11 éOçZçáìØ score.h
Author: Sim Luigi
Last Updated: 2020.08.27
===================================================================*/

#pragma once
#include "donut.h"

#define SCORE_PER_DONUT			5		// points earned per individual donut
#define SCORE_BASE_MULTIPLIER	100		// base score per donut x chain

class CScore
{
private:

	// 2020.08.24
	// score variables
	static int m_Score;
	static int m_HighScore;
	static int m_OrdersCompleted;

	// 2020.08.27
	// Tally donut count for display in result scene
	static int m_DonutCount[DONUT_TYPE_COUNT];

public:

	CScore() {}
	~CScore() {}

	static int  GetScore()						{ return m_Score; }
	static int	GetHighScore()					{ return m_HighScore; }
	static int  GetOrdersCompleted()			{ return m_OrdersCompleted; }
	static int	GetDonutCount(int donutType)	{ return m_DonutCount[donutType]; }
	
	static void AddScore(int points)			{ m_Score += points; }
	static void AddOrdersCompleted()			{ m_OrdersCompleted++; }
	static void AddDonutCount(int donutType)	{ m_DonutCount[donutType]++; }

	static bool UpdateHighScore(int score);

	static void Init();
};