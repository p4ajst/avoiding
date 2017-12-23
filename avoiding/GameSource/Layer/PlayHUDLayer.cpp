// ------------------------------------------------------------------------------------------------ //
// @ file	 : HUDLayer.cpp                                                                         //
// @ brief	 : ヘッドアップディスプレイ部分のクラス                                                 //
// @ date	 : 2017/06/30                                                                           //
// @ author  : Madoka Nakajima                                                                      //
// @ note	 :                                                                                      //
// ------------------------------------------------------------------------------------------------ // 
/* ヘッダファイルのインクルード */
// 先生のフレームワーク
#include "../../ImaseLib/DirectXTK.h"
// 自作ヘッダファイル
#include "PlayHUDLayer.h"
#include "../Utility/Common.h"

/* 名前空間 */
using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

/* メンバ関数の定義 */
// ----------------------------------------------------------------------------------------------- //
// @ brief	: 初期化                                                                               //
// @ param	: Scene* scene...シーンのポインタ                                                      //
// @ return : なし                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void PlayHUDLayer::Initialize(Scene* scene)
{
	// 現在のシーンを代入
	pScene = scene;
	// 数字のテクスチャの生成
	mNum = make_unique<Texture>(L"Resources\\number.png");
	// ビスケットのテクスチャの生成
	mBiscuitBefore = make_unique<Texture>(L"Resources\\Biscuit_before.png");
	// ビスケットのテクスチャの生成
	mBiscuitAfter = make_unique<Texture>(L"Resources\\Biscuit_after.png");

	// ビスケットの描画範囲の設定
	mBisrect.left = 1211;
	mBisrect.top = 40;
	mBisrect.right = 1275;
	mBisrect.bottom = 104;

	// ポーズフラグの初期化
	mPauseFlag = false;
	// ビスケットの描画範囲内にマウスカーソルがあるか
	mpFrag = false;
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: 更新                                                                                 //
// @ param	: なし                                                                                 //
// @ return : なし                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void PlayHUDLayer::Update()
{
	//// スタートスクリーンの更新
	//mStart->Update();

	// ビスケットの範囲内にカーソルがあれば
	if (g_mouse.x >= mBisrect.left && g_mouse.x <= mBisrect.right &&
		g_mouse.y >= mBisrect.top && g_mouse.y  <= mBisrect.bottom)
	{
		// フラグを切り替える
		mpFrag = true;
		// 左クリックされたら
		auto bottom = g_mouseTracker->GetLastState();
		if (g_mouseTracker->leftButton == Mouse::ButtonStateTracker::RELEASED)
		{
			if (!mPauseFlag)
			{
				// フラグを切り替える
				mPauseFlag = true;
			}
			else
			{
				// フラグを切り替える
				mPauseFlag = false;
			}
		}
	}
	// そうでなければ
	else
	{
		// フラグを切り替えない
		mpFrag = false;
	}
}


// ----------------------------------------------------------------------------------------------- //
// @ brief	: 描画                                                                                 //
// @ param	: なし                                                                                 //
// @ return : なし                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void PlayHUDLayer::Draw()
{
	// ビスケットの描画範囲内にマウスカーソルがなければ
	if (!mpFrag)
	{
		// ビスケットの画像を描画
		pScene->GetSprite()->Draw(mBiscuitBefore->m_pTexture, mBisrect, Colors::White);
	}
	// そうでなければ
	else
	{
		// ビスケットの画像を描画
		pScene->GetSprite()->Draw(mBiscuitAfter->m_pTexture, mBisrect, Colors::White);
	}

	// 歩数を描画
	DrawNum(pScene->GetSprite().get(), mNum->m_pTexture, mCount, 160.0f, 32.0f);
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: 終了                                                                                 //
// @ param	: なし                                                                                 //
// @ return : なし                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void PlayHUDLayer::Finalize()
{
}
