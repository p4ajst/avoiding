// ------------------------------------------------------------------------------------------------ //
// @ file	 : Actor.cpp                                                                            //
// @ brief	 : 登場物の基底クラス                                                                   //
// @ date	 : 2017/06/25                                                                           //
// @ author  : Madoka Nakajima                                                                      //
// @ note	 :                                                                                      //
// ------------------------------------------------------------------------------------------------ // 
/* ヘッダファイルのインクルード */
// 先生のフレームワーク
#include "../../ImaseLib/Direct3D.h"
#include "../../ImaseLib/DirectXTK.h"
// 自作ヘッダファイル
#include "Actor.h"

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
void Actor::Initialize()
{
	// メンバ変数の初期化
	mDef = make_shared<DGSLEffectFactory>(g_pd3dDevice.Get());
	mDef->SetDirectory(L"Resources");
	mModel = nullptr;
	mPosition = Vector3(0, 0, 0);
	mAngle = 0;
	mScalingFactor = 1;
	mLocalWorld = Matrix::Identity;
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: 更新                                                                                 //
// @ param	: なし                                                                                 //
// @ return : なし                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void Actor::Update()
{

}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: 描画                                                                                 //
// @ param	: なし                                                                                 //
// @ return : なし                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void Actor::Draw(Matrix view, Matrix proj)
{
	Calc();
	mModel->Draw(g_pImmediateContext.Get(), *g_state, mLocalWorld, view, proj);
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: 終了                                                                                 //
// @ param	: なし                                                                                 //
// @ return : なし                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void Actor::Finalize()
{
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: モデルの読み込み                                                                     //
// @ param	: wchar_t* filename                                                                    //
// @ return : なし                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void Actor::LoadModel(wchar_t * filename)
{
	mModel = Model::CreateFromCMO(g_pd3dDevice.Get(), filename, *mDef);
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: 行列計算                                                                             //
// @ param	: なし                                                                                 //
// @ return : なし                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void Actor::Calc()
{
	Matrix scale;
	Matrix rotate;
	Matrix trans;

	scale = Matrix::CreateScale(mScalingFactor);
	rotate = Matrix::CreateRotationY(XMConvertToRadians(mAngle));
	trans = Matrix::CreateTranslation(mPosition);

	mLocalWorld = scale * rotate * trans;
}
