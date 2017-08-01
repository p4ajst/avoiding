// ------------------------------------------------------------------------------------------------ //
// @ file	 : GameStartScreen.h                                                                    //
// @ brief	 : ゲーム開始前のカウントダウンに関するクラス                                           //
// @ date	 : 2017/07/18                                                                           //
// @ author  : Madoka Nakajima                                                                      //
// @ note	 :                                                                                      //
// @ version : ver.3.00                                                                             //
// ------------------------------------------------------------------------------------------------ // 
/* 多重インクルードの防止 */
#pragma once

/* ヘッダファイルのインクルード */
// 標準ライブラリ
#include <memory>
#include <SpriteBatch.h>
// 先生のフレームワーク
#include "../../ImaseLib/Texture.h"
// 自作ヘッダファイル
#include "../Utility/Common.h"

/* クラス宣言 */
class GameStartScreen
{
	/* メンバ変数 */
	// カウンタ
	int mStartCounter;
	// 開始フラグ
	bool mStartFlag;
	// スプライトバッチ
	std::unique_ptr<DirectX::SpriteBatch> pSprites;
	// 画像描画変数
	std::unique_ptr<Texture> mWhite;
	std::unique_ptr<Texture> mNumber;
public:
	/* メンバ関数 */
	// 初期化
	void Initialize();
	// 更新
	void Update();
	// 描画
	void Render();
	// 終了
	void Finalize();
	// フラグの取得
	bool GetFlag() { return mStartFlag; }
};

