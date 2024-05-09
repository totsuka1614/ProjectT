/******************************************************************************
*
* @file      pixel.cpp
* @brief     �s�N�Z���V�F�[�_
* @author    Totsuka Kensuke
* @date      2023/03/02
* @note
* @attention
*
******************************************************************************/
#include "PixelShader.h"
#include "DeviceManager.h"
/******************************************************************************
*
* @brief      Create
* @param[in]  device
* @param[in]  file_name
* @return     bool
* @author     Totsuka Kensuke
* @date       2023/03/02
* @note       �s�N�Z���V�F�[�_���쐬(������true)
* @attention
******************************************************************************/
bool CPixelShader::Create(const char* file_name)
{
	ID3D11Device* device = DeviceManager->GetDevice();

		//�V�F�[�_�ǂݍ���
		if (CShaderBase::Create(device, file_name) == false)
		{
			ErrorMessage->Output(ERROR_PIXEL_SHADER_RESOURCE_NOT_FOUND, ERROR_CELL);
		}
		//�s�N�Z���V�F�[�_�쐬
		if (FAILED(device->CreatePixelShader(m_pData, m_lSize, nullptr, &m_pPixelShader)))
		{
			ErrorMessage->Output(ERROR_PIXEL_SHADER_RESOURCE_CORRUPTION, ERROR_CELL);
		}


	return true;
}
