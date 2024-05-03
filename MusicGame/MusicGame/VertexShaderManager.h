/******************************************************************************
* 
* @file      VertexShaderManager.h
* @brief     ���_�V�F�[�_�Ǘ��N���X
* @author    Totsuka Kensuke
* @date      2024/04/28
* @note      
* @attention 
* 
******************************************************************************/
#pragma once
//�C���N���[�h
#include "main.h"
#include "ShaderBase.h"
#include "ErrorMessageManager.h"
#include "ShaderDefine.h"

class CVertexShaderManager : public CShaderBase
{
public:
	CVertexShaderManager() {};
	~CVertexShaderManager() {};
	//���_�V�F�[�_�쐬�֐�
	virtual bool Create();
	//�Q�b�^�[
	ID3D11VertexShader* GetVertexShader(VertexShaderType type) { return &m_pVertexShader[type]; }
	ID3D11InputLayout* GetInputLayout() { return m_pInputLayout; }
private:
	ID3D11VertexShader* m_pVertexShader;	//�V�F�[�_�|�C���^
	ID3D11InputLayout* m_pInputLayout;
};