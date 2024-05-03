/******************************************************************************
* 
* @file      FpsManager.h
* @brief     fps�Ǘ��N���X
* @author    Totsuka Kensuke
* @date      2024/04/28
* @note      
* @attention 
* 
******************************************************************************/
#pragma once
//�C���N���[�h
#include "main.h"

class CFpsManager
{
public:
	CFpsManager() {};
	~CFpsManager() {};

	void Init();
	void CalculationFps();
	void CalculationSleep();
	double GetFps();
private:
	double dFps;
	LARGE_INTEGER Freq = { 0 };
	LARGE_INTEGER StartTime = { 0 };
	LARGE_INTEGER NowTime = { 0 };
	int iCount = 0;
	DWORD SleepTime = 0;
};