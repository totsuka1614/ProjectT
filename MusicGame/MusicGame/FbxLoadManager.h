/******************************************************************************
* 
* @file      FbxLoadManager.h
* @brief     Fbxファイルロード
* @author    Totsuka Kensuke
* @date      2024/05/04
* 
******************************************************************************/
#pragma once
#include "main.h"

class CFbxLoadManager
{
public:
	CFbxLoadManager() {};
	~CFbxLoadManager() {};

	static CFbxLoadManager* Get() { return m_pManager; }
private:
	static CFbxLoadManager* m_pManager;
private:

};