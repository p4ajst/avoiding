// ------------------------------------------------------------------------------------------------ //
// @ file	 : Game.h                                                                               //
// @ brief	 : ゲーム全体を管理するクラス                                                           //
// @ date	 : 2017/06/25                                                                           //
// @ author  : Madoka Nakajima                                                                      //
// @ note	 :                                                                                      //
// @ version : ver.3.00                                                                             //
// ------------------------------------------------------------------------------------------------ // 
/* 多重インクルードの防止 */
#pragma once
/* ヘッダファイルのインクルード */
// 標準ライブラリ
#include <simplemath.h>
// 自作ヘッダファイル
#include "Scene\Scene.h"
#include "Scene\TitleScene.h"
#include "Scene\PlayScene.h"
#include "Scene\ResultScene.h"

/* クラス宣言 */
class Game
{
	/* メンバ変数 */
private:
	// シーンクラス
	Scene* mScene;
	// クライアント領域の大きさ
	int mClientSizeW;
	int mClientSizeH;

	/* メンバ関数 */
public:
	// 初期化
	void Initialize(int width, int height);
	// 更新
	void Update();
	// 描画
	void Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);
	// 終了
	void Finalize();
};
