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
#include "PixelShaderManager.h"
#include "VertexShaderManager.h"
#include "ShaderDefine.h"
//マクロ
#ifndef ShaderManager
#define ShaderManager CShaderManager::Get();
#endif // !ShaderManager


class CShaderManager
{
public:
	CShaderManager() : m_pVertexShaderManager(nullptr), m_pPixelShaderManager(nullptr){
		m_pPixelShaderManager = new CPixelShaderManager;
		m_pVertexShaderManager = new CVertexShaderManager;
	};
	~CShaderManager() {
		SAFE_DELETE(m_pPixelShaderManager);
		SAFE_DELETE(m_pVertexShaderManager);
	};

	void Create();
	void SetUp(VertexShaderType vertex_type,PixelShaderType pixel_type);
	static CShaderManager* Get() { return m_pShaderManager; }
	ID3D11VertexShader* GetVertexShader(VertexShaderType type) { return m_pVertexShaderManager->GetVertexShader(type); }
	ID3D11PixelShader* GetPixelShader(PixelShaderType type) { return m_pPixelShaderManager->GetPixelShader(type); }
private:
	static CShaderManager* m_pShaderManager;
private:
	CVertexShaderManager* m_pVertexShaderManager;
	CPixelShaderManager* m_pPixelShaderManager;
};

