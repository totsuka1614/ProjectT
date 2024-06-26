/******************************************************************************
* 
* @file      ShaderDefine.h
* @brief     シェーダ定義
* @author    Totsuka Kensuke
* @date      2024/04/28
* @note      
* @attention 
* 
******************************************************************************/
#pragma once

enum ePixelShaderType {
	Pixel,

	Max_Pixel_Num
};
enum eVertexShaderType {
	Vertex,

	Max_Vertex_Num
};

//頂点シェーダファイルパス
static const char* g_cVertexShaderFilePath[] = {
	"data/shader/vertex.cso",
};
//ピクセルシェーダファイルパス
static const char* g_cPixelShaderFilePath[] = {
	"data/shader/pixel.cso",
};
