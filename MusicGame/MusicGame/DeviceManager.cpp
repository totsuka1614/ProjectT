/******************************************************************************
* 
* @file      DeviceManager.cpp
* @brief     バッファが色々ある
* @author    Totsuka Kensuke
* @date      2023/03/02
* @note      
* @attention 
* 
******************************************************************************/
#include "DeviceManager.h"
#include "WindowManager.h"
#include "main.h"

#pragma comment(lib, "d3d11")

//*****************************************************************************
// グローバル変数
//*****************************************************************************
CDeviceManager g_DeviceManager;	//インスタンス

CDeviceManager* CDeviceManager::m_pBuffer = &g_DeviceManager;  // 現在のバッファ

/******************************************************************************
* 
* @brief      Init
* @return     HRESULT
* @author     Totsuka Kensuke
* @date       2023/03/02
* @note       初期化(成功でS_OK)
* @attention  
******************************************************************************/
void CDeviceManager::Init(void)
{
	m_pDevice = nullptr;
	m_pDeviceContext = nullptr; 
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
void CDeviceManager::Release(void)
{
	if (m_pDeviceContext) {
		m_pDeviceContext->OMSetRenderTargets(0, nullptr, nullptr);
	}
	// デバイス コンテキストの開放
	SAFE_RELEASE(m_pDeviceContext);
	// デバイスの開放
	SAFE_RELEASE(m_pDevice);
}