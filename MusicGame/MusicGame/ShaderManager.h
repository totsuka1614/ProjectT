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
	CShaderManager() {
		*m_pVertexShader = new CVertexShader[eVertexShaderType::Max_Vertex_Num];
		*m_pPixelShader = new CPixelShader[ePixelShaderType::Max_Pixel_Num];
	};
	~CShaderManager() {};

	void Create();
	void SetUp(eVertexShaderType vertex_type, ePixelShaderType pixel_type);
	static CShaderManager* Get() { return m_pShaderManager; }
	ID3D11VertexShader* GetVertexShader(eVertexShaderType type) { return m_pVertexShader[type]->GetVertexShader(); }
	ID3D11PixelShader* GetPixelShader(ePixelShaderType type) { return m_pPixelShader[type]->GetPixelShader(); }
private:
	static CShaderManager* m_pShaderManager;
private:
	CVertexShader* m_pVertexShader[eVertexShaderType::Max_Vertex_Num];
	CPixelShader* m_pPixelShader[ePixelShaderType::Max_Pixel_Num];
};