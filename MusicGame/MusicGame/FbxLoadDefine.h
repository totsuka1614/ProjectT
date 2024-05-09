/******************************************************************************
* 
* @file      FbxLoadDefine.h
* @brief     Fbx���[�h��`��
* @author    Totsuka Kensuke
* @date      2024/05/04
* 
******************************************************************************/
#pragma once
#include "FbxLoad.h"

#ifndef FbxLoadManager
#define FbxLoadManager CFbxLoadManager::Get()
#endif // !FbxLoadManager

enum eFbxFile {
	Player_01,

	Max_FbxFile_Num
};

//fbx�t�@�C��
static const char* g_cFbxFilePath[] = {
	"data/model/Jeep_Renegade_2016.fbx",
};

void FbxLoadMesh(FbxScene*, std::vector<MeshInfo*>*);
void FbxLoadMaterial(FbxScene*, std::vector<MaterialInfo*>*);
void FbxLoadBone(FbxScene*, BoneListInfo*);
void FbxLoadAnimation(FbxScene*, AnimationInfo**);