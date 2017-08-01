// ------------------------------------------------------------------------------------------------ //
// @ file	 : GameStartScreen.cpp                                                                  //
// @ brief	 : ゲーム開始前のカウントダウンに関するクラス                                           //
// @ date	 : 2017/07/18                                                                           //
// @ author  : Madoka Nakajima                                                                      //
// @ note	 :                                                                                      //
// @ version : ver.3.00                                                                             //
// ------------------------------------------------------------------------------------------------ // 
/* 多重インクルードの防止 */
/* ヘッダファイルのインクルード */
// 標準ライブラリ
#include <simplemath.h>
// 先生のフレームワーク
#include "../../ImaseLib/Direct3D.h"
#include "../../ImaseLib/DirectXTK.h"
// 自作ヘッダファイル
#include "GameStartScreen.h"

/* 名前空間 */
using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

/* メンバ関数の定義 */
// ----------------------------------------------------------------------------------------------- //
// @ brief	: 初期化処理                                                                           //
// @ param	: なし                                                                                 //
// @ return : なし                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void GameStartScreen::Initialize()
{
	// カウンタの初期化
	mStartCounter = 0;
	// フラグの初期化
	mStartFlag = false;
	// スプライトバッチの初期化
	pSprites = make_unique<SpriteBatch>(g_pImmediateContext.Get());
	// 画像の初期化
	mWhite = make_unique<Texture>(L"Resources\\screen.png");
	mNumber = make_unique<Texture>(L"Resources\\number.png");
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: 更新処理                                                                             //
// @ param	: なし                                                                                 //
// @ return : なし                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void GameStartScreen::Update()
{
	auto cnt = 180;
	// フラグが偽であるなら
	if (!mStartFlag)
	{
		// カウンタを進める
		cnt--;
		// カウンタが６０で割り切れたら
		if (cnt % 60 == 0)
		{
			// 何秒か計算して代入
			mStartCounter = cnt / 60;
		}
		// カウンタが０より小さくなったら
		if (mStartCounter < 0)
		{
			// フラグを真にする
			mStartFlag = true;
		}
	}
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: 描画処理                                                                             //
// @ param	: なし                                                                                 //
// @ return : なし                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void GameStartScreen::Render()
{
	// 画像の描画範囲
	RECT rect = { 0,0,1280,960 };
	auto x = mStartCounter * TextureSize;
	auto w = x + TextureSize;
	RECT crect = { x, 0, w, TextureSize};

	pSprites->Begin(SpriteSortMode_Deferred, nullptr, nullptr, nullptr, nullptr, [=]
	{
		// 画像の半透明処理
		g_pImmediateContext->OMSetBlendState(g_state->NonPremultiplied(), nullptr, 0xFFFFFFFF);
	});
	pSprites->Draw(mWhite->m_pTexture, rect, Colors::White);
	/*
		ID3D11ShaderResourceView* texture...テクスチャのポインタ
		FXMVECTOR position...画面の描画の基点（どこに描画するか）
		RECT const* sourceRectangle...元のテクスチャのどの部分を描画するか
		FXMVECTOR color...色
		float rotation...回転角
		XMFLOAT2 const& origin...描画する画像の基点
		GXMVECTOR scale...拡大率
		SpriteEffects effects
		float layerDepth
	 */
	//pSprites->Draw(mNumber->m_pTexture, Vector2(640.0f,480.0f),&crect,Colors::White,0.0f,Vector2(32.0f,32.0f),Vector2(1.0f, 1.0f));
	DrawNum(pSprites.get(), mNumber->m_pTexture, mStartCounter, 640.0f, 480.f);
	// スプライトバッチの終わり
	pSprites->End();
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: 終了処理                                                                             //
// @ param	: なし                                                                                 //
// @ return : なし                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void GameStartScreen::Finalize()
{
	// 
	// 
	// 
	// 
	// 
}
