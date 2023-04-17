/*==================================================================
DIRECTX11 éOçZçáìØ game.h
Author: Sim Luigi
Last Updated: 2020.08.29

2020.08.29
-renamed DifficultyUP() to IncreaseDifficulty()
===================================================================*/

#pragma once
#include "scene.h"

class CGame : public CScene
{
private:

	bool			m_ExitFlag;				//if exiting scene

	static bool		m_GameStartFlag;		// GameStart flag
	static float	m_Time;					// game Timer
	static float	m_Countdown;			// countdown before GameStart is active
	static float	m_TransitionOffset;		// transition time between TimeUp and next screen
	static int		m_DifficultyScaling;	// difficulty increment (enemy movement speed, etc)

public:

	static void	 IncreaseDifficulty()		{ m_DifficultyScaling++; }		//ìÔà’ìxè„è∏âÒêî

	static bool	 GetGameStartFlag()			{ return m_GameStartFlag; }
	static float GetTime()					{ return m_Time; }
	static float GetCountdown()				{ return m_Countdown; }
	static int   GetDifficultyScaling()		{ return m_DifficultyScaling; }

	// 2020.08.29
	static void	 UnloadGameResources(bool used);

	void Init();
	void Uninit();
	void Update();

};
