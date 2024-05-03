/******************************************************************************
* 
* @file      ErrorMessageDefine.h
* @brief     エラーメッセージ一覧
* @author    Totsuka Kensuke
* @date      2024/04/28
* @note      
* @attention 
* 
******************************************************************************/
#pragma once
#include "ErrorMessageManager.h"
#include <iostream>
#include <string>


#define ERROR_CELL (std::string)__FILE__ + " : " + std::to_string(__LINE__)
	//不明なエラー
#define DEFAULT_ERROR "エラーがエラーなのにエラーじゃないのん..."
//シェーダ関係
#define	ERROR_PIXEL_SHADER_RESOURCE_NOT_FOUND	"ピクセルシェーダが見つかりません。"
#define	ERROR_PIXEL_SHADER_RESOURCE_CORRUPTION "ピクセルシェーダが破損しています。"
#define	ERROR_VERTEX_SHADER_RESOURCE_NOT_FOUND "頂点シェーダが見つかりません"
#define	ERROR_VERTEX_SHADER_RESOURCE_CORRUPTION "頂点シェーダが破損しています"
//シーン関係
#define	ERROR_SCENE_CHANGE_NOT_FOUND	"シーンの遷移先が見つかりません"
