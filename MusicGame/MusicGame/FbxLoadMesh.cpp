#include "FbxLoadDefine.h"
#include <algorithm>

void GetRootMat(std::string& name, FbxMesh* pMesh, FbxNode* pNode);

void FbxLoadMesh(FbxScene* pScene, std::vector<MeshInfo*> *pMesh)
{
	FbxNode* pNode = pScene->GetRootNode();
	for (int i = 0; i < pScene->GetMemberCount<FbxMesh>(); i++) {

		MeshInfo* mesh = new MeshInfo;

		FbxMesh* fbx_mesh = pScene->GetMember<FbxMesh>(i);

		mesh->name = pNode->GetInitialName();
		//�C���f�b�N�X���
		for (int f = 0; f < fbx_mesh->GetPolygonCount(); f++) {
			mesh->IndexList.push_back(fbx_mesh->GetPolygonVertex(f, 0));
			mesh->IndexList.push_back(fbx_mesh->GetPolygonVertex(f, 1));
			mesh->IndexList.push_back(fbx_mesh->GetPolygonVertex(f, 2));
		}
		//���_���
		FbxVector4* pVertices = fbx_mesh->GetControlPoints();
		for (int f = 0; f < fbx_mesh->GetControlPointsCount(); f++) {
			XMFLOAT3 vertex;
			vertex.x = pVertices[f][0];
			vertex.y = pVertices[f][1];
			vertex.z = pVertices[f][2];
			mesh->VertexList.push_back(vertex);
		}
		//�m�[�}�����(�@��)
		FbxGeometryElementNormal* pNormal = fbx_mesh->GetElementNormal();
		FbxLayerElement::EMappingMode mapping = pNormal->GetMappingMode();
		int normal_count = 0;
		MeshInfo::NormalInfo normal_info;
		if (mapping == FbxGeometryElement::eByControlPoint) {
			normal_count = mesh->VertexList.size();
			normal_info.mapping = MAPPING_VERTEX;
		}
		else if (mapping == FbxGeometryElement::eByPolygonVertex) {
			normal_count = mesh->IndexList.size();
			normal_info.mapping = MAPPING_INDEX;
		}
		for (int f = 0; f < normal_count; f++) {
			FbxVector4 normals = pNormal->GetDirectArray().GetAt(f);
			XMFLOAT3 normal;
			normal.x = normals[0];
			normal.y = normals[1];
			normal.z = normals[2];
			normal_info.List.push_back(normal);
		}
		mesh->NormalList = normal_info;
		//UV���
		int uvCount = fbx_mesh->GetElementUVCount();
		if (uvCount > 0) {
			for (int f = 0; f < uvCount; f++) {
				MeshInfo::UVInfo uv_info;
				FbxGeometryElementUV* pUV = fbx_mesh->GetElementUV(f);
				if (pUV) {
					FbxLayerElement::EMappingMode mapping = pUV->GetMappingMode();
					FbxLayerElement::EReferenceMode reference = pUV->GetReferenceMode();
					int uv_count = 0;
					// �}�b�s���O�ʂɏ�����
					if (mapping == FbxGeometryElement::eByControlPoint) {
						uv_info.mapping = MAPPING_VERTEX;
						uv_count = mesh->VertexList.size();
					}
					else if (mapping == FbxGeometryElement::eByPolygonVertex) {
						uv_info.mapping = MAPPING_INDEX;
						uv_count = mesh->IndexList.size();
					}
					for (int g = 0; g < uv_count; g++) {
						int uvIndex = g;
						if (reference == FbxGeometryElement::eIndexToDirect) {
							uvIndex = uvIndex / 3 * 3 + (uvIndex % 3);
							uvIndex = pUV->GetIndexArray().GetAt(uvIndex); // �C���f�b�N�X�Ή�
						}
						FbxVector2 UVs = pUV->GetDirectArray().GetAt(uvIndex);
						XMFLOAT2 uv;
						uv.x = UVs[0];
						uv.y = UVs[1];
						uv_info.List.push_back(uv);
					}
				}
				mesh->UVList.push_back(uv_info);
			}
		}
		//�}�e���A����
		GetRootMat(mesh->MaterialName, fbx_mesh, pNode);
		//�X�L�����
		int skinCount = fbx_mesh->GetDeformerCount(FbxDeformer::eSkin);
		if (skinCount > 0) {
			//���b�V���̃{�[�����
			std::vector<std::vector<MeshInfo::SkinInfo::WeightInfo>> VertexWeightList(mesh->VertexList.size());
			FbxSkin* pSkin = (FbxSkin*)fbx_mesh->GetDeformer(0, FbxDeformer::eSkin);
			for (int f = 0; f < pSkin->GetClusterCount(); f++) {
				MeshInfo::SkinInfo::BoneInfo bone_info;
				FbxCluster* pCluster = pSkin->GetCluster(f);
				FbxAMatrix mat; 
				pCluster->GetTransformLinkMatrix(mat);
				bone_info.name = pCluster->GetLink()->GetInitialName();
				for (int g = 0; g < 4; g++) {
					for (int h = 0; h < 4; h++) {
						bone_info.offset[g][h] = mat[g][h];
					}
				}
				//���_�u�����h���擾
				int* pIndices = pCluster->GetControlPointIndices();
				double* pWeights = pCluster->GetControlPointWeights();
				for (int g = 0; g < pCluster->GetControlPointIndicesCount(); g++){
					MeshInfo::SkinInfo::WeightInfo weightInfo = { f,pWeights[g] };
					VertexWeightList[pIndices[g]].push_back(weightInfo);
				}
				mesh->skinInfo.BoneList.push_back(bone_info);
			}
			//���ꉽ�̏����H
			std::vector<std::vector<MeshInfo::SkinInfo::WeightInfo>>::iterator itWeight = VertexWeightList.begin();
			while (itWeight != VertexWeightList.end()) {
				std::sort(itWeight->begin(), itWeight->end(),
					[](const MeshInfo::SkinInfo::WeightInfo& objA, const MeshInfo::SkinInfo::WeightInfo& objB) {
					return objA.weight > objB.weight;
				});
				while (itWeight->size() > 4)
					itWeight->pop_back();
				while (itWeight->size() < 4){
					MeshInfo::SkinInfo::WeightInfo weight = { 0,0.0f };
					itWeight->push_back(weight);
				}
				int index = (int)(itWeight - VertexWeightList.begin());
				float total = 0.0f;
				for (int i = 0; i < 4; i++){
					mesh->skinInfo.WeightList[index].index[i] = (*itWeight).data()->index[i];
					total += (*itWeight).data()->weight[i];
				}
				if (total == 0.0f)
					total = 1.0f;
				for (int i = 0; i < 4; ++i){
					mesh->skinInfo.WeightList[index].weight[i] = (*itWeight).data()->weight[i] / total;
				}
				++itWeight;
			}
		}
		else{
			// �قڂقڃ��j�e�B�����̂��߂̑Ή�����
			// �{�[���̃m�[�h�ɕR�Â��Ă��邩�`�F�b�N
			FbxNode* pMeshNode = fbx_mesh->GetNode();
			FbxNode* parent = pMeshNode->GetParent();
			while (parent != NULL){
				FbxNodeAttribute* attr = parent->GetNodeAttribute();
				if (attr != NULL){
					FbxNodeAttribute::EType type = attr->GetAttributeType();
					if (type == FbxNodeAttribute::eSkeleton){
						break;
					}
					else if (type == FbxNodeAttribute::eMesh){
						pMeshNode = parent;
					}
				}
				parent = parent->GetParent();
			}
			// �R�Â��Ă����ꍇ�A���̃{�[���Ɋ��S�ˑ����钸�_�u�����h�Ƃ��Ĉ���
			if (parent != NULL){
				// �{�[�����ݒ�
				MeshInfo::SkinInfo::BoneInfo boneInfo;
				FbxAMatrix mat = pMeshNode->EvaluateLocalTransform();
				mat = mat.Inverse();
				for (int i = 0; i < 4; ++i) {
					for (int j = 0; j < 4; ++j) {
						boneInfo.offset[i][j] = static_cast<float>(mat[i][j]);
					}
				}
				boneInfo.name = parent->GetInitialName();
				mesh->skinInfo.BoneList.push_back(boneInfo);

				// ���_�u�����h�ݒ�
				mesh->skinInfo.WeightList.resize(mesh->VertexList.size());
				std::vector<MeshInfo::SkinInfo::WeightInfo>::iterator it = mesh->skinInfo.WeightList.begin();
				while (it != mesh->skinInfo.WeightList.end()){
					for (int i = 0; i < 4; ++i){
						it->index[i] = 0;
						it->weight[i] = 0.0f;
					}
					it->weight[0] = 1.0f;
					it++;
				}
			}
		}
		//�p���s��̎擾
		pNode = fbx_mesh->GetNode();
		FbxNode* parent = pNode->GetParent();
		//�e�K�w�����邩
		while (parent != NULL){
			FbxNodeAttribute* attr = parent->GetNodeAttribute();
			//���������邩
			while (attr != NULL){
				FbxNodeAttribute::EType type = attr->GetAttributeType();
				//����eSkeleton
				if (type == FbxNodeAttribute::EType::eSkeleton){
					// �X�P���g���̎q�K�w���ƁA�g�����X�t�H�[���𖳎����Ă��悢�H
					for (int i = 0; i < 4; ++i) {
						for (int j = 0; j < 4; ++j) {
							mesh->transform.m[i][j] = static_cast<float>(i == j ? 1.0f : 0.0f);
						}
					}
				}
				break;
			}
			parent = parent->GetParent();
		}
		//�p���s��擾
		FbxAMatrix transform(
			FbxVector4(pNode->LclTranslation),
			FbxVector4(pNode->LclRotation),
			FbxVector4(pNode->LclScaling));
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				mesh->transform.m[i][j] = static_cast<float>(transform[i][j]);
			}
		}

		pMesh->push_back(mesh);
	}
}

/******************************************************************************
* 
* @brief      GetRootMat
* @param[in]  name
* @param[in]  pMesh
* @param[in]  pNode
* @return     void
* @author     Totsuka Kensuke
* @date       2024/05/06
* 
******************************************************************************/
void GetRootMat(std::string& name, FbxMesh* pMesh, FbxNode* pNode)
{
	int attrCnt = pNode->GetNodeAttributeCount();
	for (int i = 0; i < attrCnt; ++i){
		FbxNodeAttribute* attr = pNode->GetNodeAttributeByIndex(i);
		if (attr == pMesh){
			if (attr->GetAttributeType() == FbxNodeAttribute::eMesh){
				if (pNode->GetMaterialCount() > 0){
					name = pNode->GetMaterial(i)->GetInitialName();
				}
				return;
			}
		}
	}

	// �q�v�f�̒T��
	for (int i = 0; i < pNode->GetChildCount(); ++i){
		GetRootMat(name, pMesh, pNode->GetChild(i));
	}
}