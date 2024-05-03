/******************************************************************************
* 
* @file      ErrorMessageDefine.h
* @brief     �G���[���b�Z�[�W�ꗗ
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
	//�s���ȃG���[
#define DEFAULT_ERROR "�G���[���G���[�Ȃ̂ɃG���[����Ȃ��̂�..."
//�V�F�[�_�֌W
#define	ERROR_PIXEL_SHADER_RESOURCE_NOT_FOUND	"�s�N�Z���V�F�[�_��������܂���B"
#define	ERROR_PIXEL_SHADER_RESOURCE_CORRUPTION "�s�N�Z���V�F�[�_���j�����Ă��܂��B"
#define	ERROR_VERTEX_SHADER_RESOURCE_NOT_FOUND "���_�V�F�[�_��������܂���"
#define	ERROR_VERTEX_SHADER_RESOURCE_CORRUPTION "���_�V�F�[�_���j�����Ă��܂�"
//�V�[���֌W
#define	ERROR_SCENE_CHANGE_NOT_FOUND	"�V�[���̑J�ڐ悪������܂���"
