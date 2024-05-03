/******************************************************************************
*
* @file      Window.h
* @brief     �E�B���h�E�N���X
* @author    Totsuka Kensuke
* @date      2023/04/27
* @note
* @attention
*
******************************************************************************/
#ifndef WINDOW_H
#define WINDOW_H
//�C���N���[�h��
#include "main.h"

//�}�N��
#ifndef WindowManager
#define WindowManager CWindowManager::Get()
#endif //!WindowManager
#define CLASS_NAME		_T("AppClass")		// �E�C���h�E�̃N���X��
#define WINDOW_NAME		_T("���Q�[����")	// �E�C���h�E�̃L���v�V������
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
	HWND			m_hWnd;		// ���C�� �E�B���h�E �n���h��
	HINSTANCE		m_hInst;	// �C���X�^���X �n���h��

};

#endif
