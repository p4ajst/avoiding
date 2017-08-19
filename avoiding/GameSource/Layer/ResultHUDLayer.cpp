// ------------------------------------------------------------------------------------------------ //
// @ file	 : ResultHUDLayer.cpp                                                                   //
// @ brief	 : ヘッドアップディスプレイ部分のクラス                                                 //
// @ date	 : 2017/07/10                                                                           //
// @ author  : Madoka Nakajima                                                                      //
// @ note	 :                                                                                      //
// ------------------------------------------------------------------------------------------------ // 
// 先生のフレームワーク
#include "../../ImaseLib/DirectXTK.h"
// 自作ヘッダファイル
#include "ResultHUDLayer.h"

/* 名前空間 */
using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

/* メンバ関数の定義 */
// ----------------------------------------------------------------------------------------------- //
// @ brief	: 初期化処理                                                                           //
// @ param	: Scene* scene...どのシーンか                                                          //
// @ return : なし                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void ResultHUDLayer::Initialize(Scene* scene)
{
	pScene = scene;

	// 画像描画用変数
	mBeforeFrog = make_unique<Texture>(L"Resources\\frog_before.png");
	mAfterFrog = make_unique<Texture>(L"Resources\\frog_After.png");
	mBeforeDoor = make_unique<Texture>(L"Resources\\door_before.png");
	mAfterDoor = make_unique<Texture>(L"Resources\\door_After.png");
	mGameClear = make_unique<Texture>(L"Resources\\GameClear.png");
	mGameOver = make_unique<Texture>(L"Resources\\GameOver.png");

	// 判定用フラグ
	mfFlag = false;
	mdFlag = false;
	// 画像の描画範囲
	mFrog.left = 200;
	mFrog.top = 600;
	mFrog.right = 456;
	mFrog.bottom = 856;
	mDoor.left = 700;
	mDoor.top = 500;
	mDoor.right = 956;
	mDoor.bottom = 756;
	mDoorA.left = 700;
	mDoorA.top = 500;
	mDoorA.right = 1120;
	mDoorA.bottom = 890;

	// シーン切替用変数の初期化
	mSceneFlag = false;
	// 描画用変数の初期化
	mResultFlag = false;
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: 更新処理                                                                             //
// @ param	: なし                                                                                 //
// @ return : なし                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void ResultHUDLayer::Update()
{
	// カエルの範囲内にカーソルがあれば
	if (g_mouse.x >= mFrog.left && g_mouse.x <= mFrog.right &&
		g_mouse.y >= mFrog.top && g_mouse.y <= mFrog.bottom)
	{
		// フラグを切り替える
		mfFlag = true;
		// 左クリックされたら
		if (g_mouseTracker->leftButton == Mouse::ButtonStateTracker::RELEASED)
		{
			// フラグを切り替える
			mSceneFlag = true;
		}
	}
	// そうでなければ
	else
	{
		// フラグを切り替えない
		mfFlag = false;
	}
	// ドアの範囲内にカーソルがあれば
	if (g_mouse.x >= mDoor.left && g_mouse.x <= mDoor.right &&
		g_mouse.y >= mDoor.top && g_mouse.y <= mDoor.bottom)
	{
		// フラグを切り替える
		mdFlag = true;
		// 左クリックされたら
		if (g_mouseTracker->leftButton == Mouse::ButtonStateTracker::RELEASED)
		{
			// ウインドウを閉じる
			PostQuitMessage(0);
		}
	}
	// そうでなければ
	else
	{
		// フラグを切り替えない
		mdFlag = false;
	}
}


// ----------------------------------------------------------------------------------------------- //
// @ brief	: 描画処理                                                                             //
// @ param	: なし                                                                                 //
// @ return : なし                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void ResultHUDLayer::Draw()
{
	// 画像の描画
	
	// 描画位置（l,t,r,b）;
	RECT rect{ 0,0,1280,480 };

	// リザルトフラグが真であるなら
	if (mResultFlag)
	{
		// ゲームクリア
		pScene->GetSprite()->Draw(mGameClear->m_pTexture, rect, Colors::White);
	}
	// リザルトフラグが偽であるなら
	else
	{
		// ゲームオーバー
		pScene->GetSprite()->Draw(mGameOver->m_pTexture, rect, Colors::White);
	}

	// カエルフラグが偽であるなら
	if (!mfFlag)
	{
		pScene->GetSprite()->Draw(mBeforeFrog->m_pTexture, mFrog, Colors::White);
	}
	// カエルフラグが真であるなら
	else
	{
		pScene->GetSprite()->Draw(mAfterFrog->m_pTexture, mFrog, Colors::White);
	}
	// ドアフラグが偽であるなら
	if (!mdFlag)
	{
		pScene->GetSprite()->Draw(mBeforeDoor->m_pTexture, mDoorA, Colors::White);
	}
	// ドアフラグ真であるなら
	else
	{
		pScene->GetSprite()->Draw(mAfterDoor->m_pTexture, mDoorA, Colors::White);
	}
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: 終了処理                                                                             //
// @ param	: なし                                                                                 //
// @ return : なし                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void ResultHUDLayer::Finalize()
{
}
