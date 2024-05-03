/******************************************************************************
* 
* @file      SceneBase.h
* @brief     �V�[�����N���X
* @author    Totsuka Kensuke
* @date      2024/04/29
* 
******************************************************************************/
#pragma once
#include "SceneManager.h"

class CSceneBase
{
public:
	CSceneBase() {};
	virtual ~CSceneBase() {};

	virtual void Update() = 0;
	virtual void Draw() = 0;
private:

};