// ------------------------------------------------------------------------------------------------ //
// @ file	 : MapChip.h                                                                            //
// @ brief	 : マップチップに関するクラス                                                           //
// @ date	 : 2017/06/25                                                                           //
// @ author  : Madoka Nakajima                                                                      //
// @ note	 :                                                                                      //
// @ version : ver.3.00                                                                             //
// ------------------------------------------------------------------------------------------------ // 
/* 多重インクルードの防止 */
#pragma once

/* ヘッダファイルのインクルード */
// モデルを使う為
#include <Model.h>

/* クラス宣言 */
class MapChip
{
	/* メンバ変数 */
	// ステージの属性
	int mAttribute;
	// モデル
	std::shared_ptr<DirectX::Model> mModel;
public:
	/* メンバ関数 */
	// コンストラクタ
	MapChip();
	// 引数付きコンストラクタ
	MapChip(int attribute);
	// デストラクタ
	~MapChip();
	// 属性の設定
	void SetAttribute(int attribute) { mAttribute = attribute; }
	// モデルの設定
	void SetModel(std::shared_ptr<DirectX::Model> model) { mModel = model; }
	// 属性を取得
	int GetAttribute() { return mAttribute; }
	// モデルの取得
	std::shared_ptr<DirectX::Model> GetModel() { return mModel; }
};
