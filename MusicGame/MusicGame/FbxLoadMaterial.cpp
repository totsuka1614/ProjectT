#include "FbxLoadDefine.h"
#include "Texture.h"
#include "DeviceManager.h"
#include "Utility.h"
#include <codecvt>

void FbxLoadMaterial(FbxScene* pScene, std::vector<MaterialInfo*> *pMat)
{
	for (int i = 0; i < pScene->GetMaterialCount(); i++) {
		
		MaterialInfo* mat = new MaterialInfo;
		mat->pLambert = new MaterialInfo::Lambert;
		mat->pPhong = new MaterialInfo::Phong;

		FbxSurfaceMaterial* material = pScene->GetMaterial(i);
		FbxProperty prop;

		mat->name = material->GetInitialName();

		//�����o�[�g���
		if (material->GetClassId().Is(FbxSurfaceLambert::ClassId)) {
			//�A���r�G���g
			prop = material->FindProperty(FbxSurfaceMaterial::sAmbient);
			mat->pLambert->ambient.x = prop.Get<FbxDouble3>()[0];
			mat->pLambert->ambient.y = prop.Get<FbxDouble3>()[1];
			mat->pLambert->ambient.z = prop.Get<FbxDouble3>()[2];
			prop = material->FindProperty(FbxSurfaceMaterial::sAmbientFactor);
			mat->pLambert->ambient.w = prop.Get<FbxDouble>();

			//�G�~�b�V�u
			prop = material->FindProperty(FbxSurfaceMaterial::sEmissive);
			mat->pLambert->emissive.x = prop.Get<FbxDouble3>()[0];
			mat->pLambert->emissive.y = prop.Get<FbxDouble3>()[1];
			mat->pLambert->emissive.z = prop.Get<FbxDouble3>()[2];
			prop = material->FindProperty(FbxSurfaceMaterial::sEmissiveFactor);
			mat->pLambert->emissive.w = prop.Get<FbxDouble>();

			//�f�B�q���[�Y
			prop = material->FindProperty(FbxSurfaceMaterial::sDiffuse);
			mat->pLambert->diffuse.x = prop.Get<FbxDouble3>()[0];
			mat->pLambert->diffuse.y = prop.Get<FbxDouble3>()[1];
			mat->pLambert->diffuse.z = prop.Get<FbxDouble3>()[2];
			prop = material->FindProperty(FbxSurfaceMaterial::sDiffuseFactor);
			mat->pLambert->diffuse.w = prop.Get<FbxDouble>();
		}
		//�t�H���O���
		if (material->GetClassId().Is(FbxSurfacePhong::ClassId)){
			//���t���N�V����(���˗�)
			prop = material->FindProperty(FbxSurfaceMaterial::sReflection);
			mat->pPhong->reflectivity = prop.Get<FbxDouble>();

			//�V���C�j�X(�P�x)
			prop = material->FindProperty(FbxSurfaceMaterial::sShininess);
			mat->pPhong->shininess = prop.Get<FbxDouble>();

			//�X�y�L����
			prop = material->FindProperty(FbxSurfaceMaterial::sSpecular);
			mat->pPhong->specular.x = prop.Get<FbxDouble3>()[0];
			mat->pPhong->specular.y = prop.Get<FbxDouble3>()[1];
			mat->pPhong->specular.z = prop.Get<FbxDouble3>()[2];
			prop = material->FindProperty(FbxSurfaceMaterial::sSpecularFactor);
			mat->pPhong->specular.w = prop.Get<FbxDouble>();
		}
		//�e�N�X�`���Q�b�g
		// Diffuse�v���p�e�B���擾
		prop = material->FindProperty(FbxSurfaceMaterial::sDiffuse);
		FbxFileTexture* texture = nullptr;
		int texture_num = prop.GetSrcObjectCount<FbxFileTexture>();
		if (texture_num > 0){
			//FbxFileTexture�擾
			texture = prop.GetSrcObject<FbxFileTexture>();
		}
		else{
			//FbxLayeredTexture����擾
			int layer_num = prop.GetSrcObjectCount<FbxLayeredTexture>();
			if (layer_num > 0){
				texture = prop.GetSrcObject<FbxFileTexture>(0);
			}
		}
		//�Ă������Ⴊ����Ύ擾
		if (texture != nullptr){
			//�t�@�C�����擾
			std::string file_path = texture->GetRelativeFileName();
			// �t�@�C������
			char buffer[256];
			ZeroMemory(buffer, sizeof(char) * 256);
			memcpy(buffer, file_path.c_str(), sizeof(char) * 256);

			std::vector<std::string> split_list;

			// �L������
			Replace('\\', '/', buffer);

			// �u/�v�ŕ����@�K�v�Ȃ�
			Split('/', buffer, split_list);

			ZeroMemory(buffer, sizeof(char) * 256);
			memcpy(buffer, split_list[split_list.size() - 1].data(), sizeof(char) * 256);

			// �u/�v�ŕ����@�K�v�Ȃ�
			Split('.', buffer, split_list);

			//data/Texture/xxx.png�̌`�ɂ���
			std::string root_path = "data/texture/";
			std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> cv;
			std::wstring wstr_file_name = cv.from_bytes(root_path + split_list[split_list.size() - 2] + "." + split_list[split_list.size() - 1]);
			//data/BumpMap/xxx.png
			root_path = "data/bumpmap/";
			std::wstring wstr_bumpfile_name = cv.from_bytes(root_path + split_list[split_list.size() - 2] + ".png");


			// ���������΍�
			char* file_name;
			size_t size = 0;
			FbxAnsiToUTF8(split_list[split_list.size() - 1].c_str(), file_name, &size);

			//�e�N�X�`�����[�h
			if (CreateTextureFromFile(DeviceManager->GetDevice(), wstr_file_name.c_str(), &mat->texture.pTex) == S_OK)
			{
				mat->texture.TexName = material->GetInitialName();
				if (CreateTextureFromFile(DeviceManager->GetDevice(), wstr_bumpfile_name.c_str(), &mat->texture.pBumpTex) == S_OK)
					mat->texture.bBump = true;
			}
		}

		pMat->push_back(mat);
	}
}