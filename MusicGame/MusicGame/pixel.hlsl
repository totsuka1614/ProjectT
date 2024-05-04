/******************************************************************************
* 
* @file      pixel.hlsl
* @brief     �s�N�Z���V�F�[�_
* @author    Totsuka Kensuke
* @date      2023/04/28
* @note      
* @attention 
* 
******************************************************************************/
// �O���[�o��
cbuffer global : register(b0) {
	float4	g_vEye;			// ���_���W
	// ����
	float3	g_vLightVector;	// ��������
};

struct PS_IN
{
	float4 pos : SV_POSITION;
	float4 nor : NORMAL0;
	float2 texcoord : TEXTURE0;
	float4 worldPos : TEXCOORD0;
};

Texture2D    Texture : register(t0); // Texture���X���b�g0��0�Ԗڂ̃e�N�X�`�����W�X�^�ɐݒ�
SamplerState Sampler : register(s0); // Sampler���X���b�g0��0�Ԗڂ̃T���v�����W�X�^�ɐݒ�

float4 main(PS_IN input) : SV_Target0
{
	float4 color = float4(0.7f, 0.7f, 0.7f, 1.0f);
    return color;
}