/******************************************************************************
* 
* @file      FbxLoad.h
* @brief     Fbxロード
* @author    Totsuka Kensuke
* @date      2024/05/04
* 
******************************************************************************/
#pragma once
#include "main.h"
#include "FbxDefine.h"
#include <fbxsdk.h>

class CFbxLoad
{
public:
	CFbxLoad();
	~CFbxLoad();

	void Load(const char* file_path);
private:
	FbxManager* m_pManager; //ファイルマネージャー
private:
	std::vector<MaterialInfo*> m_pMaterial;
	BoneListInfo* m_pBone;
	std::vector<MeshInfo*> m_pMesh;
	AnimationInfo* m_pAnimation[MAX_ANIMATION];
};