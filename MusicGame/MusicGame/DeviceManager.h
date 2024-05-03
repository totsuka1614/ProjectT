/******************************************************************************
* 
* @file      DeviceManager.h
* @brief     バックバッファクラス
* @author    Totsuka Kensuke
* @date      2023/04/27
* @note      バッファを格納する
* @attention 
* 
******************************************************************************/
#ifndef BUFFER_H
#define BUFFER_H

//インクルード
#include "main.h"
//マクロ
#ifndef DeviceManager
#define DeviceManager CDeviceManager::Get()
#endif

//クラス
class CDeviceManager
{
public:
	//コンストラクタ
	CDeviceManager() :
		m_pDevice(nullptr),
		m_pDeviceContext(nullptr)
	{
	}
	//デストラクタ
	~CDeviceManager() {};

	void Init(void);
	void Release(void);

	ID3D11Device**			GetDeviceP()	{return &m_pDevice;}
	ID3D11Device*			GetDevice()	{return m_pDevice;}
	ID3D11DeviceContext**	GetDeviceContextP() { return &m_pDeviceContext; }
	ID3D11DeviceContext*	GetDeviceContext() { return m_pDeviceContext; }
	static CDeviceManager* Get() { return m_pBuffer; }

private:

	ID3D11Device*				m_pDevice;				//デバイス
	ID3D11DeviceContext*		m_pDeviceContext;		//デバイスコンテキスト
	//インスタンス
	static CDeviceManager* m_pBuffer;
};

#endif // !BUFFER_H
