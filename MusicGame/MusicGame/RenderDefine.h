#pragma once
//*****************************************************************************
// �\���̒�`
//*****************************************************************************
enum EBlendState {
	BS_NONE = 0,							// ��������������
	BS_ALPHABLEND,							// ����������
	BS_ADDITIVE,							// ���Z����
	BS_SUBTRACTION,							// ���Z����

	MAX_BLENDSTATE
};

enum ECullMode {
	CULLMODE_NONE = 0,						// �J�����O���Ȃ�
	CULLMODE_CW,							// �O�ʃJ�����O
	CULLMODE_CCW,							// �w�ʃJ�����O

	MAX_CULLMODE
};