#include "FbxLoadDefine.h"

void CalcAnimation(FbxAnimLayer* pLayer, FbxNode* pNode, AnimationInfo* anime);

void FbxLoadAnimation(FbxScene* pScene, AnimationInfo** pAnime)
{
	for (int i = 0; i < MAX_ANIMATION; i++){
		
		AnimationInfo* anime = new AnimationInfo;
		if (pAnime[i] != NULL){
			continue;
		}

		// ���̑�������
		anime->playFrame = 0.0f;
		anime->loop = false;
		anime->speed = 1.0f;

		int animeStackCount = pScene->GetSrcObjectCount<FbxAnimStack>();
		//�A�j���[�V���������邩
		if (animeStackCount == 0){
			return;
		}
		FbxAnimStack* pStack = pScene->GetSrcObject<FbxAnimStack>(0);
		int animeLayerCount = pStack->GetMemberCount<FbxAnimLayer>();
		if (animeLayerCount == 0){
			return;
		}
		//�A�j���[�V�����擾
		FbxTime time;
		time.SetTime(0, 0, 0, 1, 0, 0, FbxTime::eFrames60);

		anime->totalFrame = static_cast<long>((pStack->GetLocalTimeSpan().GetDuration().Get() + (time.Get() >> 1)) / time.Get());
		CalcAnimation(pStack->GetMember<FbxAnimLayer>(0), pScene->GetRootNode(), anime);

		pAnime[i] = anime;
	}
}
/******************************************************************************
*
* @brief      CalcAnimetion
* @param[in]  pScene
* @return     HRESULT
* @author     Totsuka Kensuke
* @date       2023/08/01
* @note       �m�[�h�̐􂢏o��
* @attention
*
******************************************************************************/
void CalcAnimation(FbxAnimLayer* pLayer, FbxNode* pNode, AnimationInfo* anime)
{
	// �e�v�f�̃L�[�𒊏o
	FbxAnimCurve* pCurves[] ={
		pNode->LclTranslation.GetCurve(pLayer, FBXSDK_CURVENODE_COMPONENT_X),
		pNode->LclTranslation.GetCurve(pLayer, FBXSDK_CURVENODE_COMPONENT_Y),
		pNode->LclTranslation.GetCurve(pLayer, FBXSDK_CURVENODE_COMPONENT_Z),
		pNode->LclRotation.GetCurve(pLayer, FBXSDK_CURVENODE_COMPONENT_X),
		pNode->LclRotation.GetCurve(pLayer, FBXSDK_CURVENODE_COMPONENT_Y),
		pNode->LclRotation.GetCurve(pLayer, FBXSDK_CURVENODE_COMPONENT_Z),
		pNode->LclScaling.GetCurve(pLayer, FBXSDK_CURVENODE_COMPONENT_X),
		pNode->LclScaling.GetCurve(pLayer, FBXSDK_CURVENODE_COMPONENT_Y),
		pNode->LclScaling.GetCurve(pLayer, FBXSDK_CURVENODE_COMPONENT_Z),
	};
	AnimationInfo::CurveInfo info;
	for (int i = 0; i < AnimationInfo::CurveInfo::CHANNEL_MAX; ++i){
		//���f���̕ω������邩
		if (pCurves[i] != NULL){
			FbxTime time;
			time.SetTime(0, 0, 0, 1, 0, 0, FbxTime::eFrames60);

			info.keyList[i].resize(pCurves[i]->KeyGetCount());
			AnimationInfo::CurveInfo::List::iterator it = info.keyList[i].begin();
			while (it != info.keyList[i].end()){
				int index = static_cast<int>(it - info.keyList[i].begin());
				it->frame = static_cast<int>((pCurves[i]->KeyGetTime(index).Get() + (time.Get() >> 1)) / time.Get()); // 0.5�����Đ؂�グ
				it->value = pCurves[i]->KeyGetValue(index);
				++it;
			}
		}
	}

	for (int i = 0; i < AnimationInfo::CurveInfo::CHANNEL_MAX; ++i){
		if (info.keyList[i].size() > 0){
			info.name = pNode->GetInitialName();
			anime->curveList.push_back(info);
		}
	}

	// �q�v�f����
	for (int i = 0; i < pNode->GetChildCount(); ++i){
		CalcAnimation(pLayer, pNode->GetChild(i), anime);
	}
}