/******************************************************************************
*
* @file      window.cpp
* @brief     �E�B���h�E����N���X
* @author    Totsuka Kensuke
* @date      2023/03/02
* @note
* @attention
*
******************************************************************************/

//�C���N���[�h��
#include "WindowManager.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

CWindowManager g_window;	//�C���X�^���X

CWindowManager* CWindowManager::m_pWindow = &g_window;	//����

/******************************************************************************
*
* @brief      Release
* @return     void
* @author     Totsuka Kensuke
* @date       2023/03/02
* @note       �I��
* @attention
******************************************************************************/
void CWindowManager::Release()
{
	// �E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, m_hInst);
}

// Forward declare message handler from imgui_impl_win32.cpp

/******************************************************************************
*
* @brief      WindowProc
* @param[in]  hWnd
* @param[in]  uMsg
* @param[in]  wParam
* @param[in]  lParam
* @return     LRESULT
* @author     Totsuka Kensuke
* @date       2023/03/02
* @note       Window�v���V�[�W��
* @attention
******************************************************************************/
LRESULT CALLBACK CWindowManager::WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	switch (uMsg) {
	case WM_CREATE:					//�E�B���h�E���������ꂽ
		return ReSizeWindow(hWnd, (LPCREATESTRUCT)lParam);
	case WM_DESTROY:				//�E�B���h�E�j���w��������
		PostQuitMessage(0);				//�V�X�e���ɃX���b�h�̏I����v��
		break;
	case WM_KEYDOWN:				//�L�[�{�[�h�������ꂽ
		switch (wParam) {
		case VK_ESCAPE:					// ESC�L�[�������ꂽ
			PostMessage(hWnd, WM_CLOSE, 0, 0);	// x�������ꂽ�悤�ɐU����
			return 0;
		}
		break;
	case WM_MENUCHAR:
		return MNC_CLOSE << 16;			// Alt+Enter����BEEP��}�~
	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);

}

/******************************************************************************
*
* @brief      Create
* @param[in]  hInstance
* @param[in]  hPrevInstance
* @param[in]  lpCmdLine
* @param[in]  nCmdShow
* @return     HRESULT
* @author     Totsuka Kensuke
* @date       2023/03/02
* @note       �E�B���h�E����
* @attention
******************************************************************************/
HRESULT CWindowManager::Create(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{

	WNDCLASSEX wcex = {
	sizeof(WNDCLASSEX),
	CS_CLASSDC,
	WindowProc,
	0,
	0,
	hInstance,
	LoadIcon(hInstance, MAKEINTRESOURCE(NULL)),
	LoadCursor(nullptr, IDC_ARROW),
	(HBRUSH)(COLOR_WINDOW + 1),
	nullptr,
	CLASS_NAME,
	nullptr
	};

	// COM������
	if (FAILED(CoInitializeEx(nullptr, COINIT_MULTITHREADED))) {
		MessageBox(NULL, _T("COM�̏������Ɏ��s���܂����B"), _T("error"), MB_OK);
		return -1;
	}

	// �C���X�^���X �n���h���ۑ�
	m_hInst = hInstance;

	// �E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	// �N���C�A���g�̈�T�C�Y����E�B���h�E �T�C�Y�Z�o		
	DWORD dwStyle = WS_OVERLAPPED | WS_CAPTION
		| WS_SYSMENU | WS_BORDER | WS_MINIMIZEBOX;
	DWORD dwExStyle = 0;
	RECT rc = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	AdjustWindowRectEx(&rc, dwStyle, FALSE, dwExStyle);

	// �E�B���h�E�̍쐬
	m_hWnd = CreateWindowEx(dwExStyle,
		CLASS_NAME,
		WINDOW_NAME,
		dwStyle,
		CW_USEDEFAULT,		// �E�B���h�E�̍����W
		CW_USEDEFAULT,		// �E�B���h�E�̏���W
		rc.right - rc.left,	// �E�B���h�E����
		rc.bottom - rc.top,	// �E�B���h�E�c��
		nullptr,
		nullptr,
		hInstance,
		nullptr);

	// �E�C���h�E�̕\��
	ShowWindow(m_hWnd, nCmdShow);
	UpdateWindow(m_hWnd);

	return 0;
}

/******************************************************************************
*
* @brief      ReSizeWindow
* @param[in]  hWnd
* @param[in]  lpcs
* @return     HRESULT
* @author     Totsuka Kensuke
* @date       2023/03/02
* @note       �T�C�Y�Đݒ�
* @attention
******************************************************************************/
HRESULT CWindowManager::ReSizeWindow(HWND hWnd, LPCREATESTRUCT lpcs)
{
	// �N���C�A���g�̈�T�C�Y��SCREEN_WIDTH�~SCREEN_HEIGHT�ɍĐݒ�.
	RECT rcClnt;
	GetClientRect(hWnd, &rcClnt);
	rcClnt.right -= rcClnt.left;
	rcClnt.bottom -= rcClnt.top;
	if (rcClnt.right != SCREEN_WIDTH || rcClnt.bottom != SCREEN_HEIGHT) {
		RECT rcWnd;
		GetWindowRect(hWnd, &rcWnd);
		SIZE sizeWnd;
		sizeWnd.cx = (rcWnd.right - rcWnd.left) - rcClnt.right + SCREEN_WIDTH;
		sizeWnd.cy = (rcWnd.bottom - rcWnd.top) - rcClnt.bottom + SCREEN_HEIGHT;
		SetWindowPos(hWnd, nullptr, 0, 0, sizeWnd.cx, sizeWnd.cy, SWP_NOMOVE | SWP_NOZORDER | SWP_NOOWNERZORDER);
	}

	// IME������**���ȓ��͂������Ȃ��悤��
	ImmAssociateContext(hWnd, nullptr);

	return 0;	// -1��Ԃ���CreateWindow[Ex]�����s����.
}