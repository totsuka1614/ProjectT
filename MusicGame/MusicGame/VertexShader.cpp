/******************************************************************************
* 
* @file      VertexShaderManager.cpp
* @brief     ���_�����[���Ǘ��N���X
* @author    Totsuka Kensuke
* @date      2024/04/28
* @note      
* @attention 
* 
******************************************************************************/

//�C���N���[�h
#include "VertexShader.h"
#include "DeviceManager.h"
#include "ShaderDefine.h"

/******************************************************************************
*
* @brief      Create
* @param[in]  device
* @param[in]  file_name
* @return     bool
* @author     Totsuka Kensuke
* @date       2023/03/02
* @note       ���_�V�F�[�_�쐬(������true)
* @attention
******************************************************************************/
bool CVertexShader::Create(const char* file_path)
{
	ID3D11Device* device = DeviceManager->GetDevice();

	//�V�F�[�_�ǂݍ���
	if (CShaderBase::Create(device, file_path) == false) {
		ErrorMessage->Output(ERROR_VERTEX_SHADER_RESOURCE_NOT_FOUND, ERROR_CELL);
	}
	//�s�N�Z���V�F�[�_�쐬
	if (FAILED(device->CreateVertexShader(m_pData, m_lSize, nullptr, &m_pVertexShader))) {
		ErrorMessage->Output(ERROR_VERTEX_SHADER_RESOURCE_CORRUPTION, ERROR_CELL);
	}

	return true;
}
