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
	// シーン遷移用変数
	bool mSceneFlag;
	// 画像描画用変数
	std::unique_ptr<Texture> mGraph;
	std::unique_ptr<Texture> mBeforeStart;
	std::unique_ptr<Texture> mAfterStart;
	std::unique_ptr<Texture> mBeforeEnd;
	std::unique_ptr<Texture> mAfterEnd;
	// 判定用フラグ
	bool msFlag;
	bool meFlag;
	// 画像の描画範囲
	RECT mStart;
	RECT mEnd;

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
