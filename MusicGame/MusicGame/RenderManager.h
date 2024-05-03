/******************************************************************************
* 
* @file      RenderManager.h
* @brief     �`��Ǘ��N���X
* @author    Totsuka Kensuke
* @date      2024/04/28
* @note      
* @attention 
* 
******************************************************************************/
#pragma once
//�C���N���[�h
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
	IDXGISwapChain* m_pSwapChain;			//�X���b�v�`�F�[��
	ID3D11RenderTargetView* m_pRenderTargetView;	//�t���[���o�b�t�@
	ID3D11DepthStencilView* m_pDepthStencilView;	//Z�o�b�t�@
	ID3D11Texture2D* m_pRenderTargetTexture;	//Z�o�b�t�@�p������
	ID3D11Texture2D* m_pDepthStencilTexture;	//Z�o�b�t�@�p������
	ID3D11SamplerState* m_pSamplerState;		//Texture�T���v���[
	ID3D11ShaderResourceView* m_pShaderResourceView;   //Resource�r���[
	ID3D11DepthStencilState* m_pDSS[2];				//Z/�X�e���V�� �X�e�[�g
	ID3D11BlendState* m_pBlendState[MAX_BLENDSTATE];// �u�����h �X�e�[�g
	ID3D11RasterizerState* m_pRs[MAX_CULLMODE];	// ���X�^���C�U �X�e�[�g
	//�C���X�^���X
	static CRenderManager* m_pRenderManager;
};