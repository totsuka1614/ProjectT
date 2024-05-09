/******************************************************************************
* 
* @file      VertexShaderManager.h
* @brief     頂点シェーダ管理クラス
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

class CVertexShader : public CShaderBase
{
public:
	CVertexShader() {};
	~CVertexShader() {};
	//頂点シェーダ作成関数
	virtual bool Create(const char*);
	//ゲッター
	ID3D11VertexShader* GetVertexShader() { return m_pVertexShader; }
	ID3D11InputLayout* GetInputLayout() { return m_pInputLayout; }
private:
	ID3D11VertexShader* m_pVertexShader;	//シェーダポインタ
	ID3D11InputLayout* m_pInputLayout;
};