/******************************************************************************
*
* @file      Window.h
* @brief     ウィンドウクラス
* @author    Totsuka Kensuke
* @date      2023/04/27
* @note
* @attention
*
******************************************************************************/
#ifndef WINDOW_H
#define WINDOW_H
//インクルード部
#include "main.h"

//マクロ
#ifndef WindowManager
#define WindowManager CWindowManager::Get()
#endif //!WindowManager
#define CLASS_NAME		_T("AppClass")		// ウインドウのクラス名
#define WINDOW_NAME		_T("音ゲー作るよ")	// ウインドウのキャプション名
class CWindowManager
{
public:
	CWindowManager() {};
	~CWindowManager() {};
	void Release(void);

	HRESULT Create(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow);
	static CWindowManager* Get() { return m_pWindow; }
	HWND GetWindowHandle() { return m_hWnd; }
private:
	static LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static HRESULT ReSizeWindow(HWND hWnd, LPCREATESTRUCT lpcs);
private:

	static CWindowManager* m_pWindow;
	HWND			m_hWnd;		// メイン ウィンドウ ハンドル
	HINSTANCE		m_hInst;	// インスタンス ハンドル

};

#endif
