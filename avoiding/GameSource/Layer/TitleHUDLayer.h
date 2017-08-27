// ------------------------------------------------------------------------------------------------ //
// @ file	 : TitleHUDLayer.h                                                                      //
// @ brief	 : ヘッドアップディスプレイ部分のクラス                                                 //
// @ date	 : 2017/07/10                                                                           //
// @ author  : Madoka Nakajima                                                                      //
// @ note	 :                                                                                      //
// @ version : ver.3.00                                                                             //
// ------------------------------------------------------------------------------------------------ // 
/* 多重インクルードの防止 */
#pragma once
/* ヘッダファイルのインクルード */
// 先生のフレームワーク
#include "../../ImaseLib/Texture.h"
// 自作ヘッダファイル
#include "Layer.h"


/* クラス宣言 */
class TitleHUDLayer :public Layer
{
	/* メンバ変数 */
	// 画像描画
	struct Graph
	{
		// 画像描画用変数
		// 後
		std::unique_ptr<Texture> graphA;
		// 前
		std::unique_ptr<Texture> graphB;
		// 画像の描画範囲
		RECT range;
		// 判定用フラグ
		bool flag;
	};
	// シーン遷移用変数
	bool mSceneFlag;

	// 画像描画
	Graph start;
	Graph end;

	// 画像描画用変数
	std::unique_ptr<Texture> mGraph;

public:
	/* メンバ関数 */
	// 初期化処理
	void Initialize(Scene* scene);
	// 更新処理
	void Update();
	// 描画処理
	void Draw();
	// 終了処理
	void Finalize();
	// 取得
	bool GetFlag() { return mSceneFlag; }
};
