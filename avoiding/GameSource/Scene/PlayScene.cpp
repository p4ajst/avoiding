// ------------------------------------------------------------------------------------------------ //
// @ file	 : PlayScene.cpp                                                                        //
// @ brief	 : ゲームシーンのソースファイル                                                         //
// @ date	 : 2017/05/02                                                                           //
// @ author  : Madoka Nakajima                                                                      //
// @ note	 :                                                                                      //
// @ version : ver.3.00                                                                             //
// ------------------------------------------------------------------------------------------------ // 
/* ヘッダファイルのインクルード */
#include <SpriteBatch.h>
// 先生のフレームワーク
#include "../../ImaseLib/Direct3D.h"
#include "../../ImaseLib/DirectXTK.h"
// 自作ヘッダファイル
#include "PlayScene.h"
#include "ResultScene.h"

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
void PlayScene::Initialize(int width, int height)
{
	// スプライトバッチの生成
	pSprite = make_shared<SpriteBatch>(g_pImmediateContext.Get());
	// カメラの生成
	pCamera = make_shared<Camera>();
	// シーン遷移用変数の初期化（falseにすることで遷移しない）
	mSceneFlag = false;
	// 背景レイヤーの生成
	mBackGround = make_unique<PlayBackGroundLayer>();
	// 背景レイヤーの初期化
	mBackGround->Initialize(this);
	// ゲームレイヤーの生成
	mGame = make_unique<PlayGameLayer>();
	// ゲームレイヤーの初期化
	mGame->Initialize(this,width, height);
	// HUDレイヤーの生成
	mHUD = make_unique<PlayHUDLayer>();
	// HUDレイヤーの初期化
	mHUD->Initialize(this);
	// リザルトの文字フラグ
	mResultFlag = false;
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: 更新                                                                                 //
// @ param	: なし                                                                                 //
// @ return : なし　                                                                               //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void PlayScene::Update()
{
	// 視点の設定
	pCamera->SetEye(Vector3(0.0f, 15.0f, 25.0f));
	pCamera->SetRef(Vector3(0.0f, 0.0f, 0.0f));
	// 背景レイヤーの更新
	mBackGround->Update();
	// ゲームレイヤーの更新
	mGame->SetPauseFlag(mHUD->GetPauseFlag());
	mGame->SetStartFlag(mHUD->GetStartFlag());
	mGame->Update();
	// HUDレイヤーの更新
	mHUD->SetStartFlag(mGame->GetStartFlag());
	mHUD->Update();
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: 描画                                                                                 //
// @ param	: Matrix view...ビュー行列                                                             //
// @ param	: Matrix proj...射影行列                                                               //
// @ return : なし                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void PlayScene::Render()
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
	// ゲームで取得したカウンタを設定
	mHUD->SetCount(mGame->GetCount());
	// HUDレイヤーの描画
	mHUD->Draw();
	// スプライトバッチの終わり
	pSprite->End();
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: 終了                                                                                 //
// @ param	: なし                                                                                 //
// @ return : なし                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void PlayScene::Finalize()
{
	mGame->Finalize();
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: シーン遷移                                                                           //
// @ param	: なし                                                                                 //
// @ return : Scene*...基底クラスのポインタ                                                       //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
Scene* PlayScene::Change()
{
	// ゲームレイヤーからフラグを取得
	mSceneFlag = mGame->GetFlag();
	mResultFlag = mGame->GetResultFlag();
	// フラグが真なら（フラグが偽でなかったら）
	if (mSceneFlag != false)
	{
		// 次のシーンのポインタを返す
		auto sceneFlag = new ResultScene();
		sceneFlag->SetResultFlag(mResultFlag);
		return sceneFlag;
	}
	// そうでなかったら
	else
	{
		// nullptrを返す
		return nullptr;
	}
}
