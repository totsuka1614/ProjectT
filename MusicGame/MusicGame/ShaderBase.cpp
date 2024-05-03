/******************************************************************************
*
* @file      shaderbase.cpp
* @brief     �V�F�[�_�ׁ[�X�N���X
* @author    Totsuka Kensuke
* @date      2023/03/02
* @note
* @attention
*
******************************************************************************/
#include <stdio.h>
#include "ShaderBase.h"

/******************************************************************************
*
* @brief      Create
* @param[in]  device
* @param[in]  file_name
* @return     bool
* @author     Totsuka Kensuke
* @date       2023/03/02
* @note       �t�@�C���������true
* @attention
******************************************************************************/
bool CShaderBase::Create(ID3D11Device* device, const char* file_name)
{
	m_lSize = LoadFile(file_name);
	if (m_lSize == 0)
	{
		return false;
	}
	return true;
}

/******************************************************************************
*
* @brief      LoadFile
* @param[in]  file_name
* @return     int
* @author     Totsuka Kensuke
* @date       2023/03/02
* @note       �V�F�[�_�t�@�C�������[�h
* @attention
******************************************************************************/
int CShaderBase::LoadFile(const char* file_name)
{
	// �V�F�[�_�t�@�C���ǂݍ���
	FILE* fp = nullptr;
	fopen_s(&fp, file_name, "rb");

	//�t�@�C����������Ȃ�
	if (fp == nullptr)
	{
		return 0;
	}
	//�f�[�^�T�C�Y�擾
	fseek(fp, 0, SEEK_END);		//�f�[�^�����Ɉړ�
	m_lSize = ftell(fp);			//�T�C�Y�擾
	fseek(fp, 0, SEEK_SET);		//�擪�֖߂�
	m_pData = new char[m_lSize];

	//���[�h
	fread_s(m_pData, m_lSize, m_lSize, 1, fp);
	fclose(fp);

	return m_lSize;
}
