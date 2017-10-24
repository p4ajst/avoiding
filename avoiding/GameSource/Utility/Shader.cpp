// ------------------------------------------------------------------------------------------------ //
// @ file	 : Shader.cpp                                                                           //
// @ brief	 : シェーダーを利用するための関数群                                                     //
// @ date	 : 2017/10/19                                                                           //
// @ author  : Madoka Nakajima                                                                      //
// @ note	 :                                                                                      //
// @ version : ver.3.00                                                                             //
// ------------------------------------------------------------------------------------------------ // 
/* ヘッダファイルのインクルード */
// 標準ライブラリ
#include <fstream>
#include <simplemath.h>
// 先生のライブラリ
#include "../../ImaseLib/Direct3D.h"
#include "../../ImaseLib/DirectXTK.h"
// 自作ヘッダファイル
#include "Shader.h"

/* 名前空間 */
using namespace std;
using namespace DirectX;              
using namespace DirectX::SimpleMath;
using namespace mnLib;


/* 変数の宣言 */
// コンスタントバッファ
std::vector<char> buffer;
// 頂点シェーダ
Microsoft::WRL::ComPtr<ID3D11VertexShader> vertexShader;
// インプットレイアウト
Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout;
// ピクセルシェーダ
Microsoft::WRL::ComPtr<ID3D11PixelShader> pixelShader;
// コンスタントバッファのオブジェクト
Microsoft::WRL::ComPtr<ID3D11Buffer> constantBuffer;
// コンスタントバッファに渡すデータ
std::unique_ptr<MatrixesConstant> matrixesConstant;
// モデル
std::shared_ptr<DirectX::Model> model;
// バイナリローダー
BinaryLoader binary;


/* 関数の定義 */
// ----------------------------------------------------------------------------------------------- //
// @ brief	:                                                                                      //
// @ param	:                                                                                      //
// @ param	:                                                                                      //
// @ return :                                                                                      //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void mnLib::InitShader(wchar_t * name)
{
	DGSLEffectFactory fx(g_pd3dDevice.Get());
	fx.SetDirectory(L"Resources");
	model = Model::CreateFromCMO(g_pd3dDevice.Get(), name, fx);
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	:                                                                                      //
// @ param	:                                                                                      //
// @ param	:                                                                                      //
// @ return :                                                                                      //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void mnLib::CreateShader(const char * vertex, const char * pixel)
{
	// 頂点シェーダ
	binary.Load(vertex);
	// 頂点シェーダの作成（初期化）
	g_pd3dDevice.Get()->CreateVertexShader(buffer.data(), buffer.size(), nullptr, vertexShader.GetAddressOf());
	/*
		インプットレイアウト
		入力する要素は、座標・法線・接線・色・テクスチャ座標
	*/
	g_pd3dDevice.Get()->CreateInputLayout
	(
		// 入力の要素指定
		VertexPositionNormalTangentColorTexture::InputElements,
		// 入力の要素数
		VertexPositionNormalTangentColorTexture::InputElementCount,
		// 頂点シェーダ
		buffer.data(),
		// 頂点シェーダのサイズ
		buffer.size(),
		// インプットレイアウトの取得
		inputLayout.GetAddressOf()
	);

	// ピクセルシェーダ
	binary.Load(pixel);
	// ピクセルシェーダの作成（初期化）
	g_pd3dDevice.Get()->CreatePixelShader(buffer.data(), buffer.size(), nullptr, pixelShader.GetAddressOf());
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	:                                                                                      //
// @ param	:                                                                                      //
// @ param	:                                                                                      //
// @ return :                                                                                      //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void mnLib::CreateConstantBuffer()
{
	// コンスタントバッファの初期化
	// コンスタントバッファの情報を入れる
	D3D11_BUFFER_DESC bufferDesc = {};
	// サイズ
	bufferDesc.ByteWidth = sizeof(MatrixesConstant);
	// 場所：ビデオメモリに作成
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	// 接続：コンスタントバッファ
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	// CPUからのアクセス：書き込み
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	// 使わない
	bufferDesc.MiscFlags = 0;
	// 使わない
	bufferDesc.StructureByteStride = 0;

	// コンスタントバッファの作成
	g_pd3dDevice.Get()->CreateBuffer(&bufferDesc, nullptr, constantBuffer.GetAddressOf());
	matrixesConstant.reset(new MatrixesConstant());
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	:                                                                                      //
// @ param	:                                                                                      //
// @ param	:                                                                                      //
// @ return :                                                                                      //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void mnLib::Draw(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj)
{
	// ワールド行列
	Matrix world = Matrix::Identity;
	// ワールド＊ビュー＊プロジェクション
	Matrix wvp = Matrix::Identity;

	// ワールド＊ビュー＊プロジェクションの変数にそれぞれをかける
	wvp *= world;
	wvp *= view;
	wvp *= proj;

	// コンスタントバッファの設定
	// ※設定時にTransposeする（転置行列）
	matrixesConstant->WorldViewProjection = wvp.Transpose();

	// 描画
	model->Draw(g_pImmediateContext.Get(), *g_state.get(), world, view, proj, false, [&]()
	{
		// GPUのコンスタントバッファにアクセスするアドレスの取得
		D3D11_MAPPED_SUBRESOURCE mappedResource;
		g_pImmediateContext.Get()->Map(constantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
		// GPU上のコンスタントバッファにデータを送る
		*(MatrixesConstant*)mappedResource.pData = *matrixesConstant.get();
		g_pImmediateContext.Get()->Unmap(constantBuffer.Get(), 0);

		// インプットレイアウトの設定
		g_pImmediateContext.Get()->IASetInputLayout(inputLayout.Get());
		// バーテックスシェーダの設定
		g_pImmediateContext.Get()->VSSetShader(vertexShader.Get(), nullptr, 0);

		// バーテックスシェーダに渡すコンスタントバッファ
		ID3D11Buffer * buffer[] = { constantBuffer.Get() };
		g_pImmediateContext.Get()->VSSetConstantBuffers(0, 1, buffer);

		// ピクセルシェーダの設定
		g_pImmediateContext.Get()->PSSetShader(pixelShader.Get(), nullptr, 0);
	});
}