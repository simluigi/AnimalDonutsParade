/*==================================================================
DIRECTX11 �O�Z���� scene.h
Author: Sim Luigi
Last Updated: 2020.08.13

===================================================================*/

#pragma once
#include <list>				//list�\��				for using list structure
#include <typeinfo>			//typeid�̎g�p�̍�		for using typeid function
#include <vector>

#include "main.h"
#include "renderer.h"
#include "game_object.h"

// 2020.07.06: Layer variable added for all functions
// ���X�g�\���z�� Layer Format: Convert Single list to List Array
#define LAYER_MAX		3 

// 2020.07.24 CTitle, CGame, CResult: inherit from CScene (Object Oriented Programming)
// CTitle, CGame, CResult: CScene����p������i�I�u�W�F�N�g�w���v���O���~���O�j
class CScene
{
protected:

	// Layer Draw Priority 0/1/2 (higher number: higher 'level' i.e. Photoshop)
	// ���C���[�`��̗D�揇�� 
	std::list<CGameObject*> m_GameObject[LAYER_MAX];			 

public:
	CScene(){}
	virtual ~CScene(){}

	// 2020.07.27	
	// �C���^�[�t�F�[�X���F�������z�֐��ɕύX����
	// Interfacing: Convert to Pure Virtual Function
	virtual void Init() = 0;

	// �I���i�I�u�W�F�N�g�폜�E�����������j
	// Uninit Scene
	virtual void Uninit()
	{	
		// Layer�\�����[�v�F�e�I�u�W�F�N�g��Uninit()	
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

	// �X�V����
	// Update Process
	virtual void Update()
	{
		//Layer Format Loop
		//Layer�\�����[�v
		for (int i = 0; i < LAYER_MAX; i++)
		{			
			// �S�Ă�GameObject���� (���C���[����)
			// Update all objects (by layer)
			for (CGameObject* object : m_GameObject[i])
			{
				object->Update();
			}

			//���X�g����폜 
			//remove from list of CGameObjects
			m_GameObject[i].remove_if
			(
				//[ ] �����֐� �i�����͉��L�j
				//Nameless Function (see below)
				[](CGameObject* object)
				{
					return object->Destroy();
				}
			);
		}
	}

	//�����֐�[ ]�F�����_�� (C++ 11�ȍ~�j
	//Nameless Function [ ]: Lambda expression (C++ 11 and above)
	 
	// �`�揈��
	// Draw Process
	virtual void Draw()
	{
		// �S�Ă�GameObject���� (���C���[����)
		// Draw all objects (by layer)
		for (int i = 0; i < LAYER_MAX; i++)
		{
			for (CGameObject* object : m_GameObject[i])
			{
				object->Draw();
			}
		}
	}

	// �I�u�W�F�N�g�ǉ��@�\
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
	//�I�u�W�F�N�g�ǉ��{ID�ݒ�@�\
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
	//�I�u�W�F�N�g�ǉ��{����2��
	//AddGameObjectWithTwoArguments
	template <typename T>
	T* AddGameObjectWithTwoArguments(int Layer, int a, int b)
	{
		T* gameObject = new T();
		m_GameObject[Layer].push_back(gameObject);
		gameObject->Init(a, b);

		return gameObject;
	}

	// �I�u�W�F�N�gGet�@�\�i�P�́j
	// Template: GetGameObject (single object)	
	template <typename T>
	T* GetGameObject(int Layer)
	{
		for (CGameObject* object : m_GameObject[Layer])
		{
			if (typeid(*object) == typeid(T))			//typeid: GameObject type		�^�𒲂ׂ�
			{
				return (T*)object;  //returns object
			}
		}
		return NULL;	//not the same type	�^���قȂ�ꍇ
	}

	// �I�u�W�F�N�gGet�@�\�i�����j
	// Template: GetGameObjects (multiple objects)		
	template <typename T>
	std::vector<T*> GetGameObjects(int Layer)		
	{
		//STL�̔z��		
		//STL vector	
		std::vector<T*> objects;		

		for (CGameObject* object : m_GameObject[Layer])
		{
			if (typeid(*object) == typeid(T))			//�^�𒲂ׂ�		typeid: GameObject type		
			{
				objects.push_back((T*)object);
			}
		}

		//���ꂵ���I�u�W�F�N�g��S�ă��X�g�ŕԂ��i0�̏ꍇ������j
		//returns list of all objects found with the same type	(can return 0 objects)
		return objects;   
	}
};