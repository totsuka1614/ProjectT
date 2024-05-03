#include "SceneManager.h"
#include "ErrorMessageDefine.h"

CSceneManager g_scene_manager;	//インスタンス

CSceneManager* CSceneManager::m_pManager = &g_scene_manager;	//現在

void CSceneManager::Change(CSceneBase* scene) 
{
	if (!scene)
		ErrorMessage->Output(ERROR_SCENE_CHANGE_NOT_FOUND,ERROR_CELL);
	m_pScene.reset(scene);
}
