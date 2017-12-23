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

/* 定数定義 */
// フレーム数
static const int frame = 10;

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

	// 移動中でない = 待機中
	mIsMoving = false;
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
	// 待機中
	if (!mIsMoving)
	{
		// キャラクターの現在地を移動のスタート地点にする
		mSource = mPosition;

		// キー入力
		if (g_key.A)
		{
			// 移動方向を設定
			mAngle = 270;
			// 目的地の設定
			mDestination = mSource + Vector3::Left;
			mIsMoving = true;
		}
		if (g_key.D)
		{
			// 移動方向を設定
			mAngle = 90;
			// 目的地の設定
			mDestination = mSource + Vector3::Right;
			mIsMoving = true;
		}
		if (g_key.W)
		{
			// 移動方向を設定
			mAngle = 180;
			// 目的地の設定
			mDestination = mSource + Vector3::Forward;
			mIsMoving = true;
		}
		if (g_key.S)
		{
			// 移動方向を設定
			mAngle = 0;
			// 目的地の設定
			mDestination = mSource + Vector3::Backward;
			mIsMoving = true;
		}
		if (mIsMoving)
		{
			// 歩数をカウント
			mStepCount++;
			// 移動割合を０にする
			mMoveRate = 0;
		}
	}
	// 移動中
	else
	{
		// 割合を追加
		mMoveRate++;

		// 座標を変更する
		/// Vector3::SmoothStep()
		/// brief : 補間をする
		/// param : 開始点
		/// param : 終着点
		/// param : どこまで移動したか
		mPosition = Vector3::SmoothStep(mSource, mDestination, mMoveRate / (float)frame);


		// 移動割合がフレーム数だったら
		if (mMoveRate == frame)
		{
			mIsMoving = false;
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