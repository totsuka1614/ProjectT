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
	for (int i = 0; i < eVertexShaderType::Max_Vertex_Num; i++) {
		//頂点シェーダ読み込み
		m_pVertexShader[i]->Create(g_cVertexShaderFilePath[i]);
	}
	for (int i = 0; i < ePixelShaderType::Max_Pixel_Num; i++) {
		//ピクセルシェーダ読み込み
		m_pPixelShader[i]->Create(g_cPixelShaderFilePath[i]);
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
void CShaderManager::SetUp(eVertexShaderType vertex_type, ePixelShaderType pixel_type)
{
	auto deviceContext = DeviceManager->GetDeviceContext();
	// VerteXShader、PixelShaderを設定
	deviceContext->VSSetShader(
		m_pVertexShader[vertex_type]->GetVertexShader(),	// 使用するVertexShder
		nullptr,
		0);									// ClassInstanceの数
	deviceContext->PSSetShader(
		m_pPixelShader[pixel_type]->GetPixelShader(),
		nullptr,
		0);

	deviceContext->IASetInputLayout(m_pVertexShader[vertex_type]->GetInputLayout());
}
