// ------------------------------------------------------------------------------------------------ //
// @ file	 : Common.h                                                                             //
// @ brief	 : 複数のクラスにまたがる変数をまとめて外部参照するヘッダファイル                       //
// @ date	 : 2017/06/30                                                                           //
// @ author  : Madoka Nakajima                                                                      //
// @ note	 :                                                                                      //
// @ version : ver.3.00                                                                             //
// ------------------------------------------------------------------------------------------------ // 
/* 多重インクルードの防止 */
#pragma once

/* ヘッダファイルのインクルード */
// 標準ライブラリ
#include <SpriteBatch.h>
#include <memory>

/* 定数定義 */
static const int TextureSize = 64;

/* 変数定義 */
extern bool g_mouseFlag;

/* 関数のプロトタイプ宣言 */
void DrawNum(DirectX::SpriteBatch* sprite, ID3D11ShaderResourceView* resource,int n, float x,float y);

//void DrawNum(std::shared_ptr<SpriteBatch> sprite, ID3D11ShaderResourceView* resource, int n, float x, float y);
