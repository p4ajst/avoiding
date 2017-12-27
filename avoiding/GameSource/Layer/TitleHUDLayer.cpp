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
	start.graphB = make_unique<Texture>(L"Resources\\Start_Before.png");
	start.graphA = make_unique<Texture>(L"Resources\\Start_After.png");
	end.graphB = make_unique<Texture>(L"Resources\\End_Before.png");
	end.graphA = make_unique<Texture>(L"Resources\\End_After.png");

	// 画像描画用変数の生成
	mGraph = make_unique<Texture>(L"Resources\\Title3.png");
	
	// 判定用フラグ
	start.flag = false;
	end.flag = false;

	//// 画像の描画範囲
	//start.range.left   = 425;
	//start.range.top    = 400;
	//start.range.right  = 825;
	//start.range.bottom = 610;
	//end.range.left     = 425;
	//end.range.top      = 650;
	//end.range.right    = 825;
	//end.range.bottom   = 860;


	// 画像の描画範囲
	start.range.left = 200;
	start.range.top = 500;
	start.range.right = 600;
	start.range.bottom = 710;
	end.range.left = 680;
	end.range.top = 500;
	end.range.right = 1080;
	end.range.bottom = 710;


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
	if (g_mouse.x >= start.range.left && g_mouse.x <= start.range.right &&
		g_mouse.y >= start.range.top && g_mouse.y <= start.range.bottom)
	{
		start.flag = true;
		// 左クリックされたら
		if (g_mouseTracker->leftButton == Mouse::ButtonStateTracker::RELEASED)
		{
			// フラグを切り替える
			mSceneFlag = true;
		}
	}
	else
	{
		start.flag = false;
	}
	if (g_mouse.x >= end.range.left && g_mouse.x <= end.range.right &&
		g_mouse.y >= end.range.top && g_mouse.y <= end.range.bottom)
	{
		end.flag = true;
		// 左クリックされたら
		if (g_mouseTracker->leftButton == Mouse::ButtonStateTracker::RELEASED)
		{
			// ウインドウを閉じる
			PostQuitMessage(0);
		}
	}
	else
	{
		end.flag = false;
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
	if (!start.flag)
	{
		pScene->GetSprite()->Draw(start.graphB->m_pTexture, start.range, DirectX::Colors::White);
	}
	// スタートフラグが真であるなら
	else
	{
		pScene->GetSprite()->Draw(start.graphA->m_pTexture, start.range, DirectX::Colors::White);
	}
	// エンドフラグが偽であるなら
	if (!end.flag)
	{
		pScene->GetSprite()->Draw(end.graphB->m_pTexture, end.range, DirectX::Colors::White);
	}
	// エンドフラグが真であるなら
	else
	{
		pScene->GetSprite()->Draw(end.graphA->m_pTexture, end.range, DirectX::Colors::White);
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
