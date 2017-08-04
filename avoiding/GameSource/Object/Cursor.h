// ------------------------------------------------------------------------------------------------ //
// @ file	 : Cursor.h                                                                             //
// @ brief	 : カーソルに関するクラス                                                           //
// @ date	 : 2017/06/25                                                                           //
// @ author  : Madoka Nakajima                                                                      //
// @ note	 :                                                                                      //
// @ version : ver.3.00                                                                             //
// ------------------------------------------------------------------------------------------------ // 
/* 多重インクルードの防止 */
#pragma once
/* ヘッダファイルのインクルード */
// 自作ヘッダファイル
#include "Actor.h"
#include "../Utility/MouseCursor.h"

/* クラス宣言 */
class Cursor :public Actor
{
	/* メンバ変数 */
	// マウス制御
	std::shared_ptr<MouseCursor> mMouseCursor;
	/* メンバ関数 */
public:
	// コンストラクタ
	Cursor() = default;
	// デストラクタ
	~Cursor() = default;
	// 初期化
	void Initialize(int width, int height);
	// 更新
	void Update();
	void Update(float ox, float oz);
	// 描画
	void Draw(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);
	// 取得
	std::shared_ptr<MouseCursor> GetCursor() { return mMouseCursor; }
};