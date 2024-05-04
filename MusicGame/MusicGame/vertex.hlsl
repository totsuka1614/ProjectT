/******************************************************************************
* 
* @file      vertex.hlsl
* @brief     �ʏ�̒��_�V�F�[�_
* @author    Totsuka Kensuke
* @date      2023/04/28
* @note      
* @attention 
* 
******************************************************************************/
struct VertexIn
{
	float4 pos : POSITION0;
	float4 nor : NORMAL0;
	float2 texcoord : TEXTURE0;
};

struct VertexOut
{
	float4 pos : SV_POSITION0;
	float4 nor : NORMAL0;
	float2 texcoord : TEXTURE0;
	float4 worldPos : TEXCOORD0;
};

cbuffer ConstantBuffer: register(b0)
{
	float4x4    mWVP;		// ���[���h�~�r���[�~�ˉe�s��(�]�u�s��)
	float4x4   	mW;			// ���[���h�s��(�]�u�s��)
	float4x4   	mTex;		// �e�N�X�`���s��(�]�u�s��)
}

VertexOut main(VertexIn input)
{
	VertexOut output;
	input.nor.w = 0.0f;
	output.pos = mul(input.pos, mWVP);
	output.nor = mul(input.nor,mW).xyzw;
	output.worldPos = mul(input.pos,mW);
	output.texcoord = input.texcoord;

	return output;
}