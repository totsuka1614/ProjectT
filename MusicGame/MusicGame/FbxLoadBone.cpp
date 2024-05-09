#include "FbxLoadDefine.h"

int GetRootBone(FbxNode* pNode,std::vector<BoneInfo*> bone_info);

void FbxLoadBone(FbxScene* pScene, BoneListInfo* pBone)
{
	if (pScene->GetMemberCount<FbxSkeleton>() == 0)
		return;

	for (int i = 0; i < pScene->GetMemberCount<FbxSkeleton>(); i++) {

		BoneInfo* bone_info = new BoneInfo;
		FbxNode* pNode = pScene->GetMember<FbxSkeleton>(i)->GetNode();
		//ボーン情報取得
		bone_info->name = pNode->GetInitialName();
		FbxDouble3 trans = pNode->LclTranslation.Get();
		FbxDouble3 rotate = pNode->LclRotation.Get();
		FbxDouble3 scale = pNode->LclScaling.Get();
		FbxDouble3 preRotate = pNode->PreRotation.Get();
		//挿入
		bone_info->translate.x = static_cast<float>(trans[0]);
		bone_info->translate.y = static_cast<float>(trans[1]);
		bone_info->translate.z = static_cast<float>(trans[2]);
		bone_info->rotation.x = static_cast<float>(rotate[0]);
		bone_info->rotation.y = static_cast<float>(rotate[1]);
		bone_info->rotation.z = static_cast<float>(rotate[2]);
		bone_info->scale.x = static_cast<float>(scale[0]);
		bone_info->scale.y = static_cast<float>(scale[1]);
		bone_info->scale.z = static_cast<float>(scale[2]);
		bone_info->preRotate.x = static_cast<float>(preRotate[0]);
		bone_info->preRotate.y = static_cast<float>(preRotate[1]);
		bone_info->preRotate.z = static_cast<float>(preRotate[2]);
		//座標系取得
		FbxEuler::EOrder order;
		pNode->GetRotationOrder(FbxNode::eSourcePivot, order);
		switch (order) {
		case FbxEuler::EOrder::eOrderXYZ: bone_info->order = BoneInfo::ROTATE_XYZ; break;
		case FbxEuler::EOrder::eOrderZXY: bone_info->order = BoneInfo::ROTATE_ZXY; break;
		default: assert(""); break;
		}

		pBone->list.push_back(bone_info);
	}
	//子要素の構築
	for (int i = 0; i < pBone->list.size(); i++) {
		FbxNode* pNode = pScene->GetMember<FbxSkeleton>(i)->GetNode();
		// 構築
		for (int f = 0; f < pNode->GetChildCount(); ++f) {
			for (auto bone : pBone->list) {
				if (bone->name == pNode->GetChild(i)->GetInitialName()) {
					pBone->list[i]->children.push_back(f);
					break;
				}
			}
		}
	}
	// ルートボーン
	pBone->root = GetRootBone(pScene->GetRootNode(),pBone->list);

}
/******************************************************************************
* 
* @brief      GetRootBone
* @param[in]  pNode
* @return     int
* @author     Totsuka Kensuke
* @date       2024/05/06
* 
******************************************************************************/
int GetRootBone(FbxNode* pNode, std::vector<BoneInfo*> bone_info)
{
	//Root取得
	int attrCnt = pNode->GetNodeAttributeCount();

	for (int i = 0; i < attrCnt; i++){
		//属性取得
		FbxNodeAttribute* attr = pNode->GetNodeAttributeByIndex(i);
		//eSkeletonの場合
		if (attr->GetAttributeType() == FbxNodeAttribute::eSkeleton){
			FbxNode* pBone = attr->GetNode();
			if (pBone != NULL){
				const char* nodename = pBone->GetInitialName();
				for (auto bone : bone_info){
					static int count = 0;
					if (nodename == bone->name){
						//親ルート更新
						FbxNode* pP = pBone->GetParent();
						nodename = pP->GetInitialName();
						return count;
					}
					count++;
				}
			}
		}
	}
	int root = -1;
	for (int i = 0; i < pNode->GetChildCount() && root < 0; ++i){
		root = GetRootBone(pNode->GetChild(i), bone_info);
	}
	return root;
}