/*==================================================================
DIRECTX11 �O�Z���� manager.h
Author: Sim Luigi
Last Updated: 2020.08.13
===================================================================*/

#pragma once

class CManager
{
private:
	// �K��Static�Őݒ肵�āI ������.cpp���Đ錾���K�v
	// make sure to set this as static, redeclare all static variables in .cpp
	static class CScene*	m_Scene;

	// 2020.08.29
	static bool				m_FirstPlay;
	static bool				m_FirstResult;

public:
	CManager() {}
	~CManager() {}

	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();

	// 2020.08.29
	// First access of specific scenes (also for Unload() - will not unload unused assets )
	static void SetFirstPlay(bool firstPlay)		{ m_FirstPlay = firstPlay; }
	static bool GetFirstPlay()						{ return m_FirstPlay; }
	static void SetFirstResult(bool firstResult)	{ m_FirstResult = firstResult; }
	static bool GetFirstResult()					{ return m_FirstResult; }

	// 2020.08.29
	static void UnloadAllResources();

	static class CScene* GetScene() { return m_Scene; }
	// 2020.07.27 
	// SetScene�e���v���[�g�ǉ�
	// SetScene Template added
	template<typename T>
	static void SetScene()
	{
		if ( m_Scene != NULL )
		{
			m_Scene->Uninit();
			delete m_Scene;
		}

		T* scene = new T();
		scene->Init();

		m_Scene = scene;
	}

};