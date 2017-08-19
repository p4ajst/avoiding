// ------------------------------------------------------------------------------------------------ //
// @ file	 : PlayScene.h                                                                          //
// @ brief	 : ゲームシーンのヘッダファイル                                                         //
// @ date	 : 2017/05/02                                                                           //
// @ author  : Madoka Nakajima                                                                      //
// @ note	 :                                                                                      //
// ------------------------------------------------------------------------------------------------ // 
/* 多重インクルードの防止 */
#pragma once 
/* ヘッダファイルのインクルード */
// 標準ライブラリ
#include <d3d11.h>
#include <simplemath.h>
#include <memory>
// 自作ヘッダファイル（基底クラスのヘッダファイル）
#include "Scene.h"
// 自作ヘッダファイル
#include "../Layer/PlayHUDLayer.h"
#include "../Layer/PlayGameLayer.h"
#include "../Layer/PlayBackGroundLayer.h"

/* クラス宣言 */
class PlayScene :public Scene
{
	/* メンバ変数 */
	// 背景レイヤー
	std::unique_ptr<PlayBackGroundLayer> mBackGround;
	// ゲームレイヤー
	std::unique_ptr<PlayGameLayer> mGame;
	// HUDレイヤー
	std::unique_ptr<PlayHUDLayer> mHUD;
	// 描画判定フラグ
	bool mResultFlag;
public:
	/* メンバ関数 */
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
};
