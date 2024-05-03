/******************************************************************************
* 
* @file      ShaderBase.h
* @brief     �V�F�[�_���N���X
* @author    Totsuka Kensuke
* @date      2024/04/28
* @note      
* @attention 
* 
******************************************************************************/
#pragma once
//�C���N���[�h
#include "main.h"

class CShaderBase
{
public:
	CShaderBase() : m_lSize(0), m_pData(nullptr) {}
	virtual ~CShaderBase() { SAFE_DELETE(m_pData); };

	bool Create(ID3D11Device* device, const char* file_name);

	//�Q�b�^�[
	char* GetData() { return m_pData; }
	long GetSize() { return m_lSize; }

private:
	int LoadFile(const char* file_name);
protected:
	char* m_pData;
	long m_lSize;
};