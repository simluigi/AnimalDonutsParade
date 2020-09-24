/*==================================================================
DIRECTX11 �O�Z���� score.cpp
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
	// �X�R�A�A�n�C�X�R�A�̏�����
	m_Score = 0;
	m_OrdersCompleted = 0;

	// �h�[�i�c��ނ��Ƃ̃J�E���g�i���U���g�p�j
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


// �n�C�X�R�A�X�V�i��r�j
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