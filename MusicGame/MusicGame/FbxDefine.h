/******************************************************************************
* 
* @file      FbxDefine.h
* @brief     Fbx定義書
* @author    Totsuka Kensuke
* @date      2024/05/04
* 
******************************************************************************/
#pragma once
#include "main.h"
#include <vector>
#include <string>

#define MAX_ANIMATION (10)

enum Mapping
{
	MAPPING_VERTEX,
	MAPPING_INDEX,
};

struct MaterialInfo
{
	struct Lambert
	{
		XMFLOAT4 ambient;	//アンビエント
		XMFLOAT4 diffuse;	//ディヒューズ
		XMFLOAT4 emissive;	//エミッシブ
	};
	struct Phong
	{
		XMFLOAT4	specular;	//スペキュラ
		float	shininess;		//光度
		float	reflectivity;	//反射率
	};
	struct Texture
	{
		ID3D11ShaderResourceView* pTex;	//テクスチャ情報
		ID3D11ShaderResourceView* pBumpTex;	//バンプマップ情報
		std::string TexName;	//テクスチャ名
		bool bBump;				//バンプマップがあるか
	};

	std::string name;	//マテリアル名
	Lambert* pLambert;		//ランバート情報
	Phong* pPhong;		//フォン情報
	Texture		texture;
};

struct BoneInfo
{
	// 回転順序
	enum RotateOrder
	{
		ROTATE_XYZ,
		ROTATE_ZXY,
	};

	//ボーン名
	std::string	name;
	//移動値
	XMFLOAT3	translate;
	//回転値
	XMFLOAT3	rotation;
	//拡大縮小
	XMFLOAT3	scale;
	//事前回転
	XMFLOAT3	preRotate;
	//回転順序
	RotateOrder order;
	//子要素
	std::vector<long>	children;
};
struct BoneListInfo
{
	int root;
	std::vector<BoneInfo*> list;
};

struct MeshInfo
{
	// 法線情報
	struct NormalInfo
	{
		std::vector<XMFLOAT3> List;
		Mapping	mapping;
	};
	// UV情報
	struct UVInfo
	{
		std::vector<XMFLOAT2> List;
		Mapping	mapping;
	};
	struct SkinInfo
	{
		struct WeightInfo
		{
			long index[4];
			float weight[4];
		};

		struct BoneInfo
		{
			std::string name;
			float offset[4][4];
		};

		std::vector<WeightInfo> WeightList;
		std::vector<BoneInfo>	BoneList;
	};
	//メッシュ名
	std::string name;
	//頂点情報
	std::vector<XMFLOAT3> VertexList;
	//インデックス情報
	std::vector<UINT> IndexList;
	//法線情報
	NormalInfo NormalList;
	//UV情報
	std::vector<UVInfo> UVList;
	//マテリアル名
	std::string MaterialName;
	//スキン情報
	SkinInfo skinInfo;
	//姿勢情報
	XMFLOAT4X4 transform;
};

// アニメーション情報
struct AnimationInfo
{
	struct CurveInfo
	{
		enum Channels
		{
			TRANSLATION_X,
			TRANSLATION_Y,
			TRANSLATION_Z,
			ROTATION_X,
			ROTATION_Y,
			ROTATION_Z,
			SCALING_X,
			SCALING_Y,
			SCALING_Z,
			CHANNEL_MAX
		};
		struct KeyInfo
		{
			long	frame;
			float	value;
		};
		typedef std::vector<KeyInfo> List;

		std::string		name;					///< 対応するボーン名
		List			keyList[CHANNEL_MAX];	///< チャンネルごとのキー情報
	};
	typedef std::vector<CurveInfo> List;

	long		totalFrame;		///< アニメーション時間
	List		curveList;		///< アニメ情報

	float playFrame; // 現在再生中のフレーム
	bool loop; // 繰り返し再生するかどうか
	float speed; // アニメーションの再生スピード
};