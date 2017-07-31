// ------------------------------------------------------------------------------------------------ //
// @ file	 : TitleHUDLayer.cpp                                                                    //
// @ brief	 : ヘッドアップディスプレイ部分のクラス                                                 //
// @ date	 : 2017/07/10                                                                           //
// @ author  : Madoka Nakajima                                                                      //
// @ note	 :                                                                                      //
// @ version : ver.3.00                                                                             //
// ------------------------------------------------------------------------------------------------ // 
/* ヘッダファイルのインクルード */
// 先生のフレームワーク
#include "../../ImaseLib/DirectXTK.h"
// 自作ヘッダファイル
#include "TitleHUDLayer.h"
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
void TitleHUDLayer::Initialize(Scene * scene)
{
	// シーン遷移用変数
	pScene = scene;

	// 画像描画用変数の生成
	mGraph = make_unique<Texture>(L"Resources\\Title3.png");
	mBeforeStart = make_unique<Texture>(L"Resources\\Start_Before.png");
	mAfterStart = make_unique<Texture>(L"Resources\\Start_After.png");
	mBeforeEnd = make_unique<Texture>(L"Resources\\End_Before.png");
	mAfterEnd = make_unique<Texture>(L"Resources\\End_After.png");
	// 判定用フラグ
	msFlag = false;
	meFlag = false;

	// 画像の描画範囲
	mStart.left   = 425;
	mStart.top    = 400;
	mStart.right  = 825;
	mStart.bottom = 610;

	mEnd.left     = 425;
	mEnd.top      = 650;
	mEnd.right    = 825;
	mEnd.bottom   = 860;

	// シーン切替用変数の初期化
	mSceneFlag = false;
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: 更新                                                                                 //
// @ param	: なし                                                                                 //
// @ return : なし                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void TitleHUDLayer::Update()
{
	// Startの範囲にカーソルが入ったら
	if (g_mouse.x >= mStart.left && g_mouse.x <= mStart.right &&
		g_mouse.y >= mStart.top && g_mouse.y <= mStart.bottom)
	{
		msFlag = true;
		// 左クリックされたら
		if (g_mouseTracker->leftButton == Mouse::ButtonStateTracker::RELEASED)
		{
			// フラグを切り替える
			mSceneFlag = true;
		}
	}
	else
	{
		msFlag = false;
	}
	if (g_mouse.x >= mEnd.left && g_mouse.x <= mEnd.right &&
		g_mouse.y >= mEnd.top && g_mouse.y <= mEnd.bottom)
	{
		meFlag = true;
		// 左クリックされたら
		if (g_mouseTracker->leftButton == Mouse::ButtonStateTracker::RELEASED)
		{
			// ウインドウを閉じる
			PostQuitMessage(0);
		}
	}
	else
	{
		meFlag = false;
	}
}


// ----------------------------------------------------------------------------------------------- //
// @ brief	: 描画                                                                                 //
// @ param	: なし                                                                                 //
// @ return : なし                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void TitleHUDLayer::Draw()
{
	// 画像の描画範囲
	RECT rect{ 0,0,1280,480 };
	// 画像の描画
	pScene->GetSprite()->Draw(mGraph->m_pTexture, rect, DirectX::Colors::White);
	// スタートフラグが偽であるなら
	if (!msFlag)
	{
		pScene->GetSprite()->Draw(mBeforeStart->m_pTexture, mStart, DirectX::Colors::White);
	}
	// スタートフラグが真であるなら
	else
	{
		pScene->GetSprite()->Draw(mAfterStart->m_pTexture, mStart, DirectX::Colors::White);
	}
	// エンドフラグが偽であるなら
	if (!meFlag)
	{
		pScene->GetSprite()->Draw(mBeforeEnd->m_pTexture, mEnd, DirectX::Colors::White);
	}
	// エンドフラグが真であるなら
	else
	{
		pScene->GetSprite()->Draw(mAfterEnd->m_pTexture, mEnd, DirectX::Colors::White);
	}
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: 終了                                                                                 //
// @ param	: なし                                                                                 //
// @ return : なし                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void TitleHUDLayer::Finalize()
{
}
