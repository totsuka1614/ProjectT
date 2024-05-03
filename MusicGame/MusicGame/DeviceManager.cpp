/******************************************************************************
* 
* @file      DeviceManager.cpp
* @brief     �o�b�t�@���F�X����
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
// �O���[�o���ϐ�
//*****************************************************************************
CDeviceManager g_DeviceManager;	//�C���X�^���X

CDeviceManager* CDeviceManager::m_pBuffer = &g_DeviceManager;  // ���݂̃o�b�t�@

/******************************************************************************
* 
* @brief      Init
* @return     HRESULT
* @author     Totsuka Kensuke
* @date       2023/03/02
* @note       ������(������S_OK)
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
* @note       ���\�[�X�̊J��
* @attention  
******************************************************************************/
void CDeviceManager::Release(void)
{
	if (m_pDeviceContext) {
		m_pDeviceContext->OMSetRenderTargets(0, nullptr, nullptr);
	}
	// �f�o�C�X �R���e�L�X�g�̊J��
	SAFE_RELEASE(m_pDeviceContext);
	// �f�o�C�X�̊J��
	SAFE_RELEASE(m_pDevice);
}