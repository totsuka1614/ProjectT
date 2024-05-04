/******************************************************************************
* 
* @file      ShaderManager.cpp
* @brief     �V�F�[�_�Ǘ��N���X
* @author    Totsuka Kensuke
* @date      2024/04/28
* @note      
* @attention 
* 
******************************************************************************/

//�C���N���[�h��
#include "ShaderManager.h"
#include "ShaderDefine.h"
#include "WindowManager.h"
#include "DeviceManager.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

CShaderManager g_shader;	//�C���X�^���X

CShaderManager* CShaderManager::m_pShaderManager = &g_shader;	//����

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
	//���_�V�F�[�_�ǂݍ���
	m_pVertexShader->Create();
	
	//�s�N�Z���V�F�[�_�ǂݍ���
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
* @note       �`��O��shaderSetup
* @attention  
* 
******************************************************************************/
void CShaderManager::SetUp(VertexShaderType vertex_type, PixelShaderType pixel_type)
{
	auto deviceContext = DeviceManager->GetDeviceContext();
	// VerteXShader�APixelShader��ݒ�
	deviceContext->VSSetShader(
		m_pVertexShader->GetVertexShader(vertex_type),	// �g�p����VertexShder
		nullptr,
		0);									// ClassInstance�̐�
	deviceContext->PSSetShader(
		m_pPixelShader->GetPixelShader(pixel_type),
		nullptr,
		0);

	deviceContext->IASetInputLayout(m_pVertexShader->GetInputLayout());
}
