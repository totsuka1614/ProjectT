/******************************************************************************
* 
* @file      ErrorMessageManager.cpp
* @brief     エラーメッセージ管理クラス
* @author    Totsuka Kensuke
* @date      2024/04/28
* @note      
* @attention 
* 
******************************************************************************/

//インクルード
#include "ErrorMessageManager.h"

CErrorMessageManager g_error;	//インスタンス

CErrorMessageManager* CErrorMessageManager::m_pMessageManager = &g_error;	//現在

void CErrorMessageManager::Output(const char* error,std::string file)
{
	MessageBox(NULL, _T(error), _T(file.data()), MB_OK);
}
