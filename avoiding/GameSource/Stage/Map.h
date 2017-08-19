// ------------------------------------------------------------------------------------------------ //
// @ file	 : Map.h                                                                                //
// @ brief	 : マップに関するクラス                                                                 //
// @ date	 : 2017/06/25                                                                           //
// @ author  : Madoka Nakajima                                                                      //
// @ note	 :                                                                                      //
// ------------------------------------------------------------------------------------------------ // 
/* 多重インクルードの防止 */
#pragma once

/* ヘッダファイルのインクルード */
// 標準ライブラリ
#include <simplemath.h>
// 自作ヘッダファイル
#include "MapChip.h"

/* クラス宣言 */
class Map
{
	/* メンバ変数 */
	// マップチップの配列
	MapChip** mMapChip;
	// マップの幅と高さ
	int mWidth;
	int mHeight;
public:
	/* メンバ関数 */
	// コンストラクタ
	Map(int width, int height);
	// デストラクタ
	~Map();
	// マップチップの登録
	void Set(int x, int y, MapChip* chip);
	// 二次元配列の添え字から一次元配列の添え字にする
	int ToIndex(int x, int y);
	// 描画
	void Draw(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);
	// マップチップ番号からマウスカーソルの座標を取得
	DirectX::SimpleMath::Vector3 GetPos(int x, int z, int ox, int oz);
	// 乱数を取得
	DirectX::SimpleMath::Vector3 GetRandomPos(int x, int z, float ox, float oz);
	// マップチップの属性を取得
	int GetAttribute(int x, int z);
};
