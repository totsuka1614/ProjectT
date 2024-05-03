/******************************************************************************
* 
* @file      DeviceManager.h
* @brief     �o�b�N�o�b�t�@�N���X
* @author    Totsuka Kensuke
* @date      2023/04/27
* @note      �o�b�t�@���i�[����
* @attention 
* 
******************************************************************************/
#ifndef BUFFER_H
#define BUFFER_H

//�C���N���[�h
#include "main.h"
//�}�N��
#ifndef DeviceManager
#define DeviceManager CDeviceManager::Get()
#endif

//�N���X
class CDeviceManager
{
public:
	//�R���X�g���N�^
	CDeviceManager() :
		m_pDevice(nullptr),
		m_pDeviceContext(nullptr)
	{
	}
	//�f�X�g���N�^
	~CDeviceManager() {};

	void Init(void);
	void Release(void);

	ID3D11Device**			GetDeviceP()	{return &m_pDevice;}
	ID3D11Device*			GetDevice()	{return m_pDevice;}
	ID3D11DeviceContext**	GetDeviceContextP() { return &m_pDeviceContext; }
	ID3D11DeviceContext*	GetDeviceContext() { return m_pDeviceContext; }
	static CDeviceManager* Get() { return m_pBuffer; }

private:

	ID3D11Device*				m_pDevice;				//�f�o�C�X
	ID3D11DeviceContext*		m_pDeviceContext;		//�f�o�C�X�R���e�L�X�g
	//�C���X�^���X
	static CDeviceManager* m_pBuffer;
};

#endif // !BUFFER_H
