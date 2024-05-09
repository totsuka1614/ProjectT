/******************************************************************************
* 
* @file      FbxBuffer.cpp
* @brief     
* @author    Totsuka Kensuke
* @date      2024/05/08
* 
******************************************************************************/
#include "FbxBuffer.h"
#include "DeviceManager.h"
#include "ErrorMessageDefine.h"

/******************************************************************************
* 
* @brief      CreateVertex
* @param[in]  vertex
* @return     HRESULT
* @author     Totsuka Kensuke
* @date       2024/05/08
* 
******************************************************************************/
void CFbxBuffer::CreateVertex(std::vector<Vertex3D> vertex)
{
	//頂点バッファ作成
	D3D11_BUFFER_DESC buffer_desc;
	buffer_desc.ByteWidth = sizeof(Vertex3D) * vertex.size();	// バッファのサイズ
	buffer_desc.Usage = D3D11_USAGE_DEFAULT;			// 使用方法
	buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;	// BIND設定
	buffer_desc.CPUAccessFlags = 0;						// リソースへのCPUのアクセス権限についての設定
	buffer_desc.MiscFlags = 0;							// リソースオプションのフラグ
	buffer_desc.StructureByteStride = 0;				// 構造体のサイズ

	D3D11_SUBRESOURCE_DATA sub_resource;
	sub_resource.pSysMem = vertex.data();	// バッファの中身の設定
	sub_resource.SysMemPitch = 0;			// textureデータを使用する際に使用するメンバ
	sub_resource.SysMemSlicePitch = 0;		// textureデータを使用する際に使用するメンバ

	m_nVtxSize = sizeof(Vertex3D);
	m_nVtxCount = vertex.size();

	// バッファ作成
	if (FAILED(DeviceManager->GetDevice()->CreateBuffer(
		&buffer_desc,								// バッファ情報
		&sub_resource,								// リソース情報
		&m_pVtxBuffer)))	// 作成されたバッファの格納先
	{
		ErrorMessage->Output(ERROR_FBX_CREATE_VERTEX_BUFFER_FAILED);
	}

}
/******************************************************************************
* 
* @brief      CreateVertex
* @param[in]  vertex
* @return     HRESULT
* @author     Totsuka Kensuke
* @date       2024/05/08
* 
******************************************************************************/
void CFbxBuffer::CreateVertex(std::vector<Vertex2D> vertex)
{
	//頂点バッファ作成
	D3D11_BUFFER_DESC buffer_desc;
	buffer_desc.ByteWidth = sizeof(Vertex2D) * vertex.size();	// バッファのサイズ
	buffer_desc.Usage = D3D11_USAGE_DEFAULT;			// 使用方法
	buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;	// BIND設定
	buffer_desc.CPUAccessFlags = 0;						// リソースへのCPUのアクセス権限についての設定
	buffer_desc.MiscFlags = 0;							// リソースオプションのフラグ
	buffer_desc.StructureByteStride = 0;				// 構造体のサイズ

	D3D11_SUBRESOURCE_DATA sub_resource;
	sub_resource.pSysMem = vertex.data();	// バッファの中身の設定
	sub_resource.SysMemPitch = 0;			// textureデータを使用する際に使用するメンバ
	sub_resource.SysMemSlicePitch = 0;		// textureデータを使用する際に使用するメンバ

	m_nVtxSize = sizeof(Vertex2D);
	m_nVtxCount = vertex.size();

	// バッファ作成
	if (FAILED(DeviceManager->GetDevice()->CreateBuffer(
		&buffer_desc,								// バッファ情報
		&sub_resource,								// リソース情報
		&m_pVtxBuffer)))	// 作成されたバッファの格納先
	{
		ErrorMessage->Output(ERROR_FBX_CREATE_VERTEX_BUFFER_FAILED);
	}
}

void CFbxBuffer::CreateIndex(std::vector<UINT> index)
{
	//頂点バッファ作成
	D3D11_BUFFER_DESC buffer_desc;
	buffer_desc.ByteWidth = (UINT)sizeof(UINT) * index.size();	// バッファのサイズ
	buffer_desc.Usage = D3D11_USAGE_DEFAULT;							// 使用方法
	buffer_desc.BindFlags = D3D11_BIND_INDEX_BUFFER;					// BIND設定
	buffer_desc.CPUAccessFlags = 0;										// リソースへのCPUのアクセス権限についての設定
	buffer_desc.MiscFlags = 0;											// リソースオプションのフラグ
	buffer_desc.StructureByteStride = 0;								// 構造体のサイズ

	D3D11_SUBRESOURCE_DATA sub_resource;
	sub_resource.pSysMem = index.data();							// バッファの中身の設定
	sub_resource.SysMemPitch = 0;										// textureデータを使用する際に使用するメンバ
	sub_resource.SysMemSlicePitch = 0;									// textureデータを使用する際に使用するメンバ

	m_nIdxSize = sizeof(UINT);
	m_nIdxCount = index.size();

	// バッファ作成
	if (FAILED(DeviceManager->GetDevice()->CreateBuffer(
		&buffer_desc,						// バッファ情報
		&sub_resource,						// リソース情報
		&m_pIdxBuffer)))		// 作成されたバッファの格納先
	{
		ErrorMessage->Output(ERROR_FBX_CREATE_INDEX_BUFFER_FAILED);
	}
}