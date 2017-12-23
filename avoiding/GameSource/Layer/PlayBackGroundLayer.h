// ------------------------------------------------------------------------------------------------ //
// @ file	 : BackGroundLayer.h                                                                    //
// @ brief	 : 背景部分のクラス                                                                     //
// @ date	 : 2017/06/30                                                                           //
// @ author  : Madoka Nakajima                                                                      //
// @ note	 :                                                                                      //
// ------------------------------------------------------------------------------------------------ // 
/* 多重インクルードの防止 */
#pragma once

/* ヘッダファイルのインクルード */
// 標準ライブラリ
#include <SpriteBatch.h>
// 先生のライブラリ
#include "../../ImaseLib/Texture.h"
// 自作ヘッダファイル
#include "Layer.h"

/* クラス宣言 */
class PlayBackGroundLayer :public Layer
{
	// 画像
	std::unique_ptr<Texture> mBackGround;

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
};
