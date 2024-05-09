/******************************************************************************
* 
* @file      FbxDefine.h
* @brief     Fbx��`��
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
		XMFLOAT4 ambient;	//�A���r�G���g
		XMFLOAT4 diffuse;	//�f�B�q���[�Y
		XMFLOAT4 emissive;	//�G�~�b�V�u
	};
	struct Phong
	{
		XMFLOAT4	specular;	//�X�y�L����
		float	shininess;		//���x
		float	reflectivity;	//���˗�
	};
	struct Texture
	{
		ID3D11ShaderResourceView* pTex;	//�e�N�X�`�����
		ID3D11ShaderResourceView* pBumpTex;	//�o���v�}�b�v���
		std::string TexName;	//�e�N�X�`����
		bool bBump;				//�o���v�}�b�v�����邩
	};

	std::string name;	//�}�e���A����
	Lambert* pLambert;		//�����o�[�g���
	Phong* pPhong;		//�t�H�����
	Texture		texture;
};

struct BoneInfo
{
	// ��]����
	enum RotateOrder
	{
		ROTATE_XYZ,
		ROTATE_ZXY,
	};

	//�{�[����
	std::string	name;
	//�ړ��l
	XMFLOAT3	translate;
	//��]�l
	XMFLOAT3	rotation;
	//�g��k��
	XMFLOAT3	scale;
	//���O��]
	XMFLOAT3	preRotate;
	//��]����
	RotateOrder order;
	//�q�v�f
	std::vector<long>	children;
};
struct BoneListInfo
{
	int root;
	std::vector<BoneInfo*> list;
};

struct MeshInfo
{
	// �@�����
	struct NormalInfo
	{
		std::vector<XMFLOAT3> List;
		Mapping	mapping;
	};
	// UV���
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
	//���b�V����
	std::string name;
	//���_���
	std::vector<XMFLOAT3> VertexList;
	//�C���f�b�N�X���
	std::vector<UINT> IndexList;
	//�@�����
	NormalInfo NormalList;
	//UV���
	std::vector<UVInfo> UVList;
	//�}�e���A����
	std::string MaterialName;
	//�X�L�����
	SkinInfo skinInfo;
	//�p�����
	XMFLOAT4X4 transform;
};

// �A�j���[�V�������
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

		std::string		name;					///< �Ή�����{�[����
		List			keyList[CHANNEL_MAX];	///< �`�����l�����Ƃ̃L�[���
	};
	typedef std::vector<CurveInfo> List;

	long		totalFrame;		///< �A�j���[�V��������
	List		curveList;		///< �A�j�����

	float playFrame; // ���ݍĐ����̃t���[��
	bool loop; // �J��Ԃ��Đ����邩�ǂ���
	float speed; // �A�j���[�V�����̍Đ��X�s�[�h
};