/******************************************************************************
* 
* @file      PixelShaderManager.h
* @brief     �s�N�Z���V�F�[�_�Ǘ��N���X
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

class CPixelShader : public CShaderBase
{
public:
	CPixelShader():m_pPixelShader(nullptr) {};
	~CPixelShader() { SAFE_RELEASE(m_pPixelShader); };
	//�s�N�Z���V�F�[�_�쐬�֐�
	virtual bool Create(const char* file_name);
	ID3D11PixelShader* GetPixelShader(PixelShaderType type) { return &m_pPixelShader[type]; }

private:
	ID3D11PixelShader* m_pPixelShader;	//�V�F�[�_�|�C���^
};