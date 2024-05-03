/******************************************************************************
* 
* @file      main.cpp
* @brief     ���C��
* @author    Totsuka Kensuke
* @date      2024/04/24
* 
******************************************************************************/
#include "main.h"
#include "FpsManager.h"
#include "WindowManager.h"
#include "ErrorMessageManager.h"
#include "DeviceManager.h"
#include "ShaderManager.h"
#include "RenderManager.h"
#include "SceneManager.h"
#include "Input.h"
//���C�u�����̃����N
#pragma comment(lib, "winmm")
#pragma comment(lib, "imm32")
#pragma comment(lib, "d3d11")

void Init();
void Uninit();
void Update();
void Draw();

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);	// ���g�p�錾
	UNREFERENCED_PARAMETER(lpCmdLine);		// ���g�p�錾

	CWindowManager* window = WindowManager;
	MSG msg;
	CFpsManager fps_manager;
	
	if (window->Create(hInstance, hPrevInstance, lpCmdLine, nCmdShow))
		return -1;

	Init();
	fps_manager.Init();
	// ���b�Z�[�W���[�v
	for (;;) {
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT) {
				// PostQuitMessage()���Ă΂ꂽ�烋�[�v�I��
				break;
			}
			else {
				// ���b�Z�[�W�̖|��ƃf�B�X�p�b�`
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else {

			fps_manager.CalculationFps();

			// �X�V����
			Update();
			// �`�揈��
			Draw();
			fps_manager.CalculationSleep();
		}
	}

	// �^�C�}�ݒ�����ɖ߂�
	timeEndPeriod(1);

	// �I������
	Uninit();

	window->Release();

	// COM�I������
	CoUninitialize();

	return (int)msg.wParam;

}

/******************************************************************************
* 
* @brief      Init
* @return     void
* @author     Totsuka Kensuke
* @date       2024/04/28
* 
******************************************************************************/
void Init()
{
	DeviceManager->Init();
	RenderManager->Init();
	CInput::Init();
}
/******************************************************************************
* 
* @brief      Uninit
* @return     void
* @author     Totsuka Kensuke
* @date       2024/04/28
* 
******************************************************************************/
void Uninit()
{
	DeviceManager->Release();
	RenderManager->Release();
	CInput::Fin();
}
/******************************************************************************
* 
* @brief      Update
* @return     void
* @author     Totsuka Kensuke
* @date       2024/04/28
* 
******************************************************************************/
void Update()
{
	CInput::Update();
	SceneManager->Update();
}
/******************************************************************************
* 
* @brief      Draw
* @return     void
* @author     Totsuka Kensuke
* @date       2024/04/28
* 
******************************************************************************/
void Draw()
{
	RenderManager->StartRendering();
	SceneManager->Draw();
	RenderManager->FinishRendering();
}
