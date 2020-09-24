/*==================================================================
DIRECTX11 三校合同 scene.h
Author: Sim Luigi
Last Updated: 2020.08.13

===================================================================*/

#pragma once
#include <list>				//list構造				for using list structure
#include <typeinfo>			//typeidの使用の際		for using typeid function
#include <vector>

#include "main.h"
#include "renderer.h"
#include "game_object.h"

// 2020.07.06: Layer variable added for all functions
// リスト構造配列 Layer Format: Convert Single list to List Array
#define LAYER_MAX		3 

// 2020.07.24 CTitle, CGame, CResult: inherit from CScene (Object Oriented Programming)
// CTitle, CGame, CResult: CSceneから継承する（オブジェクト指向プログラミング）
class CScene
{
protected:

	// Layer Draw Priority 0/1/2 (higher number: higher 'level' i.e. Photoshop)
	// レイヤー描画の優先順位 
	std::list<CGameObject*> m_GameObject[LAYER_MAX];			 

public:
	CScene(){}
	virtual ~CScene(){}

	// 2020.07.27	
	// インターフェース化：純粋仮想関数に変更する
	// Interfacing: Convert to Pure Virtual Function
	virtual void Init() = 0;

	// 終了（オブジェクト削除・メモリ上解放）
	// Uninit Scene
	virtual void Uninit()
	{	
		// Layer構造ループ：各オブジェクトをUninit()	
		// Layer Format Loop: Uninit all objects	
		for (int i = 0; i < LAYER_MAX; i++)
		{
			for (CGameObject* object : m_GameObject[i])
			{
				object->Uninit();
				delete object;
			}
			m_GameObject[i].clear();
		}
	}

	// 更新処理
	// Update Process
	virtual void Update()
	{
		//Layer Format Loop
		//Layer構造ループ
		for (int i = 0; i < LAYER_MAX; i++)
		{			
			// 全てのGameObjectを回す (レイヤー順番)
			// Update all objects (by layer)
			for (CGameObject* object : m_GameObject[i])
			{
				object->Update();
			}

			//リストから削除 
			//remove from list of CGameObjects
			m_GameObject[i].remove_if
			(
				//[ ] 無名関数 （説明は下記）
				//Nameless Function (see below)
				[](CGameObject* object)
				{
					return object->Destroy();
				}
			);
		}
	}

	//無名関数[ ]：ラムダ式 (C++ 11以降）
	//Nameless Function [ ]: Lambda expression (C++ 11 and above)
	 
	// 描画処理
	// Draw Process
	virtual void Draw()
	{
		// 全てのGameObjectを回す (レイヤー順番)
		// Draw all objects (by layer)
		for (int i = 0; i < LAYER_MAX; i++)
		{
			for (CGameObject* object : m_GameObject[i])
			{
				object->Draw();
			}
		}
	}

	// オブジェクト追加機能
	// Template: AddGameObject	
	template <typename T>
	T* AddGameObject(int Layer)
	{
		T* gameObject = new T();
		m_GameObject[Layer].push_back(gameObject);
		gameObject->Init();

		return gameObject;
	}

	//2020.08.13
	//オブジェクト追加＋ID設定機能
	//AddGameObjectWithID	
	template <typename T>
	T* AddGameObjectWithID(int Layer, int ID)
	{
		T* gameObject = new T();
		m_GameObject[Layer].push_back(gameObject);
		gameObject->Init(ID);

		return gameObject;
	}

	//2020.08.18
	//オブジェクト追加＋引数2つ
	//AddGameObjectWithTwoArguments
	template <typename T>
	T* AddGameObjectWithTwoArguments(int Layer, int a, int b)
	{
		T* gameObject = new T();
		m_GameObject[Layer].push_back(gameObject);
		gameObject->Init(a, b);

		return gameObject;
	}

	// オブジェクトGet機能（単体）
	// Template: GetGameObject (single object)	
	template <typename T>
	T* GetGameObject(int Layer)
	{
		for (CGameObject* object : m_GameObject[Layer])
		{
			if (typeid(*object) == typeid(T))			//typeid: GameObject type		型を調べる
			{
				return (T*)object;  //returns object
			}
		}
		return NULL;	//not the same type	型が異なる場合
	}

	// オブジェクトGet機能（複数）
	// Template: GetGameObjects (multiple objects)		
	template <typename T>
	std::vector<T*> GetGameObjects(int Layer)		
	{
		//STLの配列		
		//STL vector	
		std::vector<T*> objects;		

		for (CGameObject* object : m_GameObject[Layer])
		{
			if (typeid(*object) == typeid(T))			//型を調べる		typeid: GameObject type		
			{
				objects.push_back((T*)object);
			}
		}

		//統一したオブジェクトを全てリストで返す（0の場合もある）
		//returns list of all objects found with the same type	(can return 0 objects)
		return objects;   
	}
};