#pragma once
//*****************************************************************************
// 構造体定義
//*****************************************************************************
enum EBlendState {
	BS_NONE = 0,							// 半透明合成無し
	BS_ALPHABLEND,							// 半透明合成
	BS_ADDITIVE,							// 加算合成
	BS_SUBTRACTION,							// 減算合成

	MAX_BLENDSTATE
};

enum ECullMode {
	CULLMODE_NONE = 0,						// カリングしない
	CULLMODE_CW,							// 前面カリング
	CULLMODE_CCW,							// 背面カリング

	MAX_CULLMODE
};