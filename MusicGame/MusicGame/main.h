/******************************************************************************
*
* @file      main.h
* @brief     メインクラス
* @author    Totsuka Kensuke
* @date      2023/04/27
* @note
* @attention
*
******************************************************************************/
#ifndef __MAIN_H__
#define __MAIN_H__

// インクルードファイル
#include <windows.h>
#include <tchar.h>
#include <math.h>
#include <mmsystem.h>
#include <d3d11.h>
#include <string>
#include <DirectXMath.h>

using namespace DirectX;
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(x) {if(x){(x)->Release();x=nullptr;}}
#endif

#ifndef SAFE_DELETE
#define SAFE_DELETE(x) {if(x){delete(x);x=nullptr;}}
#endif
#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(x) {if(x){delete[](x);x=nullptr;}}
#endif

#define SCREEN_WIDTH	(1280)				// ウインドウの幅
#define SCREEN_HEIGHT	(720)				// ウインドウの高さ
#define SCREEN_CENTER_X	(SCREEN_WIDTH/2)	// ウインドウの中心Ｘ座標
#define SCREEN_CENTER_Y	(SCREEN_HEIGHT/2)	// ウインドウの中心Ｙ座標

#define	NUM_VERTEX		(4)					// 頂点数
#define	NUM_POLYGON		(2)					// ポリゴン数

#define SinDeg(degree)	sinf(XMConvertToRadians(degree))
#define CosDeg(degree)	cosf(XMConvertToRadians(degree))

#endif
