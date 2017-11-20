// ------------------------------------------------------------------------------------------------ //
// @ file	 : Character.cpp                                                                        //
// @ brief	 : キャラクターに関するクラス                                                           //
// @ date	 : 2017/06/25                                                                           //
// @ author  : Madoka Nakajima                                                                      //
// @ note	 :                                                                                      //
// ------------------------------------------------------------------------------------------------ // 
/* ヘッダファイルのインクルード */
// 標準ライブラリ
#include <time.h>
#include <memory>
// 先生のライブラリ
#include "../../ImaseLib/Direct3D.h"
// 自作ヘッダファイル
#include "Character.h"
#include "../../ImaseLib/DirectXTK.h"

/* 名前空間 */
using namespace DirectX;
using namespace DirectX::SimpleMath;

void Character::Initialize(int sx,int sz)
{
	// マップの初期化
	mMap = std::make_shared<Map>(sx,sz);
	// nullチェック
	if (mMap == nullptr)
	{
		return;
	}

	// メンバ変数の初期化
	mDef = std::make_shared<DirectX::DGSLEffectFactory>(g_pd3dDevice.Get());
	mDef->SetDirectory(L"Resources");
	mModel = nullptr;
	mPosition = Vector3(0, 0, 0);
	mAngle = 0;
	mScalingFactor = 1;
	mLocalWorld = Matrix::Identity;

}

/* メンバ関数の定義 */
// ----------------------------------------------------------------------------------------------- //
// @ brief	: 移動                                                                                 //
// @ param	: なし                                                                                 //
// @ return : なし                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void Character::Move(int ox, int oz, int sx, int sz)
{
	Vector3 lerpSpd = Vector3(0, 0, 0);
	Vector3 temp;
	float deltaTime;
	deltaTime = 1.0f / 60.0f;
	if (g_key.A)
	{
		mAngle = 270;
		
		// ポジションを代入
		temp = mPosition;
		// 左に移動
		temp += Vector3(-1.00f,0.0f,0.0f);
		Vector3 mTemp = mPosition;
		for (float i = 0.0f; i < 1.0f; i += deltaTime)
		{
			lerpSpd = Vector3::Lerp(mTemp, temp, deltaTime);
			mPosition = lerpSpd;
		}
		mStepCount++;
	}
	if (g_key.D)
	{
		mAngle = 90;
		// ポジションを代入
		temp = mPosition;
		// 左に移動
		temp += Vector3(1.00f, 0.0f, 0.0f);
		Vector3 mTemp = mPosition;
		for (float i = 0.0f; i < 1.0f; i += deltaTime)
		{
			lerpSpd = Vector3::Lerp(mTemp, temp, deltaTime);
			mPosition = lerpSpd;
		}
		mStepCount++;
	}
	if (g_key.W)
	{
		mAngle = 180;
		// ポジションを代入
		temp = mPosition;
		// 左に移動
		temp += Vector3(0.0f, 0.0f, -1.00f);
		Vector3 mTemp = mPosition;
		for (float i = 0.0f; i < 1.0f; i += deltaTime)
		{
			lerpSpd = Vector3::Lerp(mTemp, temp, deltaTime);
			mPosition = lerpSpd;
		}
		mStepCount++;
	}
	if (g_key.S)
	{
		mAngle = 0;
		// ポジションを代入
		temp = mPosition;
		// 左に移動
		temp += Vector3(0.00f, 0.0f, 1.00f);
		Vector3 mTemp = mPosition;
		for (float i = 0.0f; i < 1.0f; i += deltaTime)
		{
			lerpSpd = Vector3::Lerp(mTemp, temp, deltaTime);
			mPosition = lerpSpd;
			mStepCount++;
		}
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