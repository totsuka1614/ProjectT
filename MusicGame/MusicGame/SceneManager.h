/******************************************************************************
* 
* @file      SceneManager.h
* @brief     シーン管理クラス
* @author    Totsuka Kensuke
* @date      2024/04/29
* 
******************************************************************************/
#pragma once
//インクルード
#include "SceneBase.h"
#include "SceneDefine.h"
#include <iostream>
#ifndef SceneManager
#define SceneManager CSceneManager::Get()
#endif // !SceneManager

class CSceneBase;
class CSceneManager
{
public:
	CSceneManager() { m_pScene.reset(StartScene); };
	~CSceneManager() {};

	void Update() { m_pScene->Update(); };
	void Draw() { m_pScene->Draw(); };

	void Change(CSceneBase* scene);
public:
	static CSceneManager* Get() { return m_pManager; }
private:
	static CSceneManager* m_pManager;
private:
	std::shared_ptr<CSceneBase> m_pScene;
};