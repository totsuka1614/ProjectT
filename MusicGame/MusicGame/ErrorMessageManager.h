/******************************************************************************
* 
* @file      ErrorMessageManager.h
* @brief     �G���[���b�Z�[�W�Ǘ��N���X
* @author    Totsuka Kensuke
* @date      2024/04/28
* @note      
* @attention 
* 
******************************************************************************/
#pragma once
//�C���N���[�h
#include "main.h"
#include "ErrorMessageDefine.h"

#ifndef ErrorMessage
#define ErrorMessage CErrorMessageManager::Get()
#endif // !ERROR_MESSAGE

class CErrorMessageManager
{
public:
	CErrorMessageManager() {};
	~CErrorMessageManager() {};

	void Output(const char*,std::string file_cell= "default");

	static CErrorMessageManager* Get() { return m_pMessageManager; }
private:
	static CErrorMessageManager* m_pMessageManager;
};