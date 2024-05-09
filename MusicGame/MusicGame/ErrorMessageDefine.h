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
#define ERROR_DEFAULT "エラーがエラーなのにエラーじゃないのん..."
//シェーダ関係
#define	ERROR_PIXEL_SHADER_RESOURCE_NOT_FOUND	"ピクセルシェーダが見つかりません。"
#define	ERROR_PIXEL_SHADER_RESOURCE_CORRUPTION "ピクセルシェーダが破損しています。"
#define	ERROR_VERTEX_SHADER_RESOURCE_NOT_FOUND "頂点シェーダが見つかりません"
#define	ERROR_VERTEX_SHADER_RESOURCE_CORRUPTION "頂点シェーダが破損しています"
//シーン関係
#define	ERROR_SCENE_CHANGE_NOT_FOUND	"シーンの遷移先が見つかりません"
//モデル関係
#define ERROR_FBX_FILE_NOT_FOUND "Fbxファイルが見つかりません"
#define ERROR_FBX_MESH_FAILED "Fbxメッシュロード失敗"
#define ERROR_FBX_MATERIAL_FAILED "Fbxマテリアルロード失敗"
#define ERROR_FBX_BONE_FAILED "Fbxボーンロード失敗"
#define ERROR_FBX_ANIMATION_FAILED "Fbxアニメーションロード失敗"
#define ERROR_FBX_CREATE_VERTEX_BUFFER_FAILED "FbxVeretxBuffer作成失敗"
#define ERROR_FBX_CREATE_INDEX_BUFFER_FAILED "FbxIndexBuffer作成失敗"
