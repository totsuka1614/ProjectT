/******************************************************************************
* 
* @file      RenderManager.h
* @brief     描画管理クラス
* @author    Totsuka Kensuke
* @date      2024/04/28
* @note      
* @attention 
* 
******************************************************************************/
#pragma once
//インクルード
#include "main.h"
#include "RenderDefine.h"

#ifndef RenderManager
#define RenderManager CRenderManager::Get()
#endif // !RenderManager

class CRenderManager
{
public:
	CRenderManager() {};
	~CRenderManager() {};
	HRESULT Init();
	void Release();

	void StartRendering(void);
	void FinishRendering(void);
	void SetTexture(ID3D11ShaderResourceView* texture, int nNumber);
	void SetBlendState(int nBlend = BS_NONE);
	void SetCullMode(int nCull = CULLMODE_NONE);
	void SetZBuffer(bool bEnable = true);
	void SetUpViewPort(void);
	void SetUpViewPort(float x, float y, float width, float height);
public:
	static CRenderManager* Get() { return m_pRenderManager; }
private:
	HRESULT CreateSwapChain(void);
	HRESULT CreateRenderTargetView(void);
	HRESULT CreateDepthAndStencilView(void);
	HRESULT CreateTextureSampler(void);
	HRESULT CreateBlendState(void);
	HRESULT CreateRasterizerState(void);
	HRESULT CreateDepthStencilState(void);
private:
	IDXGISwapChain* m_pSwapChain;			//スワップチェーン
	ID3D11RenderTargetView* m_pRenderTargetView;	//フレームバッファ
	ID3D11DepthStencilView* m_pDepthStencilView;	//Zバッファ
	ID3D11Texture2D* m_pRenderTargetTexture;	//Zバッファ用メモリ
	ID3D11Texture2D* m_pDepthStencilTexture;	//Zバッファ用メモリ
	ID3D11SamplerState* m_pSamplerState;		//Textureサンプラー
	ID3D11ShaderResourceView* m_pShaderResourceView;   //Resourceビュー
	ID3D11DepthStencilState* m_pDSS[2];				//Z/ステンシル ステート
	ID3D11BlendState* m_pBlendState[MAX_BLENDSTATE];// ブレンド ステート
	ID3D11RasterizerState* m_pRs[MAX_CULLMODE];	// ラスタライザ ステート
	//インスタンス
	static CRenderManager* m_pRenderManager;
};