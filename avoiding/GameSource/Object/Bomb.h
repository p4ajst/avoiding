// ------------------------------------------------------------------------------------------------ //
// @ file	 : Bomb.h                                                                               //
// @ brief	 : 爆弾に関するクラス                                                                   //
// @ date	 : 2017/06/25                                                                           //
// @ author  : Madoka Nakajima                                                                      //
// @ note	 :                                                                                      //
// @ version : ver.3.00                                                                             //
// ------------------------------------------------------------------------------------------------ // 
/* 多重インクルードの防止 */
#pragma once

/* ヘッダファイルのインクルード */
#include <vector>
// 自作ヘッダファイル
#include "Actor.h"
#include "../Stage/Map.h"

/* 定数定義 */
// 重力
static const float GRAVITY = 0.980665f;

/* クラス宣言 */
class Bomb :public Actor
{
	/* メンバ変数 */
private:
	// ボムの配列
	std::vector<std::shared_ptr<Bomb>> mBombs;
	// 速度
	DirectX::SimpleMath::Vector3 mVelocity;
	// map
	std::shared_ptr<Map> mMap;
	// 落下時間
	float mTime;
	// フラグ
	bool mFlag;

	/* メンバ関数 */
public:
	// コンストラクタ
	Bomb() = default;
	// デストラクタ
	~Bomb() = default;
	// 初期化
	void Initialize();
	// 更新
	void Update();
	// 自由落下
	void FreeFall();
	// 座標に速度を足す
	void AddPos();
	// 設定
	void SetVel(DirectX::SimpleMath::Vector3 vel) { mVelocity = vel; }
	//void SetFlag(bool flag) { mFlag = flag; }
	// 取得
	DirectX::SimpleMath::Vector3 GetVel() { return mVelocity; }
	bool GetFlag() { return mFlag; }
};