/******************************************************************************
* 
* @file      FbxBuffer.h
* @brief     Fbx�̃V�F�[�_�ɑ���o�b�t�@
* @author    Totsuka Kensuke
* @date      2024/05/08
* 
******************************************************************************/
#pragma once
#include "main.h"
#include <vector>

class CFbxBuffer
{
public:
	// ���_�t�H�[�}�b�g
	typedef struct {
		XMFLOAT3 vtx;	// ���_���W
		XMFLOAT3 nor;	// �@���x�N�g��
		XMFLOAT2 tex;	// �e�N�X�`�����W
		// ���b�V���ƃ{�[�������т��邽�߂̃f�[�^
		float weight[4];// ���ꂼ��̍�����ǂ̒��x�e�����󂯂邩
		long index[4];  // �ǂ̍��Ɉ����t���ē�����
	} Vertex3D;
	// ���_�t�H�[�}�b�g
	typedef struct {
		XMFLOAT2 vtx;	// ���_���W
		XMFLOAT2 tex;	// �e�N�X�`�����W
		XMFLOAT4 diffuse;// �g�U���ˌ�
	} Vertex2D;
public:
	CFbxBuffer() : m_pVtxBuffer(nullptr), m_pIdxBuffer(nullptr) {}
	~CFbxBuffer() {
		SAFE_DELETE(m_pVtxBuffer);
		SAFE_DELETE(m_pIdxBuffer);
	}
	void CreateVertex(std::vector<Vertex3D> vertex);
	void CreateVertex(std::vector<Vertex2D> vertex);
	void CreateIndex(std::vector<UINT> index);
private:
	ID3D11Buffer* m_pVtxBuffer;
	UINT m_nVtxSize;
	UINT m_nVtxCount;

	ID3D11Buffer* m_pIdxBuffer;
	UINT m_nIdxSize;
	UINT m_nIdxCount;

	D3D11_PRIMITIVE_TOPOLOGY m_tTopology;
};