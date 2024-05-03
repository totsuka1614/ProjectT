/******************************************************************************
* 
* @file      ErrorMessageManager.cpp
* @brief     �G���[���b�Z�[�W�Ǘ��N���X
* @author    Totsuka Kensuke
* @date      2024/04/28
* @note      
* @attention 
* 
******************************************************************************/

//�C���N���[�h
#include "ErrorMessageManager.h"

CErrorMessageManager g_error;	//�C���X�^���X

CErrorMessageManager* CErrorMessageManager::m_pMessageManager = &g_error;	//����

void CErrorMessageManager::Output(const char* error,std::string file)
{
	MessageBox(NULL, _T(error), _T(file.data()), MB_OK);
}