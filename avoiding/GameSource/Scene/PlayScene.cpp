// ------------------------------------------------------------------------------------------------ //
// @ file	 : PlayScene.cpp                                                                        //
// @ brief	 : ゲームシーンのソースファイル                                                         //
// @ date	 : 2017/05/02                                                                           //
// @ author  : Madoka Nakajima                                                                      //
// @ note	 :                                                                                      //
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
	if (mBackGround != nullptr)
	{
		// 背景レイヤーの初期化
		mBackGround->Initialize(this);
	}
	// ゲームレイヤーの生成
	mGame = make_unique<PlayGameLayer>();
	if (mGame != nullptr)
	{	
		// ゲームレイヤーの初期化
		mGame->Initialize(this, width, height);
	}
	// HUDレイヤーの生成
	mHUD = make_unique<PlayHUDLayer>();
	if (mHUD != nullptr)
	{
		// HUDレイヤーの初期化
		mHUD->Initialize(this);
	}
	// ゲーム開始前のカウンタの生成
	mStart = make_unique<GameStartScreen>();
	// スタートスクリーンがnullptrでなければ
	if (mStart != nullptr)
	{
		// スタートスクリーンの初期化
		mStart->Initialize();
	}
	// ポーズ画面の生成
	mPause = make_unique<PauseScreen>();
	// ポーズ画面がnullptrでなければ
	if (mPause != nullptr)
	{
		// ポーズ画面の初期化
		mPause->Initialize();
	}
	// 状態遷移用変数の初期化
	mState = START;
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
	pCamera->SetEye(Vector3(0.0f, 18.0f, 30.0f));
	pCamera->SetRef(Vector3(0.0f, 0.0f, 0.0f));

	switch(mState)
	{
		// ゲーム開始前のカウンタ
		case START:
			// 
			mStart->Update();
			// 
			if (mStart->GetFlag())
			{
				// 状態をゲームにする
				mState = GAME;
			}
			break;
		// ゲーム開始後
		case GAME:
			// 背景レイヤーの更新
			mBackGround->Update();
			// ゲームレイヤーの更新
			
			//mGame->SetPauseFlag(mHUD->GetPauseFlag());
			mGame->Update();
			// HUDレイヤーの更新
			mHUD->Update();
			// ポーズ画面のフラグがtrueだったら
			if (mHUD->GetPauseFlag() == true)
			{
				// 状態をポーズにする
				mState = PAUSE;
			}
			break;
		// ポーズ画面
		case PAUSE:
			// HUDレイヤーの更新
			mHUD->Update();
			// ポーズ画面の更新
			mPause->Update();
			// ポーズ画面のフラグがfalseなら
			if (mHUD->GetPauseFlag() == false)
			{
				// 状態をゲームにする
				mState = GAME;
			}
			break;
	}
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
	// ゲーム開始前のカウンタだったr
	if (mState == START)
	{
		// ゲーム開始前のカウンタの描画
		mStart->Render();
	}
	// ポーズ画面だったら
	if (mState == PAUSE)
	{
		// ポーズ画面の描画
		mPause->Render();
	}
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
