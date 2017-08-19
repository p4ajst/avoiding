// ------------------------------------------------------------------------------------------------ //
// @ file	 : HUDLayer.h                                                                           //
// @ brief	 : ヘッドアップディスプレイ部分のクラス                                                 //
// @ date	 : 2017/06/30                                                                           //
// @ author  : Madoka Nakajima                                                                      //
// @ note	 :                                                                                      //
// ------------------------------------------------------------------------------------------------ // 
/* 多重インクルードの防止 */
#pragma once

/* ヘッダファイルのインクルード */
#include <memory>
// 先生のフレームワーク
#include "../../ImaseLib/Texture.h"
// 自作ヘッダファイル
#include "Layer.h"
#include "../Scene/PauseScreen.h"
#include "../Scene/GameStartScreen.h"


/* クラス宣言 */
class PlayHUDLayer :public Layer
{
private:
	// テクスチャ
	std::shared_ptr<Texture> pTexture;
	// 画像描画
	std::unique_ptr<Texture> mNum;
	std::unique_ptr<Texture> mBiscuitBefore;
	std::unique_ptr<Texture> mBiscuitAfter;
	std::unique_ptr<PauseScreen> mPause;
	std::unique_ptr<GameStartScreen> mStart;
	// 描画範囲
	RECT mBisrect;
	// ポーズ中か？
	bool mPauseFlag;
	// スタートカウンター中か？
	bool mStartFlag;
	// カーソルが画像の描画範囲内にあるか？
	bool mpFrag;
	// カウンタ
	int mCount;

	/* メンバ関数 */
public:
	// 初期化
	void Initialize(Scene* scene);
	// 更新
	void Update();
	// 描画
	void Draw();

	// 終了
	void Finalize();
	// カウンタのセット
	void SetCount(int cnt) { mCount = cnt; }
	void SetStartFlag(bool flag) { mStartFlag = flag; }
	// フラグの取得
	bool GetPauseFlag() { return mPauseFlag; }
	bool GetStartFlag() { return mStartFlag; }
};
