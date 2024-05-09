/******************************************************************************
* 
* @file      PixelShaderManager.h
* @brief     ピクセルシェーダ管理クラス
* @author    Totsuka Kensuke
* @date      2024/04/28
* @note      
* @attention 
* 
******************************************************************************/
#pragma once
//インクルード
#include "main.h"
#include "ShaderBase.h"
#include "ErrorMessageManager.h"
#include "ShaderDefine.h"

class CPixelShader : public CShaderBase
{
public:
	CPixelShader():m_pPixelShader(nullptr) {};
	~CPixelShader() { SAFE_RELEASE(m_pPixelShader); };
	//ピクセルシェーダ作成関数
	virtual bool Create(const char*);
	ID3D11PixelShader* GetPixelShader() { return m_pPixelShader; }

private:
	ID3D11PixelShader* m_pPixelShader;	//シェーダポインタ
};