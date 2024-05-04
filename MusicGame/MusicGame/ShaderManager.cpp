/******************************************************************************
* 
* @file      ShaderManager.cpp
* @brief     シェーダ管理クラス
* @author    Totsuka Kensuke
* @date      2024/04/28
* @note      
* @attention 
* 
******************************************************************************/

//インクルード部
#include "ShaderManager.h"
#include "ShaderDefine.h"
#include "WindowManager.h"
#include "DeviceManager.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

CShaderManager g_shader;	//インスタンス

CShaderManager* CShaderManager::m_pShaderManager = &g_shader;	//現在

/******************************************************************************
* 
* @brief      Create
* @return     void
* @author     Totsuka Kensuke
* @date       2024/04/28
* @note       
* @attention  
* 
******************************************************************************/
void CShaderManager::Create()
{
	//頂点シェーダ読み込み
	m_pVertexShader->Create();
	
	//ピクセルシェーダ読み込み
	for (auto file_path : g_cPixelShaderFilePath) {
		m_pPixelShader->Create(file_path);
	}
}
/******************************************************************************
* 
* @brief      SetUp
* @return     void
* @author     Totsuka Kensuke
* @date       2024/04/28
* @note       描画前のshaderSetup
* @attention  
* 
******************************************************************************/
void CShaderManager::SetUp(VertexShaderType vertex_type, PixelShaderType pixel_type)
{
	auto deviceContext = DeviceManager->GetDeviceContext();
	// VerteXShader、PixelShaderを設定
	deviceContext->VSSetShader(
		m_pVertexShader->GetVertexShader(vertex_type),	// 使用するVertexShder
		nullptr,
		0);									// ClassInstanceの数
	deviceContext->PSSetShader(
		m_pPixelShader->GetPixelShader(pixel_type),
		nullptr,
		0);

	deviceContext->IASetInputLayout(m_pVertexShader->GetInputLayout());
}
