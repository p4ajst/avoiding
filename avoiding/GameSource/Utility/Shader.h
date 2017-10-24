// ------------------------------------------------------------------------------------------------ //
// @ file	 : Shader.h                                                                             //
// @ brief	 : シェーダーを利用するための関数群                                                     //
// @ date	 : 2017/10/19                                                                           //
// @ author  : Madoka Nakajima                                                                      //
// @ note	 :                                                                                      //
// @ version : ver.3.00                                                                             //
// ------------------------------------------------------------------------------------------------ // 
/* 多重インクルードの防止 */
#pragma once
/* ヘッダファイルのインクルード */
// スタンダードライブラリ関連 
#include <memory>          // スマートポインタを使うため
#define _USE_MATH_DEFINES
#include <cmath>           // 算術関数
#include <iostream>        // IOストリーム

// DirectX関連
#include <DirectXMath.h>   // DirectXの算術関連を使うため
#include <SimpleMath.h>    // DirectXTKの簡易算術関連を使うため
#include <DirectXColors.h> // 色指定のため

#include <wrl.h>  // Windows ランタイム C++ テンプレート ライブラリ

// DGSLシェーダを使用するためのヘッダファイル
#include <Effects.h>
#include <Model.h>
#include <CommonStates.h>

// バーテックスシェーダを使用するためのヘッダファイル
#include <d3d11.h>
#include <vector>
#include <fstream>
#include <VertexTypes.h>
#include <DirectXMath.h>

// 自作ヘッダファイル
#include "BinaryLoader.h"

namespace mnLib
{
	/* 構造体の宣言 */
	// シェーダに渡すデータの構造体
#pragma pack(push,1)
	__declspec(align(16)) struct MatrixesConstant
	{
		DirectX::XMMATRIX WorldViewProjection;   // world * view * projection
		float x;                                 // ｘ座標
		float z;                                 // ｚ座標
		float padding1;                          // 空間を埋める	
		float padding2;                          // 空間を埋める	

												 // Allocate aligned memory.
		static void* operator new(size_t size)
		{
			// アライメントを取得
			const size_t alignment = __alignof(MatrixesConstant);
			/*
			　　エラーメッセージ：AlignedNew > は８バイトアライメントを持つタイプにのみ有効です。
			  　あなたは派生に__declspec（位置合わせ）を忘れましたか。
			   */
			static_assert(alignment > 8
				, "AlignedNew is only useful for types with > 8byte alignment.Did you forget a __declspec(align) on TDerved ? ");
			// アライメントに合わせてメモリー確保
			void* ptr = _aligned_malloc(size, alignment);
			// メモリー確保できたかチェック
			if (!ptr)
				throw std::bad_alloc();
			// 確保したメモリアドレスを返す
			return ptr;
		}

		// Free align memory.
		static void operator delete(void* ptr)
		{
			// _aligned_mallocで確保したメモリーの解放
			_aligned_free(ptr);
		}
	};
#pragma pack(pop)

	// コンスタントバッファの構造体
#pragma pack(push,1)
	struct MatrixesConstants
	{
		DirectX::XMMATRIX WorldViewProjection;
		float Time;
	};
#pragma pack(pop)



	/* 関数のプロトタイプ宣言 */
	void InitShader(wchar_t* name);

	void CreateShader(const char* vertex, const char* pixel);
	void CreateConstantBuffer();

	void Draw(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);
}

