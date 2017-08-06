// ------------------------------------------------------------------------------------------------ //
// @ file	 : Cursor.cpp                                                                           //
// @ brief	 : カーソルに関するクラス                                                               //
// @ date	 : 2017/06/25                                                                           //
// @ author  : Madoka Nakajima                                                                      //
// @ note	 :                                                                                      //
// @ version : ver.3.00                                                                             //
// ------------------------------------------------------------------------------------------------ // 
/* 多重インクルードの防止 */

/* ヘッダファイルのインクルード */
// 先生のフレームワーク
#include "../../ImaseLib/Direct3D.h"
#include "../../ImaseLib/DirectXTK.h"
// 自作ヘッダファイル
#include "Cursor.h"

/* 名前空間 */
using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

/* メンバ関数の定義 */
// ----------------------------------------------------------------------------------------------- //
// @ brief	: 初期化                                                                               //
// @ param	: int width...クライアント領域の幅                                                     //
// @ param	: int height...クライアント領域の高さ                                                  //
// @ return : なし                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void Cursor::Initialize(int width, int height)
{
	// メンバ変数の初期化
	mDef = make_shared<DGSLEffectFactory>(g_pd3dDevice.Get());
	mDef->SetDirectory(L"Resources");
	mModel = nullptr;
	mPosition = Vector3(0, 0, 0);
	mAngle = 0;
	mScalingFactor = 1;
	mLocalWorld = Matrix::Identity;

	mMouseCursor = make_shared<MouseCursor>(width, height);
	mMouseCursor->Initialize();
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: 更新                                                                                 //
// @ param	: なし                                                                                 //
// @ return : なし                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void Cursor::Update()
{
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: 更新                                                                                 //
// @ param	: float ox...オフセットのｘ                                                            //
// @ param	: float oz...オフセットのｚ                                                            //
// @ return : なし                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void Cursor::Update(float ox, float oz)
{

}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: 描画                                                                                 //
// @ param	: なし                                                                                 //
// @ return : なし                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void Cursor::Draw(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj)
{
	mMouseCursor->Calc(view, proj);
	/*
		brief    :描画
		param[in]:コンテキスト
		param[in]:ステート
		param[in]:ワールド行列
		param[in]:ビュー行列
		param[in]:射影行列
		param[in]:ワイヤーフレームかどうか
		param[in]:ラムダ式
	*/
	mModel->Draw(g_pImmediateContext.Get(), *g_state.get(), mLocalWorld, view, proj, false,
		[&]()
	{
		// ブレンドステートの設定（半透明）
		g_pImmediateContext->OMSetBlendState(g_state->NonPremultiplied(), nullptr, 0xffffffff);
	});
}
