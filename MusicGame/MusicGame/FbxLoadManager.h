/******************************************************************************
* 
* @file      FbxLoadManager.h
* @brief     Fbxファイルロード
* @author    Totsuka Kensuke
* @date      2024/05/04
* 
******************************************************************************/
#pragma once
#include "FbxLoad.h"
#include "FbxLoadDefine.h"

class CFbxLoad;
class CFbxLoadManager
{
public:
	CFbxLoadManager(){};
	~CFbxLoadManager() {};

	void Create();
	CFbxLoad& GetFbxData(eFbxFile num) { m_pFbxData[num]; }
	static CFbxLoadManager* Get() { return m_pManager; }
private:
	static CFbxLoadManager* m_pManager;
private:
	CFbxLoad* m_pFbxData[eFbxFile::Max_FbxFile_Num];
};