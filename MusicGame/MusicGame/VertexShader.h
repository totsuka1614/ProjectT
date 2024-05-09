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

class CVertexShader : public CShaderBase
{
public:
	CVertexShader() {};
	~CVertexShader() {};
	//���_�V�F�[�_�쐬�֐�
	virtual bool Create(const char*);
	//�Q�b�^�[
	ID3D11VertexShader* GetVertexShader() { return m_pVertexShader; }
	ID3D11InputLayout* GetInputLayout() { return m_pInputLayout; }
private:
	ID3D11VertexShader* m_pVertexShader;	//�V�F�[�_�|�C���^
	ID3D11InputLayout* m_pInputLayout;
};