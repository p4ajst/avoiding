// ------------------------------------------------------------------------------------------------ //
// @ file	 : TitleScene.h                                                                         //
// @ brief	 : タイトルシーンのヘッダファイル                                                       //
// @ date	 : 2017/05/02                                                                           //
// @ author  : Madoka Nakajima                                                                      //
// @ note	 :                                                                                      //
// ------------------------------------------------------------------------------------------------ // 
/* 多重インクルードの防止 */
#pragma once 
/* ヘッダファイルのインクルード */
#include <memory>
#include <Effects.h>
// 先生のフレームワーク
#include "../../ImaseLib/Texture.h"
// 自作ヘッダファイル（基底クラスのヘッダファイル）
#include "Scene.h"
#include "../Layer/TitleBackGroundLayer.h"
#include "../Layer/TitleGameLayer.h"
#include "../Layer/TitleHUDLayer.h"

/* クラス宣言 */
class TitleScene :public Scene
{
	/* メンバ変数 */
	// 背景レイヤー
	std::unique_ptr<TitleBackGroundLayer> mBackGround;
	// ゲームレイヤー
	std::unique_ptr<TitleGameLayer> mGame;
	// HUDレイヤー
	std::unique_ptr<TitleHUDLayer> mHUD;

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
};
