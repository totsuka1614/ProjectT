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

class CVertexShaderManager : public CShaderBase
{
public:
	CVertexShaderManager() {};
	~CVertexShaderManager() {};
	//頂点シェーダ作成関数
	virtual bool Create();
	//ゲッター
	ID3D11VertexShader* GetVertexShader(VertexShaderType type) { return &m_pVertexShader[type]; }
	ID3D11InputLayout* GetInputLayout() { return m_pInputLayout; }
private:
	ID3D11VertexShader* m_pVertexShader;	//シェーダポインタ
	ID3D11InputLayout* m_pInputLayout;
};