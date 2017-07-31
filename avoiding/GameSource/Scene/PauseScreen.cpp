// ------------------------------------------------------------------------------------------------ //
// @ file	 : PauseScreen.cpp                                                                      //
// @ brief	 : ポーズ画面のソースファイル                                                           //
// @ date	 : 2017/07/13                                                                           //
// @ author  : Madoka Nakajima                                                                      //
// @ note	 :                                                                                      //
// @ version : ver.3.00                                                                             //
// ------------------------------------------------------------------------------------------------ // 
/* ヘッダファイルのインクルード */
// 先生のフレームワーク
#include "../../ImaseLib/Direct3D.h"
#include "../../ImaseLib/DirectXTK.h"
// 自作ヘッダファイル
#include "PauseScreen.h"

/* 名前空間 */
using namespace std;
using namespace DirectX;

/* メンバ関数の定義 */
// ----------------------------------------------------------------------------------------------- //
// @ brief	: 初期化                                                                               //
// @ param	: なし                                                                                 //
// @ return : なし                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void PauseScreen::Initialize()
{
	pSpriteBatch = make_unique<SpriteBatch>(g_pImmediateContext.Get());
	mChoco = make_unique<Texture>(L"Resources\\DecoWhiteChocolate.png");
}


// ----------------------------------------------------------------------------------------------- //
// @ brief	: 更新                                                                                 //
// @ param	: なし                                                                                 //
// @ return : なし　                                                                               //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void PauseScreen::Update()
{
}


// ----------------------------------------------------------------------------------------------- //
// @ brief	: 描画                                                                                 //
// @ param	: なし                                                                                 //
// @ return : なし                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void PauseScreen::Render()
{
	RECT rect{ 32,105,1247,855 };
	pSpriteBatch->Begin(SpriteSortMode_Deferred, nullptr, nullptr, nullptr, nullptr, [=]
	{
		// 画像の半透明処理
		g_pImmediateContext->OMSetBlendState(g_state->NonPremultiplied(), nullptr, 0xFFFFFFFF);
	});
	pSpriteBatch->Draw(mChoco->m_pTexture, rect, Colors::White);
	// スプライトバッチの終わり
	pSpriteBatch->End();
}


// ----------------------------------------------------------------------------------------------- //
// @ brief	: 終了                                                                                 //
// @ param	: なし                                                                                 //
// @ return : なし                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void PauseScreen::Finalize()
{
}
