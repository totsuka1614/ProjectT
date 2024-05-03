/******************************************************************************
* 
* @file      RenderManager.cpp
* @brief     描画管理クラス
* @author    Totsuka Kensuke
* @date      2024/04/28
* @note      
* @attention 
* 
******************************************************************************/

//インクルード
#include "RenderManager.h"
#include "DeviceManager.h"
#include "WindowManager.h"
//*****************************************************************************
// グローバル変数
//*****************************************************************************
CRenderManager g_RenderManager;	//インスタンス

CRenderManager* CRenderManager::m_pRenderManager = &g_RenderManager;  // 現在のバッファ

/******************************************************************************
*
* @brief      Init
* @return     HRESULT
* @author     Totsuka Kensuke
* @date       2023/03/02
* @note       初期化(成功でS_OK)
* @attention
******************************************************************************/
HRESULT CRenderManager::Init(void)
{
	m_pSwapChain = nullptr;
	m_pRenderTargetView = nullptr;
	m_pDepthStencilTexture = nullptr;
	m_pDepthStencilView = nullptr;

	HRESULT hr = S_OK;

	//スワップチェーン作成		//フロントバッファ、バックバッファ
	hr = CreateSwapChain();
	if (FAILED(hr))
		return hr;

	//レンダーターゲット作成	//描画するためのリソースの確保
	hr = CreateRenderTargetView();
	if (FAILED(hr))
		return hr;

	//Zバッファ/ステンシルバッファ作成	//物体の前後を知る
	hr = CreateDepthAndStencilView();
	if (FAILED(hr))
		return hr;

	//ブレンドステート作成
	hr = CreateBlendState();
	if (FAILED(hr))
		return hr;

	//ビューポート設定
	SetUpViewPort();

	//ラスタライザ設定
	CreateRasterizerState();

	//深度バッファ作成
	CreateDepthStencilState();

	return hr;
}
/******************************************************************************
*
* @brief      Release
* @return     void
* @author     Totsuka Kensuke
* @date       2023/03/02
* @note       リソースの開放
* @attention
******************************************************************************/
void CRenderManager::Release(void)
{
	//デプスステンシル開放
	SAFE_RELEASE(m_pDepthStencilView);
	//デプスステンシルテクスチャ開放
	SAFE_RELEASE(m_pDepthStencilTexture);
	//レンダ―ターゲットテクスチャ開放
	SAFE_RELEASE(m_pRenderTargetTexture);
	//レンダ―ターゲットビュー開放
	SAFE_RELEASE(m_pRenderTargetView);
	// スワップチェーン解放
	SAFE_RELEASE(m_pSwapChain);
}

/******************************************************************************
*
* @brief      StartRendering
* @return     void
* @author     Totsuka Kensuke
* @date       2023/03/02
* @note       描画開始処理
* @attention
******************************************************************************/
void CRenderManager::StartRendering(void)
{
	auto deviceContext = DeviceManager->GetDeviceContext();

	// バックバッファ＆Ｚバッファのクリア
	float ClearColor[4] = { 0.117647f, 0.254902f, 0.352941f, 1.0f };
	deviceContext->ClearRenderTargetView(m_pRenderTargetView, ClearColor);
	deviceContext->ClearDepthStencilView(m_pDepthStencilView,
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

/******************************************************************************
*
* @brief      FinishRendering
* @return     void
* @author     Totsuka Kensuke
* @date       2023/03/02
* @note       描画終了処理
* @attention
******************************************************************************/
void CRenderManager::FinishRendering(void)
{
	// バックバッファとフロントバッファの入れ替え
	m_pSwapChain->Present(0, 0);
}
/******************************************************************************
*
* @brief      SetBlendState
* @param[in]  nBlend
* @return     void
* @author     Totsuka Kensuke
* @date       2023/03/02
* @note       ブレンドステートをセット
* @attention  EBlendStateを参照
******************************************************************************/
void CRenderManager::SetBlendState(int nBlend)
{
	if (nBlend >= 0 && nBlend < MAX_BLENDSTATE) {
		float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
		DeviceManager->GetDeviceContext()->OMSetBlendState(m_pBlendState[nBlend], blendFactor, 0xffffffff);
	}
}

/******************************************************************************
*
* @brief      SetCullMode
* @param[in]  nCull
* @return     void
* @author     Totsuka Kensuke
* @date       2023/03/02
* @note       カリングセット
* @attention  ECullModeを参照
******************************************************************************/
void CRenderManager::SetCullMode(int nCull)
{
	if (nCull >= 0 && nCull < MAX_CULLMODE) {
		DeviceManager->GetDeviceContext()->RSSetState(m_pRs[nCull]);
	}
}

/******************************************************************************
*
* @brief      SetZBuffer
* @param[in]  bEnable
* @return     void
* @author     Totsuka Kensuke
* @date       2023/03/02
* @note       深度バッファ有効無効のセット
* @attention
******************************************************************************/
void CRenderManager::SetZBuffer(bool bEnable)
{
	DeviceManager->GetDeviceContext()->OMSetDepthStencilState((bEnable) ? nullptr : m_pDSS[1], 0);
}

/******************************************************************************
*
* @brief      SetUpViewPort
* @return     void
* @author     Totsuka Kensuke
* @date       2023/03/02
* @note       ビューポートセッティング
* @attention
******************************************************************************/
void CRenderManager::SetUpViewPort(void)
{
	// ビューポート設定
	D3D11_VIEWPORT vp;
	vp.Width = (float)SCREEN_WIDTH;
	vp.Height = (float)SCREEN_HEIGHT;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	DeviceManager->GetDeviceContext()->RSSetViewports(1, &vp);
}
/******************************************************************************
*
* @brief      SetUpViewPort
* @param[in]  x
* @param[in]  y
* @param[in]  width
* @param[in]  height
* @return     void
* @author     Totsuka Kensuke
* @date       2023/03/02
* @note       ビューポートセッティング(サイズ指定)
* @attention
******************************************************************************/
void CRenderManager::SetUpViewPort(float x, float y, float width, float height)
{
	// ビューポート設定
	D3D11_VIEWPORT vp;
	vp.Width = (float)width;
	vp.Height = (float)height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = (float)x;
	vp.TopLeftY = (float)y;
	DeviceManager->GetDeviceContext()->RSSetViewports(1, &vp);
}
/******************************************************************************
*
* @brief      SetTexture
* @param[in]  texture
* @param[in]  nNumber
* @return     void
* @author     Totsuka Kensuke
* @date       2023/03/02
* @note       ピクセルシェーダで利用するテクスチャをセット
* @attention  nNumberはスロット番号
******************************************************************************/
void CRenderManager::SetTexture(ID3D11ShaderResourceView* texture, int nNumber)
{
	ID3D11DeviceContext* deviceContext = DeviceManager->GetDeviceContext();
	// Samplerの設定
	deviceContext->PSSetSamplers(
		0,					// スロット番号
		1,					// サンプラーの数
		&m_pSamplerState);	// ID3D11SamplerState

	// PixelShaderで使用するテクスチャの設定
	deviceContext->PSSetShaderResources(
		nNumber,								// スロット番号
		1,								// リソースの数
		&texture);						// ID3D11ShaderResourceView
}

/******************************************************************************
*
* @brief      CreateDeviceAndSwapChain
* @return     HRESULT
* @author     Totsuka Kensuke
* @date       2023/03/02
* @note       スワップチェーンの作成(成功でS_OK)
* @attention
******************************************************************************/
HRESULT CRenderManager::CreateSwapChain(void)
{
	HRESULT hr = S_OK;

	// デバイス、スワップチェーンの作成
	DXGI_SWAP_CHAIN_DESC scd;
	ZeroMemory(&scd, sizeof(scd));
	scd.BufferCount = 1;
	scd.BufferDesc.Width = SCREEN_WIDTH;
	scd.BufferDesc.Height = SCREEN_HEIGHT;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.BufferDesc.RefreshRate.Numerator = 60;
	scd.BufferDesc.RefreshRate.Denominator = 1;
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.OutputWindow = WindowManager->GetWindowHandle();
	scd.SampleDesc.Count = 1;
	scd.SampleDesc.Quality = 0;
	scd.Windowed = true;

	D3D_FEATURE_LEVEL featureLevels[] = {
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1,
	};

	hr = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE,
		nullptr, 0, featureLevels, _countof(featureLevels), D3D11_SDK_VERSION, &scd,
		&m_pSwapChain, DeviceManager->GetDeviceP(), nullptr, DeviceManager->GetDeviceContextP());
	if (FAILED(hr)) {
		return hr;
	}

	return hr;
}
/******************************************************************************
*
* @brief      CreateRenderTargetView
* @return     HRESULT
* @author     Totsuka Kensuke
* @date       2023/03/02
* @note       レンダ―ターゲット作成(成功でS_OK)
* @attention
******************************************************************************/
HRESULT CRenderManager::CreateRenderTargetView(void)
{
	HRESULT hr = S_OK;

	ID3D11Device* device = DeviceManager->GetDevice();

	D3D11_TEXTURE2D_DESC desc = {};
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.Width = SCREEN_WIDTH;
	desc.Height = SCREEN_HEIGHT;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.SampleDesc.Count = 1;

	desc.BindFlags |= D3D11_BIND_RENDER_TARGET;

	// テクスチャ作成
	hr = device->CreateTexture2D(&desc, nullptr, &m_pRenderTargetTexture);

	// 設定
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	srvDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = 1;

	hr = device->CreateShaderResourceView(m_pRenderTargetTexture, &srvDesc, &m_pShaderResourceView);

	// RenderTargetViewの対象となるBufferの取得
	hr = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&m_pRenderTargetTexture);
	if (FAILED(hr))
		return hr;


	// BufferからRenderTargetViewの作成
	hr = device->CreateRenderTargetView(m_pRenderTargetTexture, NULL, &m_pRenderTargetView);
	if (FAILED(hr))
		return hr;


	return hr;
}
/******************************************************************************
*
* @brief      CreateDepthAndStencilView
* @return     HRESULT
* @author     Totsuka Kensuke
* @date       2023/03/02
* @note       Zバッファ＆ステンシル作成(成功でS_OK)
* @attention
******************************************************************************/
HRESULT CRenderManager::CreateDepthAndStencilView()
{
	ID3D11Device* device = DeviceManager->GetDevice();
	ID3D11DeviceContext* deviceContext = DeviceManager->GetDeviceContext();

	// Zバッファ用テクスチャ生成
	D3D11_TEXTURE2D_DESC td;
	ZeroMemory(&td, sizeof(td));
	td.Width = SCREEN_WIDTH;
	td.Height = SCREEN_HEIGHT;
	td.MipLevels = 1;
	td.ArraySize = 1;
	td.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	td.SampleDesc.Count = 1;
	td.SampleDesc.Quality = 0;
	td.Usage = D3D11_USAGE_DEFAULT;
	td.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	HRESULT hr = device->CreateTexture2D(&td, nullptr, &m_pDepthStencilTexture);
	if (FAILED(hr)) {
		return hr;
	}

	// Zバッファターゲットビュー生成
	D3D11_DEPTH_STENCIL_VIEW_DESC dsvd;
	ZeroMemory(&dsvd, sizeof(dsvd));
	dsvd.Format = td.Format;
	dsvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
	hr = device->CreateDepthStencilView(m_pDepthStencilTexture,
		&dsvd, &m_pDepthStencilView);
	if (FAILED(hr)) {
		return hr;
	}

	// 各ターゲットビューをレンダーターゲットに設定
	deviceContext->OMSetRenderTargets(1, &m_pRenderTargetView, m_pDepthStencilView);

	return hr;
}
/******************************************************************************
*
* @brief      CreateTextureSampler
* @return     HRESULT
* @author     Totsuka Kensuke
* @date       2023/03/02
* @note       テクスチャサンプラ作成(成功でS_OK)
* @attention
******************************************************************************/
HRESULT CRenderManager::CreateTextureSampler(void)
{
	D3D11_SAMPLER_DESC sampler_desc;

	ZeroMemory(&sampler_desc, sizeof(D3D11_SAMPLER_DESC));

	sampler_desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;	// サンプリング時の補間方法
	// UVW値が0.0～1.0の範囲外になった場合の対応設定
	sampler_desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampler_desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampler_desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	
	if (FAILED(DeviceManager->GetDevice()->CreateSamplerState(&sampler_desc, &m_pSamplerState)))
	{
		return false;
	}

	return true;
}
/******************************************************************************
*
* @brief      CreateBlendState
* @return     HRESULT
* @author     Totsuka Kensuke
* @date       2023/03/02
* @note       ブレンドステート作成(成功でS_OK)
* @attention
******************************************************************************/
HRESULT CRenderManager::CreateBlendState(void)
{
	ID3D11Device* device = DeviceManager->GetDevice();
	// ブレンド ステート生成
	D3D11_BLEND_DESC BlendDesc;
	ZeroMemory(&BlendDesc, sizeof(BlendDesc));
	BlendDesc.AlphaToCoverageEnable = FALSE;
	BlendDesc.IndependentBlendEnable = FALSE;
	BlendDesc.RenderTarget[0].BlendEnable = FALSE;
	BlendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	BlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	BlendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	BlendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	BlendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	BlendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	BlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	device->CreateBlendState(&BlendDesc, &m_pBlendState[0]);
	// ブレンド ステート生成 (アルファ ブレンド用)
	//BlendDesc.AlphaToCoverageEnable = TRUE;
	BlendDesc.RenderTarget[0].BlendEnable = TRUE;
	device->CreateBlendState(&BlendDesc, &m_pBlendState[1]);
	// ブレンド ステート生成 (加算合成用)
	BlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	device->CreateBlendState(&BlendDesc, &m_pBlendState[2]);
	// ブレンド ステート生成 (減算合成用)
	BlendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_REV_SUBTRACT;
	device->CreateBlendState(&BlendDesc, &m_pBlendState[3]);
	SetBlendState(BS_ALPHABLEND);

	return S_OK;
}

/******************************************************************************
*
* @brief      CreateRasterizerState
* @return     HRESULT
* @author     Totsuka Kensuke
* @date       2023/03/02
* @note       ラスタライズ作成(成功でS_OK)
* @attention
******************************************************************************/
HRESULT CRenderManager::CreateRasterizerState()
{
	ID3D11Device* device = DeviceManager->GetDevice();
	ID3D11DeviceContext* deviceContext = DeviceManager->GetDeviceContext();

	// ラスタライズ設定
	D3D11_RASTERIZER_DESC rd;
	ZeroMemory(&rd, sizeof(rd));
	rd.FillMode = D3D11_FILL_SOLID;
	rd.CullMode = D3D11_CULL_NONE;	// カリング無し(両面描画)
	device->CreateRasterizerState(&rd, &m_pRs[0]);
	rd.CullMode = D3D11_CULL_FRONT;	// 前面カリング(裏面描画)
	device->CreateRasterizerState(&rd, &m_pRs[1]);
	rd.CullMode = D3D11_CULL_BACK;	// 背面カリング(表面描画)
	device->CreateRasterizerState(&rd, &m_pRs[2]);
	deviceContext->RSSetState(m_pRs[2]);

	return S_OK;
}

/******************************************************************************
*
* @brief      CreateDepthStencilState
* @return     HRESULT
* @author     Totsuka Kensuke
* @date       2023/03/02
* @note       深度ステンシル作成(成功でS_OK)
* @attention
******************************************************************************/
HRESULT CRenderManager::CreateDepthStencilState()
{
	ID3D11Device* device = DeviceManager->GetDevice();
	// 深度ステンシルステート生成
	CD3D11_DEFAULT def;
	CD3D11_DEPTH_STENCIL_DESC dsd(def);
	dsd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
	device->CreateDepthStencilState(&dsd, &m_pDSS[0]);
	CD3D11_DEPTH_STENCIL_DESC dsd2(def);
	dsd2.DepthEnable = FALSE;
	device->CreateDepthStencilState(&dsd2, &m_pDSS[1]);

	return S_OK;
}