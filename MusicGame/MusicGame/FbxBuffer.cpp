/******************************************************************************
* 
* @file      FbxBuffer.cpp
* @brief     
* @author    Totsuka Kensuke
* @date      2024/05/08
* 
******************************************************************************/
#include "FbxBuffer.h"
#include "DeviceManager.h"
#include "ErrorMessageDefine.h"

/******************************************************************************
* 
* @brief      CreateVertex
* @param[in]  vertex
* @return     HRESULT
* @author     Totsuka Kensuke
* @date       2024/05/08
* 
******************************************************************************/
void CFbxBuffer::CreateVertex(std::vector<Vertex3D> vertex)
{
	//���_�o�b�t�@�쐬
	D3D11_BUFFER_DESC buffer_desc;
	buffer_desc.ByteWidth = sizeof(Vertex3D) * vertex.size();	// �o�b�t�@�̃T�C�Y
	buffer_desc.Usage = D3D11_USAGE_DEFAULT;			// �g�p���@
	buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;	// BIND�ݒ�
	buffer_desc.CPUAccessFlags = 0;						// ���\�[�X�ւ�CPU�̃A�N�Z�X�����ɂ��Ă̐ݒ�
	buffer_desc.MiscFlags = 0;							// ���\�[�X�I�v�V�����̃t���O
	buffer_desc.StructureByteStride = 0;				// �\���̂̃T�C�Y

	D3D11_SUBRESOURCE_DATA sub_resource;
	sub_resource.pSysMem = vertex.data();	// �o�b�t�@�̒��g�̐ݒ�
	sub_resource.SysMemPitch = 0;			// texture�f�[�^���g�p����ۂɎg�p���郁���o
	sub_resource.SysMemSlicePitch = 0;		// texture�f�[�^���g�p����ۂɎg�p���郁���o

	m_nVtxSize = sizeof(Vertex3D);
	m_nVtxCount = vertex.size();

	// �o�b�t�@�쐬
	if (FAILED(DeviceManager->GetDevice()->CreateBuffer(
		&buffer_desc,								// �o�b�t�@���
		&sub_resource,								// ���\�[�X���
		&m_pVtxBuffer)))	// �쐬���ꂽ�o�b�t�@�̊i�[��
	{
		ErrorMessage->Output(ERROR_FBX_CREATE_VERTEX_BUFFER_FAILED);
	}

}
/******************************************************************************
* 
* @brief      CreateVertex
* @param[in]  vertex
* @return     HRESULT
* @author     Totsuka Kensuke
* @date       2024/05/08
* 
******************************************************************************/
void CFbxBuffer::CreateVertex(std::vector<Vertex2D> vertex)
{
	//���_�o�b�t�@�쐬
	D3D11_BUFFER_DESC buffer_desc;
	buffer_desc.ByteWidth = sizeof(Vertex2D) * vertex.size();	// �o�b�t�@�̃T�C�Y
	buffer_desc.Usage = D3D11_USAGE_DEFAULT;			// �g�p���@
	buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;	// BIND�ݒ�
	buffer_desc.CPUAccessFlags = 0;						// ���\�[�X�ւ�CPU�̃A�N�Z�X�����ɂ��Ă̐ݒ�
	buffer_desc.MiscFlags = 0;							// ���\�[�X�I�v�V�����̃t���O
	buffer_desc.StructureByteStride = 0;				// �\���̂̃T�C�Y

	D3D11_SUBRESOURCE_DATA sub_resource;
	sub_resource.pSysMem = vertex.data();	// �o�b�t�@�̒��g�̐ݒ�
	sub_resource.SysMemPitch = 0;			// texture�f�[�^���g�p����ۂɎg�p���郁���o
	sub_resource.SysMemSlicePitch = 0;		// texture�f�[�^���g�p����ۂɎg�p���郁���o

	m_nVtxSize = sizeof(Vertex2D);
	m_nVtxCount = vertex.size();

	// �o�b�t�@�쐬
	if (FAILED(DeviceManager->GetDevice()->CreateBuffer(
		&buffer_desc,								// �o�b�t�@���
		&sub_resource,								// ���\�[�X���
		&m_pVtxBuffer)))	// �쐬���ꂽ�o�b�t�@�̊i�[��
	{
		ErrorMessage->Output(ERROR_FBX_CREATE_VERTEX_BUFFER_FAILED);
	}
}

void CFbxBuffer::CreateIndex(std::vector<UINT> index)
{
	//���_�o�b�t�@�쐬
	D3D11_BUFFER_DESC buffer_desc;
	buffer_desc.ByteWidth = (UINT)sizeof(UINT) * index.size();	// �o�b�t�@�̃T�C�Y
	buffer_desc.Usage = D3D11_USAGE_DEFAULT;							// �g�p���@
	buffer_desc.BindFlags = D3D11_BIND_INDEX_BUFFER;					// BIND�ݒ�
	buffer_desc.CPUAccessFlags = 0;										// ���\�[�X�ւ�CPU�̃A�N�Z�X�����ɂ��Ă̐ݒ�
	buffer_desc.MiscFlags = 0;											// ���\�[�X�I�v�V�����̃t���O
	buffer_desc.StructureByteStride = 0;								// �\���̂̃T�C�Y

	D3D11_SUBRESOURCE_DATA sub_resource;
	sub_resource.pSysMem = index.data();							// �o�b�t�@�̒��g�̐ݒ�
	sub_resource.SysMemPitch = 0;										// texture�f�[�^���g�p����ۂɎg�p���郁���o
	sub_resource.SysMemSlicePitch = 0;									// texture�f�[�^���g�p����ۂɎg�p���郁���o

	m_nIdxSize = sizeof(UINT);
	m_nIdxCount = index.size();

	// �o�b�t�@�쐬
	if (FAILED(DeviceManager->GetDevice()->CreateBuffer(
		&buffer_desc,						// �o�b�t�@���
		&sub_resource,						// ���\�[�X���
		&m_pIdxBuffer)))		// �쐬���ꂽ�o�b�t�@�̊i�[��
	{
		ErrorMessage->Output(ERROR_FBX_CREATE_INDEX_BUFFER_FAILED);
	}
}