// ------------------------------------------------------------------------------------------------ //
// @ file	 : ResultScene.h                                                                        //
// @ brief	 : リザルトシーンのヘッダファイル                                                       //
// @ date	 : 2017/05/02                                                                           //
// @ author  : Madoka Nakajima                                                                      //
// @ note	 :                                                                                      //
// ------------------------------------------------------------------------------------------------ // 
/* 多重インクルードの防止 */
#pragma once 
/* ヘッダファイルのインクルード */
// 自作ヘッダファイル（基底クラスのヘッダファイル）
#include "Scene.h"
// 自作ヘッダファイル
#include "../Layer/ResultBackGroundLayer.h"
#include "../Layer/ResultGameLayer.h"
#include "../Layer/ResultHUDLayer.h"

/* クラス宣言 */
class ResultScene :public Scene
{
	/* メンバ変数 */
	// 背景レイヤー
	std::unique_ptr<ResultBackGroundLayer> mBackGround;
	// ゲームレイヤー
	std::unique_ptr<ResultGameLayer> mGame;
	// HUDレイヤー
	std::unique_ptr<ResultHUDLayer> mHUD;
	// 描画画像変更用
	bool mResultFlag;

	/* メンバ関数 */
public:
	// 初期化処理
	void Initialize(int width, int height);
	// 更新処理
	void Update();
	// 描画処理
	void Render();
	// 終了処理
	void Finalize();
	// シーン遷移
	Scene* Change();
	// フラグの設定
	void SetResultFlag(bool flag) { mResultFlag = flag; }
};
