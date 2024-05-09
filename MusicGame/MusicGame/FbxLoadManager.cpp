/******************************************************************************
* 
* @file      FbxLoadManager.cpp
* @brief     ä«óù
* @author    Totsuka Kensuke
* @date      2024/05/04
* 
******************************************************************************/
#include "FbxLoadManager.h"

CFbxLoadManager g_fbx_manager;

CFbxLoadManager* CFbxLoadManager::m_pManager = &g_fbx_manager;

void CFbxLoadManager::Create()
{
	for (int i = 0; i < eFbxFile::Max_FbxFile_Num; i++) {
		m_pFbxData[i] = new CFbxLoad;
		m_pFbxData[i]->Load(g_cFbxFilePath[i]);
	}
}
