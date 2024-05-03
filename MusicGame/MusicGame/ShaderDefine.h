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

enum PixelShaderType {
	Pixel,
};
enum VertexShaderType {
	Vertex,
};

//頂点シェーダファイルパス
static const char* g_cVertexShaderFilePath[] = {
	"data/shader/vertex.cso",
	"data/shader/.cso"
};
//ピクセルシェーダファイルパス
static const char* g_cPixelShaderFilePath[] = {
	"data/shader/pixel.cso",
	"data/shader/.cso"
};
