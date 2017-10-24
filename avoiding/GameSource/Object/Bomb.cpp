// ------------------------------------------------------------------------------------------------ //
// @ file	 : Bomb.cpp                                                                             //
// @ brief	 : 爆弾に関するクラス                                                                   //
// @ date	 : 2017/06/25                                                                           //
// @ author  : Madoka Nakajima                                                                      //
// @ note	 :                                                                                      //
// @ version : ver.3.00                                                                             //
// ------------------------------------------------------------------------------------------------ // 
/* ヘッダファイルのインクルード */
// 先生のフレームワーク
#include "../../ImaseLib/Direct3D.h"
// 自作ヘッダファイル
#include "Bomb.h"
#include "../Utility/Shader.h"


/* 名前空間 */
using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

/* メンバ関数の定義 */
// ----------------------------------------------------------------------------------------------- //
// @ brief	: 初期化                                                                               //
// @ param	: なし                                                                                 //
// @ return : なし                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void Bomb::Initialize()
{
	// メンバ変数の初期化
	mDef = make_shared<DGSLEffectFactory>(g_pd3dDevice.Get());
	mDef->SetDirectory(L"Resources");
	mModel = nullptr;
	mPosition = Vector3(0, 0, 0);
	mVelocity = Vector3(0, 0, 0);
	mAngle = 0;
	mScalingFactor = 1;
	mLocalWorld = Matrix::Identity;
	mTime = 0;
	mFlag = true;
	mnLib::InitShader(L"Resources\\dogbomb1.cmo");
	mnLib::CreateShader("VertexLight.cso", "PixelLight.cso");
	mnLib::CreateConstantBuffer();
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: 更新                                                                                 //
// @ param	: なし                                                                                 //
// @ return : なし                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void Bomb::Update()
{
	FreeFall();
	AddPos();
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: 自由落下                                                                             //
// @ param	: なし                                                                                 //
// @ return : なし                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void Bomb::FreeFall()
{
	// 60フレームに1回
	float delta = 1.0f / 60.0f;
	// 落下時間を加算
	mTime = mTime + delta;
	// 速度を計算（-重力加速度 ＊ 落下経過時間）
	mVelocity.y = -GRAVITY * 0.5f;
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: 速度を座標に加算                                                                     //
// @ param	: なし                                                                                 //
// @ return : なし                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void Bomb::AddPos()
{
	mPosition = mPosition + mVelocity;
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: 描画                                                                                 //
// @ param	: なし                                                                                 //
// @ return : なし                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void Bomb::Draw(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj)
{
	mnLib::Draw(view, proj);
}
