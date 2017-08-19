// ------------------------------------------------------------------------------------------------ //
// @ file	 : ResultScene.cpp                                                                      //
// @ brief	 : リザルトシーンのソースファイル                                                       //
// @ date	 : 2017/05/02                                                                           //
// @ author  : Madoka Nakajima                                                                      //
// @ note	 :                                                                                      //
// ------------------------------------------------------------------------------------------------ // 

/* ヘッダファイルのインクルード */
// 標準ライブラリ
#include <simplemath.h>
// 先生のフレームワーク
#include "../../ImaseLib/Direct3D.h"
#include "../../ImaseLib/DirectXTK.h"
// 自作ヘッダファイル
#include "ResultScene.h"
#include "TitleScene.h"
#include "../Utility/Common.h"


/* 名前空間 */
using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

/* メンバ関数の定義 */
// ----------------------------------------------------------------------------------------------- //
// @ brief	: 初期化処理                                                                           //
// @ param	: int width,int height...画面サイズ                                                    //
// @ return : なし                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void ResultScene::Initialize(int width, int height)
{
	// スプライトバッチの生成
	pSprite = make_shared<SpriteBatch>(g_pImmediateContext.Get());
	// カメラの生成
	pCamera = make_shared<Camera>();

	// 背景レイヤーの生成
	mBackGround = make_unique<ResultBackGroundLayer>();
	// 背景レイヤーの初期化
	mBackGround->Initialize(this);
	// ゲームレイヤーの生成
	mGame = make_unique<ResultGameLayer>();
	// ゲームレイヤーの初期化
	mGame->Initialize(this);
	// HUDレイヤーの生成
	mHUD = make_unique<ResultHUDLayer>();
	// HUDレイヤーの初期化
	mHUD->Initialize(this);
	// シーン切替用変数の初期化
	mSceneFlag = false;
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: 更新処理                                                                             //
// @ param	: なし                                                                                 //
// @ return : なし                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void ResultScene::Update()
{
	// 背景レイヤーの更新
	mBackGround->Update();
	// ゲームレイヤーの更新
	mGame->Update();
	// HUDレイヤーの更新
	mHUD->Update();

#pragma region Debug
	// F1キーが押されたら
	if (g_key.F3)
	{
		// シーンを遷移する
		mSceneFlag = true;
	}

	// Escapeキーを押したら
	if (g_key.Escape)
	{
		// ウインドウを閉じる
		PostQuitMessage(0);
	}
#pragma endregion デバッグ用機能
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: 描画処理                                                                             //
// @ param	: Matrix view,Matrix proj...ビュー行列とプロジェクション行列                           //
// @ return : なし                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void ResultScene::Render()
{
	// 背景レイヤーの描画
	mBackGround->Draw();
	// ゲームレイヤーの描画
	mGame->Draw();
	// スプライトバッチの始まり（半透明処理）
	pSprite->Begin(SpriteSortMode_Deferred, nullptr, nullptr, nullptr, nullptr, [=]
	{
		// 画像の半透明処理
		g_pImmediateContext->OMSetBlendState(g_state->NonPremultiplied(), nullptr, 0xFFFFFFFF);
	});
	mHUD->SetResultFlag(mResultFlag);
	// HUDレイヤーの描画
	mHUD->Draw();
	// スプライトバッチの終わり
	pSprite->End();
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: 終了処理                                                                             //
// @ param	: なし                                                                                 //
// @ return : なし                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void ResultScene::Finalize()
{
	mGame->Finalize();
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: シーン遷移                                                                           //
// @ param	: なし                                                                                 //
// @ return : Scene*...基底クラスのポインタ                                                       //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
Scene* ResultScene::Change()
{
	// ゲームレイヤーからフラグを取得
	mSceneFlag = mHUD->GetFlag();
	// フラグが真なら（フラグが偽でなかったら）
	if (mSceneFlag != false)
	{
		// 次のシーンのポインタを返す
		return new TitleScene();
	}
	// そうでなかったら
	else
	{
		// nullptrを返す
		return nullptr;
	}
}
