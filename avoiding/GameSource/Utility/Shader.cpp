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
// ComPtrを使う為
using namespace Microsoft::WRL;
// unique_ptrを使う為
using namespace std;
// DirectXの機能を使う為
using namespace DirectX;
// SimpleMathの機能を使う為
using namespace DirectX::SimpleMath;
// 自作名前空間
using namespace mnLib;

/* メンバ関数の定義 */


// ----------------------------------------------------------------------------------------------- //
// @ brief	: コンストラクタ                                                                       //
// @ param	: なし                                                                                 //
// @ return : なし                                                                                 //
// @ note	: 自作名前空間内の関数                                                                 //
// ----------------------------------------------------------------------------------------------- // 
mnLib::Shader::Shader()
{
	// モデルに空を入れる
	model = nullptr;
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: デストラクタ                                                                         //
// @ param	: なし                                                                                 //
// @ return : なし                                                                                 //
// @ note	: 自作名前空間内の関数                                                                 //
// ----------------------------------------------------------------------------------------------- // 
mnLib::Shader::~Shader()
{

}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: シェーダーを設定するモデルの初期化                                                   //
// @ param	: wchar_t* name...読み込むモデルのファイル名                                           //
// @ return : なし                                                                                 //
// @ note	: 自作名前空間内の関数                                                                 //
// ----------------------------------------------------------------------------------------------- // 
void mnLib::Shader::InitShader(wchar_t * name)
{
	DGSLEffectFactory fx(g_pd3dDevice.Get());
	fx.SetDirectory(L"Resources");
	model = Model::CreateFromCMO(g_pd3dDevice.Get(), name, fx);
}


// ----------------------------------------------------------------------------------------------- //
// @ brief	: シェーダーを作成する                                                                 //
// @ param	: const char * vertex...頂点シェーダーのファイル名                                     //
// @ param	: const char * pixel...ピクセルシェーダのファイル名                                    //
// @ return : なし                                                                                 //
// @ note	: 自作名前空間内の関数                                                                 //
// ----------------------------------------------------------------------------------------------- // 
void mnLib::Shader::CreateShader(const char * vertex, const char * pixel)
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
// @ brief	: コンスタントバッファの初期化                                                         //
// @ param	: なし                                                                                 //
// @ return : なし                                                                                 //
// @ note	: 自作名前空間内の関数                                                                 //
// ----------------------------------------------------------------------------------------------- // 
void mnLib::Shader::CreateConstantBuffer()
{
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
// @ brief	: 描画                                                                                 //
// @ param	: Matrix view...ビュー行列                                                             //
// @ param	: Matrix proj...射影行列                                                               //
// @ return : なし                                                                                 //
// @ note	: 自作名前空間内の関数                                                                 //
// ----------------------------------------------------------------------------------------------- // 
void mnLib::Shader::Draw(Matrix view, Matrix proj)
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

void mnLib::Shader::SetModel(wchar_t * filename)
{
	InitShader(filename);
}
