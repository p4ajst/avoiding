// ------------------------------------------------------------------------------------------------ //
// @ file	 : Character.cpp                                                                        //
// @ brief	 : キャラクターに関するクラス                                                           //
// @ date	 : 2017/06/25                                                                           //
// @ author  : Madoka Nakajima                                                                      //
// @ note	 :                                                                                      //
// @ version : ver.3.00                                                                             //
// ------------------------------------------------------------------------------------------------ // 
/* ヘッダファイルのインクルード */
// 自作ヘッダファイル
#include "Character.h"
#include "../../ImaseLib/DirectXTK.h"

/* 名前空間 */
using namespace DirectX;
using namespace DirectX::SimpleMath;

/* メンバ関数の定義 */
// ----------------------------------------------------------------------------------------------- //
// @ brief	: 移動                                                                                 //
// @ param	: なし                                                                                 //
// @ return : なし                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void Character::Move()
{
	if (g_keyTracker->pressed.A)
	{
		mAngle = 270;
		mVelocity = Vector3(-1, 0, 0);
		mPosition += mVelocity;
		mStepCount += 1;
	}
	if (g_keyTracker->pressed.D)
	{
		mAngle = 90;
		mVelocity = Vector3(1, 0, 0);
		mPosition += mVelocity;
		mStepCount += 1;
	}
	if (g_keyTracker->pressed.W)
	{
		mAngle = 180;
		mVelocity = Vector3(0, 0, -1);
		mPosition += mVelocity;
		mStepCount += 1;
	}
	if (g_keyTracker->pressed.S)
	{
		mAngle = 0;
		mVelocity = Vector3(0, 0, 1);
		mPosition += mVelocity;
		mStepCount += 1;
	}
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: 落下                                                                                 //
// @ param	: なし                                                                                 //
// @ return : なし                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void Character::Fall()
{
	// 重力
	float GRAVITY = 0.980665f;

	// 速度を計算（-重力加速度 ＊ 落下経過時間）
	mVelocity.y = -GRAVITY * 0.0005f;
	mPosition.y += mVelocity.y;
}
