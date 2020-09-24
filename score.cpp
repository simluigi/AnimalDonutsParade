/*==================================================================
DIRECTX11 三校合同 score.cpp
Author: Sim Luigi
Last Updated: 2020.08.24

This class manages the score mechanics and UI displays.

2020.08.23
-.cpp, header file created.

2020.08.27
- donuts by type, orders completed, high score migrated here.

2020.08.28
- Set UpdateHighScore() to return bool value (true if update, false if not)
===================================================================*/

#include "main.h"
#include "manager.h"
#include "scene.h"
#include "input.h"
#include "game.h"
#include "model.h"
#include "player.h"
#include "donut.h"
#include "order.h"
#include "UI_score.h"
#include "score.h"

int CScore::m_Score;
int CScore::m_HighScore;
int CScore::m_OrdersCompleted;
int CScore::m_DonutCount[DONUT_TYPE_COUNT];

void CScore::Init()
{
	// スコア、ハイスコアの初期化
	m_Score = 0;
	m_OrdersCompleted = 0;

	// ドーナツ種類ごとのカウント（リザルト用）
	for (int i = 0; i < DONUT_TYPE_COUNT; i++)
	{
		m_DonutCount[i] = 0;
	}

	// Init high score only on first play
	if (CManager::GetFirstPlay() == true)
	{
		m_HighScore = 0;
	}
}


// ハイスコア更新（比較）
// Update High Score (compare with old score)
bool CScore::UpdateHighScore(int score)
{
	if (score > m_HighScore)
	{
		m_HighScore = score;
		return true;
	}
	return false;
}