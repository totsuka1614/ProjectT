/******************************************************************************
* 
* @file      FbxBuffer.h
* @brief     Fbxのシェーダに送るバッファ
* @author    Totsuka Kensuke
* @date      2024/05/08
* 
******************************************************************************/
#pragma once
#include "main.h"
#include <vector>

class CFbxBuffer
{
public:
	// 頂点フォーマット
	typedef struct {
		XMFLOAT3 vtx;	// 頂点座標
		XMFLOAT3 nor;	// 法線ベクトル
		XMFLOAT2 tex;	// テクスチャ座標
		// メッシュとボーンを結びつけるためのデータ
		float weight[4];// それぞれの骨からどの程度影響を受けるか
		long index[4];  // どの骨に引っ付いて動くか
	} Vertex3D;
	// 頂点フォーマット
	typedef struct {
		XMFLOAT2 vtx;	// 頂点座標
		XMFLOAT2 tex;	// テクスチャ座標
		XMFLOAT4 diffuse;// 拡散反射光
	} Vertex2D;
public:
	CFbxBuffer() : m_pVtxBuffer(nullptr), m_pIdxBuffer(nullptr) {}
	~CFbxBuffer() {
		SAFE_DELETE(m_pVtxBuffer);
		SAFE_DELETE(m_pIdxBuffer);
	}
	void CreateVertex(std::vector<Vertex3D> vertex);
	void CreateVertex(std::vector<Vertex2D> vertex);
	void CreateIndex(std::vector<UINT> index);
private:
	ID3D11Buffer* m_pVtxBuffer;
	UINT m_nVtxSize;
	UINT m_nVtxCount;

	ID3D11Buffer* m_pIdxBuffer;
	UINT m_nIdxSize;
	UINT m_nIdxCount;

	D3D11_PRIMITIVE_TOPOLOGY m_tTopology;
};