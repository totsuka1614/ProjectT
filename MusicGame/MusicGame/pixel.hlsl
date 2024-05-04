/******************************************************************************
* 
* @file      pixel.hlsl
* @brief     ピクセルシェーダ
* @author    Totsuka Kensuke
* @date      2023/04/28
* @note      
* @attention 
* 
******************************************************************************/
// グローバル
cbuffer global : register(b0) {
	float4	g_vEye;			// 視点座標
	// 光源
	float3	g_vLightVector;	// 光源方向
};

struct PS_IN
{
	float4 pos : SV_POSITION;
	float4 nor : NORMAL0;
	float2 texcoord : TEXTURE0;
	float4 worldPos : TEXCOORD0;
};

Texture2D    Texture : register(t0); // Textureをスロット0の0番目のテクスチャレジスタに設定
SamplerState Sampler : register(s0); // Samplerをスロット0の0番目のサンプラレジスタに設定

float4 main(PS_IN input) : SV_Target0
{
	float4 color = float4(0.7f, 0.7f, 0.7f, 1.0f);
    return color;
}