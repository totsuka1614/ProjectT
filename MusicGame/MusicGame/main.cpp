/******************************************************************************
* 
* @file      main.cpp
* @brief     メイン
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
//ライブラリのリンク
#pragma comment(lib, "winmm")
#pragma comment(lib, "imm32")
#pragma comment(lib, "d3d11")

void Init();
void Uninit();
void Update();
void Draw();

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);	// 未使用宣言
	UNREFERENCED_PARAMETER(lpCmdLine);		// 未使用宣言

	CWindowManager* window = WindowManager;
	MSG msg;
	CFpsManager fps_manager;
	
	if (window->Create(hInstance, hPrevInstance, lpCmdLine, nCmdShow))
		return -1;

	Init();
	fps_manager.Init();
	// メッセージループ
	for (;;) {
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT) {
				// PostQuitMessage()が呼ばれたらループ終了
				break;
			}
			else {
				// メッセージの翻訳とディスパッチ
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else {

			fps_manager.CalculationFps();

			// 更新処理
			Update();
			// 描画処理
			Draw();
			fps_manager.CalculationSleep();
		}
	}

	// タイマ設定を元に戻す
	timeEndPeriod(1);

	// 終了処理
	Uninit();

	window->Release();

	// COM終了処理
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
