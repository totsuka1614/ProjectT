/******************************************************************************
*
* @file      pixel.cpp
* @brief     ピクセルシェーダ
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
* @note       ピクセルシェーダを作成(成功でtrue)
* @attention
******************************************************************************/
bool CPixelShader::Create(const char* file_name)
{
	ID3D11Device* device = DeviceManager->GetDevice();

		//シェーダ読み込み
		if (CShaderBase::Create(device, file_name) == false)
		{
			ErrorMessage->Output(ERROR_PIXEL_SHADER_RESOURCE_NOT_FOUND, ERROR_CELL);
		}
		//ピクセルシェーダ作成
		if (FAILED(device->CreatePixelShader(m_pData, m_lSize, nullptr, &m_pPixelShader)))
		{
			ErrorMessage->Output(ERROR_PIXEL_SHADER_RESOURCE_CORRUPTION, ERROR_CELL);
		}


	return true;
}
