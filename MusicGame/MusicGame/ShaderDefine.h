/******************************************************************************
* 
* @file      ShaderDefine.h
* @brief     �V�F�[�_��`
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

//���_�V�F�[�_�t�@�C���p�X
static const char* g_cVertexShaderFilePath[] = {
	"data/shader/vertex.cso",
	"data/shader/.cso"
};
//�s�N�Z���V�F�[�_�t�@�C���p�X
static const char* g_cPixelShaderFilePath[] = {
	"data/shader/pixel.cso",
	"data/shader/.cso"
};
