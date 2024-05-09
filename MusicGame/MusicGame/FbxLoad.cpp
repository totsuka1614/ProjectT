/******************************************************************************
* 
* @file      FbxLoad.cpp
* @brief     FBX���[�h
* @author    Totsuka Kensuke
* @date      2024/05/04
* 
******************************************************************************/
#include "FbxLoad.h"
#include "FbxLoadDefine.h"
#include "ErrorMessageDefine.h"

#pragma comment(lib, "libfbxsdk-mt.lib")
#pragma comment(lib, "libxml2-mt.lib")
#pragma comment(lib, "zlib-mt.lib")

/******************************************************************************
* 
* @brief      CFbxLoad
* @return     void
* @author     Totsuka Kensuke
* @date       2024/05/04
* 
******************************************************************************/
CFbxLoad::CFbxLoad()
{
	//������
	m_pBone = new BoneListInfo;

	for (int i = 0; i < MAX_ANIMATION; i++){
		m_pAnimation[i] = new AnimationInfo;
		//������
		m_pAnimation[i]->curveList.clear();
		m_pAnimation[i]->loop = false;
		m_pAnimation[i]->playFrame = -1;
		m_pAnimation[i]->speed = -1;
		m_pAnimation[i]->totalFrame = -1;
	}

	m_pManager = FbxManager::Create();

	FbxIOSettings* pIO = FbxIOSettings::Create(m_pManager, IOSROOT);
	m_pManager->SetIOSettings(pIO);
}

/******************************************************************************
* 
* @brief      ~CFbxLoad
* @return     void
* @author     Totsuka Kensuke
* @date       2024/05/04
* 
******************************************************************************/
CFbxLoad::~CFbxLoad()
{
	m_pManager->Destroy();
}

void CFbxLoad::Load(const char* file_path)
{
	// �ǂݍ��ݏ�����
	FbxImporter* pImporter = FbxImporter::Create(m_pManager, "");
	if (!pImporter->Initialize(file_path, -1, m_pManager->GetIOSettings()))
	{
		//�t�@�C����������Ȃ�
		ErrorMessage->Output(ERROR_FBX_FILE_NOT_FOUND,ERROR_CELL);
	}

	// �ǂݍ���
	FbxScene* pScene = FbxScene::Create(m_pManager, "originalScene");
	pImporter->Import(pScene);
	// �O�p��
	FbxGeometryConverter geometryConverter(m_pManager);
	geometryConverter.Triangulate(pScene, true);
	geometryConverter.RemoveBadPolygonsFromMeshes(pScene);
	// �}�e���A���ŕ���
	geometryConverter.SplitMeshesPerMaterial(pScene, true);

	//�e�탍�[�h
	FbxLoadMesh(pScene,&m_pMesh);
	FbxLoadMaterial(pScene,&m_pMaterial);
	FbxLoadBone(pScene,&(*m_pBone));
	FbxLoadAnimation(pScene,&(*m_pAnimation));
}
