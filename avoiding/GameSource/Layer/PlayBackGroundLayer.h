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
#include "Layer.h"

/* クラス宣言 */
class PlayBackGroundLayer :public Layer
{
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
