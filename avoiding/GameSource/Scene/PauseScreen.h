// ------------------------------------------------------------------------------------------------ //
// @ file	 : PauseScreen.h                                                                        //
// @ brief	 : ポーズ画面のヘッダファイル                                                           //
// @ date	 : 2017/07/13                                                                           //
// @ author  : Madoka Nakajima                                                                      //
// @ note	 :                                                                                      //
// ------------------------------------------------------------------------------------------------ // 
/* 多重インクルードの防止 */
#pragma once 

/* ヘッダファイルのインクルード */
// 標準ライブラリ
#include <memory>
#include <SpriteBatch.h>
// 先生のフレームワーク
#include "../../ImaseLib/Texture.h"

/* クラス宣言 */
class PauseScreen
{
	/* メンバ変数 */
	// スプライトバッチ
	std::unique_ptr<DirectX::SpriteBatch> pSpriteBatch;
	// 画像描画変数
	std::unique_ptr<Texture> mChoco;
public:
	/* メンバ関数 */
	// 初期化処理
	void Initialize();
	// 更新処理
	void Update();
	// 描画処理
	void Render();
	// 終了処理
	void Finalize();
};
