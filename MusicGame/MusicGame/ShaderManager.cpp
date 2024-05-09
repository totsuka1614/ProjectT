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
	for (int i = 0; i < eVertexShaderType::Max_Vertex_Num; i++) {
		//���_�V�F�[�_�ǂݍ���
		m_pVertexShader[i]->Create(g_cVertexShaderFilePath[i]);
	}
	for (int i = 0; i < ePixelShaderType::Max_Pixel_Num; i++) {
		//�s�N�Z���V�F�[�_�ǂݍ���
		m_pPixelShader[i]->Create(g_cPixelShaderFilePath[i]);
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
void CShaderManager::SetUp(eVertexShaderType vertex_type, ePixelShaderType pixel_type)
{
	auto deviceContext = DeviceManager->GetDeviceContext();
	// VerteXShader�APixelShader��ݒ�
	deviceContext->VSSetShader(
		m_pVertexShader[vertex_type]->GetVertexShader(),	// �g�p����VertexShder
		nullptr,
		0);									// ClassInstance�̐�
	deviceContext->PSSetShader(
		m_pPixelShader[pixel_type]->GetPixelShader(),
		nullptr,
		0);

	deviceContext->IASetInputLayout(m_pVertexShader[vertex_type]->GetInputLayout());
}
