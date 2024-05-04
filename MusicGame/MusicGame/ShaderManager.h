/******************************************************************************
* 
* @file      ShaderManager.h
* @brief     シェーダ管理クラス
* @author    Totsuka Kensuke
* @date      2024/04/28
* @note      
* @attention 
* 
******************************************************************************/
#pragma once
//インクルード
#include "main.h"
#include "PixelShader.h"
#include "VertexShader.h"
#include "ShaderDefine.h"
//マクロ
#ifndef ShaderManager
#define ShaderManager CShaderManager::Get()
#endif // !ShaderManager


class CShaderManager
{
public:
	CShaderManager() : m_pVertexShader(nullptr), m_pPixelShader(nullptr){
		m_pPixelShader = new CPixelShader;
		m_pVertexShader = new CVertexShader;
	};
	~CShaderManager() {
		SAFE_DELETE(m_pPixelShader);
		SAFE_DELETE(m_pVertexShader);
	};

	void Create();
	void SetUp(VertexShaderType vertex_type,PixelShaderType pixel_type);
	static CShaderManager* Get() { return m_pShaderManager; }
	ID3D11VertexShader* GetVertexShader(VertexShaderType type) { return m_pVertexShader->GetVertexShader(type); }
	ID3D11PixelShader* GetPixelShader(PixelShaderType type) { return m_pPixelShader->GetPixelShader(type); }
private:
	static CShaderManager* m_pShaderManager;
private:
	CVertexShader* m_pVertexShader;
	CPixelShader* m_pPixelShader;
};

