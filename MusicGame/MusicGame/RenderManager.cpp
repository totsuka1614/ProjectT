/******************************************************************************
* 
* @file      RenderManager.cpp
* @brief     �`��Ǘ��N���X
* @author    Totsuka Kensuke
* @date      2024/04/28
* @note      
* @attention 
* 
******************************************************************************/

//�C���N���[�h
#include "RenderManager.h"
#include "DeviceManager.h"
#include "WindowManager.h"
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
CRenderManager g_RenderManager;	//�C���X�^���X

CRenderManager* CRenderManager::m_pRenderManager = &g_RenderManager;  // ���݂̃o�b�t�@

/******************************************************************************
*
* @brief      Init
* @return     HRESULT
* @author     Totsuka Kensuke
* @date       2023/03/02
* @note       ������(������S_OK)
* @attention
******************************************************************************/
HRESULT CRenderManager::Init(void)
{
	m_pSwapChain = nullptr;
	m_pRenderTargetView = nullptr;
	m_pDepthStencilTexture = nullptr;
	m_pDepthStencilView = nullptr;

	HRESULT hr = S_OK;

	//�X���b�v�`�F�[���쐬		//�t�����g�o�b�t�@�A�o�b�N�o�b�t�@
	hr = CreateSwapChain();
	if (FAILED(hr))
		return hr;

	//�����_�[�^�[�Q�b�g�쐬	//�`�悷�邽�߂̃��\�[�X�̊m��
	hr = CreateRenderTargetView();
	if (FAILED(hr))
		return hr;

	//Z�o�b�t�@/�X�e���V���o�b�t�@�쐬	//���̂̑O���m��
	hr = CreateDepthAndStencilView();
	if (FAILED(hr))
		return hr;

	//�u�����h�X�e�[�g�쐬
	hr = CreateBlendState();
	if (FAILED(hr))
		return hr;

	//�r���[�|�[�g�ݒ�
	SetUpViewPort();

	//���X�^���C�U�ݒ�
	CreateRasterizerState();

	//�[�x�o�b�t�@�쐬
	CreateDepthStencilState();

	return hr;
}
/******************************************************************************
*
* @brief      Release
* @return     void
* @author     Totsuka Kensuke
* @date       2023/03/02
* @note       ���\�[�X�̊J��
* @attention
******************************************************************************/
void CRenderManager::Release(void)
{
	//�f�v�X�X�e���V���J��
	SAFE_RELEASE(m_pDepthStencilView);
	//�f�v�X�X�e���V���e�N�X�`���J��
	SAFE_RELEASE(m_pDepthStencilTexture);
	//�����_�\�^�[�Q�b�g�e�N�X�`���J��
	SAFE_RELEASE(m_pRenderTargetTexture);
	//�����_�\�^�[�Q�b�g�r���[�J��
	SAFE_RELEASE(m_pRenderTargetView);
	// �X���b�v�`�F�[�����
	SAFE_RELEASE(m_pSwapChain);
}

/******************************************************************************
*
* @brief      StartRendering
* @return     void
* @author     Totsuka Kensuke
* @date       2023/03/02
* @note       �`��J�n����
* @attention
******************************************************************************/
void CRenderManager::StartRendering(void)
{
	auto deviceContext = DeviceManager->GetDeviceContext();

	// �o�b�N�o�b�t�@���y�o�b�t�@�̃N���A
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
* @note       �`��I������
* @attention
******************************************************************************/
void CRenderManager::FinishRendering(void)
{
	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	m_pSwapChain->Present(0, 0);
}
/******************************************************************************
*
* @brief      SetBlendState
* @param[in]  nBlend
* @return     void
* @author     Totsuka Kensuke
* @date       2023/03/02
* @note       �u�����h�X�e�[�g���Z�b�g
* @attention  EBlendState���Q��
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
* @note       �J�����O�Z�b�g
* @attention  ECullMode���Q��
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
* @note       �[�x�o�b�t�@�L�������̃Z�b�g
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
* @note       �r���[�|�[�g�Z�b�e�B���O
* @attention
******************************************************************************/
void CRenderManager::SetUpViewPort(void)
{
	// �r���[�|�[�g�ݒ�
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
* @note       �r���[�|�[�g�Z�b�e�B���O(�T�C�Y�w��)
* @attention
******************************************************************************/
void CRenderManager::SetUpViewPort(float x, float y, float width, float height)
{
	// �r���[�|�[�g�ݒ�
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
* @note       �s�N�Z���V�F�[�_�ŗ��p����e�N�X�`�����Z�b�g
* @attention  nNumber�̓X���b�g�ԍ�
******************************************************************************/
void CRenderManager::SetTexture(ID3D11ShaderResourceView* texture, int nNumber)
{
	ID3D11DeviceContext* deviceContext = DeviceManager->GetDeviceContext();
	// Sampler�̐ݒ�
	deviceContext->PSSetSamplers(
		0,					// �X���b�g�ԍ�
		1,					// �T���v���[�̐�
		&m_pSamplerState);	// ID3D11SamplerState

	// PixelShader�Ŏg�p����e�N�X�`���̐ݒ�
	deviceContext->PSSetShaderResources(
		nNumber,								// �X���b�g�ԍ�
		1,								// ���\�[�X�̐�
		&texture);						// ID3D11ShaderResourceView
}

/******************************************************************************
*
* @brief      CreateDeviceAndSwapChain
* @return     HRESULT
* @author     Totsuka Kensuke
* @date       2023/03/02
* @note       �X���b�v�`�F�[���̍쐬(������S_OK)
* @attention
******************************************************************************/
HRESULT CRenderManager::CreateSwapChain(void)
{
	HRESULT hr = S_OK;

	// �f�o�C�X�A�X���b�v�`�F�[���̍쐬
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
* @note       �����_�\�^�[�Q�b�g�쐬(������S_OK)
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

	// �e�N�X�`���쐬
	hr = device->CreateTexture2D(&desc, nullptr, &m_pRenderTargetTexture);

	// �ݒ�
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	srvDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = 1;

	hr = device->CreateShaderResourceView(m_pRenderTargetTexture, &srvDesc, &m_pShaderResourceView);

	// RenderTargetView�̑ΏۂƂȂ�Buffer�̎擾
	hr = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&m_pRenderTargetTexture);
	if (FAILED(hr))
		return hr;


	// Buffer����RenderTargetView�̍쐬
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
* @note       Z�o�b�t�@���X�e���V���쐬(������S_OK)
* @attention
******************************************************************************/
HRESULT CRenderManager::CreateDepthAndStencilView()
{
	ID3D11Device* device = DeviceManager->GetDevice();
	ID3D11DeviceContext* deviceContext = DeviceManager->GetDeviceContext();

	// Z�o�b�t�@�p�e�N�X�`������
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

	// Z�o�b�t�@�^�[�Q�b�g�r���[����
	D3D11_DEPTH_STENCIL_VIEW_DESC dsvd;
	ZeroMemory(&dsvd, sizeof(dsvd));
	dsvd.Format = td.Format;
	dsvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
	hr = device->CreateDepthStencilView(m_pDepthStencilTexture,
		&dsvd, &m_pDepthStencilView);
	if (FAILED(hr)) {
		return hr;
	}

	// �e�^�[�Q�b�g�r���[�������_�[�^�[�Q�b�g�ɐݒ�
	deviceContext->OMSetRenderTargets(1, &m_pRenderTargetView, m_pDepthStencilView);

	return hr;
}
/******************************************************************************
*
* @brief      CreateTextureSampler
* @return     HRESULT
* @author     Totsuka Kensuke
* @date       2023/03/02
* @note       �e�N�X�`���T���v���쐬(������S_OK)
* @attention
******************************************************************************/
HRESULT CRenderManager::CreateTextureSampler(void)
{
	D3D11_SAMPLER_DESC sampler_desc;

	ZeroMemory(&sampler_desc, sizeof(D3D11_SAMPLER_DESC));

	sampler_desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;	// �T���v�����O���̕�ԕ��@
	// UVW�l��0.0�`1.0�͈̔͊O�ɂȂ����ꍇ�̑Ή��ݒ�
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
* @note       �u�����h�X�e�[�g�쐬(������S_OK)
* @attention
******************************************************************************/
HRESULT CRenderManager::CreateBlendState(void)
{
	ID3D11Device* device = DeviceManager->GetDevice();
	// �u�����h �X�e�[�g����
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
	// �u�����h �X�e�[�g���� (�A���t�@ �u�����h�p)
	//BlendDesc.AlphaToCoverageEnable = TRUE;
	BlendDesc.RenderTarget[0].BlendEnable = TRUE;
	device->CreateBlendState(&BlendDesc, &m_pBlendState[1]);
	// �u�����h �X�e�[�g���� (���Z�����p)
	BlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	device->CreateBlendState(&BlendDesc, &m_pBlendState[2]);
	// �u�����h �X�e�[�g���� (���Z�����p)
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
* @note       ���X�^���C�Y�쐬(������S_OK)
* @attention
******************************************************************************/
HRESULT CRenderManager::CreateRasterizerState()
{
	ID3D11Device* device = DeviceManager->GetDevice();
	ID3D11DeviceContext* deviceContext = DeviceManager->GetDeviceContext();

	// ���X�^���C�Y�ݒ�
	D3D11_RASTERIZER_DESC rd;
	ZeroMemory(&rd, sizeof(rd));
	rd.FillMode = D3D11_FILL_SOLID;
	rd.CullMode = D3D11_CULL_NONE;	// �J�����O����(���ʕ`��)
	device->CreateRasterizerState(&rd, &m_pRs[0]);
	rd.CullMode = D3D11_CULL_FRONT;	// �O�ʃJ�����O(���ʕ`��)
	device->CreateRasterizerState(&rd, &m_pRs[1]);
	rd.CullMode = D3D11_CULL_BACK;	// �w�ʃJ�����O(�\�ʕ`��)
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
* @note       �[�x�X�e���V���쐬(������S_OK)
* @attention
******************************************************************************/
HRESULT CRenderManager::CreateDepthStencilState()
{
	ID3D11Device* device = DeviceManager->GetDevice();
	// �[�x�X�e���V���X�e�[�g����
	CD3D11_DEFAULT def;
	CD3D11_DEPTH_STENCIL_DESC dsd(def);
	dsd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
	device->CreateDepthStencilState(&dsd, &m_pDSS[0]);
	CD3D11_DEPTH_STENCIL_DESC dsd2(def);
	dsd2.DepthEnable = FALSE;
	device->CreateDepthStencilState(&dsd2, &m_pDSS[1]);

	return S_OK;
}