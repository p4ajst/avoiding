// ------------------------------------------------------------------------------------------------ //
// @ file	 : TitleBackGroundLayer.h                                                               //
// @ brief	 : 背景レイヤー                                                                         //
// @ date	 : 2017/07/10                                                                           //
// @ author  : Madoka Nakajima                                                                      //
// @ note	 :                                                                                      //
// @ version : ver.3.00                                                                             //
// ------------------------------------------------------------------------------------------------ // 
/* 多重インクルードの防止 */
#pragma once
/* ヘッダファイルのインクルード */
#include "Layer.h"
/* クラス宣言 */
class TitleBackGroundLayer :public Layer
{
	/* メンバ変数 */
	bool mSceneFlag;
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
