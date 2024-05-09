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

		//ランバート情報
		if (material->GetClassId().Is(FbxSurfaceLambert::ClassId)) {
			//アンビエント
			prop = material->FindProperty(FbxSurfaceMaterial::sAmbient);
			mat->pLambert->ambient.x = prop.Get<FbxDouble3>()[0];
			mat->pLambert->ambient.y = prop.Get<FbxDouble3>()[1];
			mat->pLambert->ambient.z = prop.Get<FbxDouble3>()[2];
			prop = material->FindProperty(FbxSurfaceMaterial::sAmbientFactor);
			mat->pLambert->ambient.w = prop.Get<FbxDouble>();

			//エミッシブ
			prop = material->FindProperty(FbxSurfaceMaterial::sEmissive);
			mat->pLambert->emissive.x = prop.Get<FbxDouble3>()[0];
			mat->pLambert->emissive.y = prop.Get<FbxDouble3>()[1];
			mat->pLambert->emissive.z = prop.Get<FbxDouble3>()[2];
			prop = material->FindProperty(FbxSurfaceMaterial::sEmissiveFactor);
			mat->pLambert->emissive.w = prop.Get<FbxDouble>();

			//ディヒューズ
			prop = material->FindProperty(FbxSurfaceMaterial::sDiffuse);
			mat->pLambert->diffuse.x = prop.Get<FbxDouble3>()[0];
			mat->pLambert->diffuse.y = prop.Get<FbxDouble3>()[1];
			mat->pLambert->diffuse.z = prop.Get<FbxDouble3>()[2];
			prop = material->FindProperty(FbxSurfaceMaterial::sDiffuseFactor);
			mat->pLambert->diffuse.w = prop.Get<FbxDouble>();
		}
		//フォング情報
		if (material->GetClassId().Is(FbxSurfacePhong::ClassId)){
			//リフレクション(反射率)
			prop = material->FindProperty(FbxSurfaceMaterial::sReflection);
			mat->pPhong->reflectivity = prop.Get<FbxDouble>();

			//シャイニス(輝度)
			prop = material->FindProperty(FbxSurfaceMaterial::sShininess);
			mat->pPhong->shininess = prop.Get<FbxDouble>();

			//スペキュラ
			prop = material->FindProperty(FbxSurfaceMaterial::sSpecular);
			mat->pPhong->specular.x = prop.Get<FbxDouble3>()[0];
			mat->pPhong->specular.y = prop.Get<FbxDouble3>()[1];
			mat->pPhong->specular.z = prop.Get<FbxDouble3>()[2];
			prop = material->FindProperty(FbxSurfaceMaterial::sSpecularFactor);
			mat->pPhong->specular.w = prop.Get<FbxDouble>();
		}
		//テクスチャゲット
		// Diffuseプロパティを取得
		prop = material->FindProperty(FbxSurfaceMaterial::sDiffuse);
		FbxFileTexture* texture = nullptr;
		int texture_num = prop.GetSrcObjectCount<FbxFileTexture>();
		if (texture_num > 0){
			//FbxFileTexture取得
			texture = prop.GetSrcObject<FbxFileTexture>();
		}
		else{
			//FbxLayeredTextureから取得
			int layer_num = prop.GetSrcObjectCount<FbxLayeredTexture>();
			if (layer_num > 0){
				texture = prop.GetSrcObject<FbxFileTexture>(0);
			}
		}
		//てくすちゃがあれば取得
		if (texture != nullptr){
			//ファイル名取得
			std::string file_path = texture->GetRelativeFileName();
			// ファイル分解
			char buffer[256];
			ZeroMemory(buffer, sizeof(char) * 256);
			memcpy(buffer, file_path.c_str(), sizeof(char) * 256);

			std::vector<std::string> split_list;

			// 記号統一
			Replace('\\', '/', buffer);

			// 「/」で分解　必要なし
			Split('/', buffer, split_list);

			ZeroMemory(buffer, sizeof(char) * 256);
			memcpy(buffer, split_list[split_list.size() - 1].data(), sizeof(char) * 256);

			// 「/」で分解　必要なし
			Split('.', buffer, split_list);

			//data/Texture/xxx.pngの形にする
			std::string root_path = "data/texture/";
			std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> cv;
			std::wstring wstr_file_name = cv.from_bytes(root_path + split_list[split_list.size() - 2] + "." + split_list[split_list.size() - 1]);
			//data/BumpMap/xxx.png
			root_path = "data/bumpmap/";
			std::wstring wstr_bumpfile_name = cv.from_bytes(root_path + split_list[split_list.size() - 2] + ".png");


			// 文字化け対策
			char* file_name;
			size_t size = 0;
			FbxAnsiToUTF8(split_list[split_list.size() - 1].c_str(), file_name, &size);

			//テクスチャロード
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