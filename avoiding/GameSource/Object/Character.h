// ------------------------------------------------------------------------------------------------ //
// @ file	 : Character.h                                                                          //
// @ brief	 : キャラクターに関するクラス                                                           //
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

/* クラス宣言 */
class Character :public Actor
{
	/* メンバ変数 */
private:
	// 速度
	DirectX::SimpleMath::Vector3 mVelocity;
	// 歩数
	int mStepCount;
	/* メンバ関数 */
public:
	// コンストラクタ
	Character() = default;
	// デストラクタ
	~Character() = default;
	// 移動
	void Move();
	// 落下
	void Fall();
	// 設定
	void SetVel(DirectX::SimpleMath::Vector3 vel) { mVelocity = vel; }
	// 取得
	DirectX::SimpleMath::Vector3 GetVel() { return mVelocity; }
	int GetCount() { return mStepCount; }
};
