﻿// ------------------------------------------------------------------------------------------------ //
// @ file	 : TitleGameLayer.h                                                                     //
// @ brief	 : ゲーム部分のクラス                                                                   //
// @ date	 : 2017/07/10                                                                           //
// @ author  : Madoka Nakajima                                                                      //
// @ note	 :                                                                                      //
// ------------------------------------------------------------------------------------------------ // 
/* 多重インクルードの防止 */
#pragma once
/* ヘッダファイルのインクルード */
#include "Layer.h"
/* クラス宣言 */
class TitleGameLayer :public Layer
{
	/* メンバ変数 */
public:
	/* メンバ関数 */
	// 初期化
	void Initialize(Scene* scene);
	// 更新
	void Update();
	// 描画
	void Draw();
	// 終了
	void Finalize();
};
