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

#include "GameStartScreen.h"
#include "PauseScreen.h"

/* クラス宣言 */
class PlayScene :public Scene
{
	/* 列挙体 */
	enum PlayState
	{
		START,
		GAME,
		PAUSE
	};

	/* メンバ変数 */
	// 背景レイヤー
	std::unique_ptr<PlayBackGroundLayer> mBackGround;
	// ゲームレイヤー
	std::unique_ptr<PlayGameLayer> mGame;
	// HUDレイヤー
	std::unique_ptr<PlayHUDLayer> mHUD;
	// ゲーム開始前のカウンタ
	std::unique_ptr<GameStartScreen> mStart;
	// ポーズ画面
	std::unique_ptr<PauseScreen> mPause;
	// 状態遷移用変数
	PlayState mState;
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
