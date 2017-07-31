// ------------------------------------------------------------------------------------------------ //
// @ file	 : HUDLayer.cpp                                                                         //
// @ brief	 : ヘッドアップディスプレイ部分のクラス                                                 //
// @ date	 : 2017/06/30                                                                           //
// @ author  : Madoka Nakajima                                                                      //
// @ note	 :                                                                                      //
// @ version : ver.3.00                                                                             //
// ------------------------------------------------------------------------------------------------ // 
/* ヘッダファイルのインクルード */
#include "../../ImaseLib/DirectXTK.h"
#include "PlayHUDLayer.h"

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
	pScene = scene;
	mNum = make_unique<Texture>(L"Resources\\number.png");
	mBiscuitBefore = make_unique<Texture>(L"Resources\\Biscuit_before.png");
	mBiscuitAfter = make_unique<Texture>(L"Resources\\Biscuit_after.png");
	mPause = make_unique<PauseScreen>();
	if (mPause != nullptr)
	{
		mPause->Initialize();
	}
	mStart = make_unique<GameStartScreen>();
	if (mStart != nullptr)
	{
		mStart->Initialize();
	}
	mBisrect.left = 1211;
	mBisrect.top = 40;
	mBisrect.right = 1275;
	mBisrect.bottom = 104;
	mPauseFlag = false;
	mStartFlag = false;
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
	mPause->Update();
	mStart->Update();
}


// ----------------------------------------------------------------------------------------------- //
// @ brief	: 描画                                                                                 //
// @ param	: なし                                                                                 //
// @ return : なし                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void PlayHUDLayer::Draw()
{
	if (!mpFrag)
	{
		pScene->GetSprite()->Draw(mBiscuitBefore->m_pTexture, mBisrect, Colors::White);
	}
	else
	{
		pScene->GetSprite()->Draw(mBiscuitAfter->m_pTexture, mBisrect, Colors::White);
	}
	if (mPauseFlag)
	{
		mPause->Render();
	}
	if (mStartFlag)
	{
		mStart->Render();
	}
	DrawNum();
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: 数字描画                                                                             //
// @ param	: なし                                                                                 //
// @ return : なし                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void PlayHUDLayer::DrawNum()
{

	// 作業用
	auto num = mCount;
	// 文字数
	auto sn = 0;
	// 座標
	auto x = 160.0f;
	auto y = 32.0f;
	// 画像の中心点
	auto ox = NumTextureSize / 2.0f;
	auto oy = NumTextureSize / 2.0f;
	// 画像の描画範囲
	RECT crect = { 0, 0, NumTextureSize, NumTextureSize };


	if (num == 0)
	{
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
		pScene->GetSprite()->Draw(mNum->m_pTexture, Vector2(x, y), &crect, Colors::White, 0.0f, Vector2(ox, oy), Vector2(1.0f, 1.0f));
	}
	else
	{
		while (num)
		{

			int l = (num % 10) * NumTextureSize;
			int t = 0;
			int r = l + NumTextureSize;
			int b = NumTextureSize;

			int px = x - sn * NumTextureSize;

			// 画像の描画範囲
			crect = { l,t,r,b };
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
			pScene->GetSprite()->Draw(mNum->m_pTexture, Vector2(px, y), &crect, Colors::White, 0.0f, Vector2(ox, oy), Vector2(1.0f, 1.0f));
			num /= 10;
			sn++;
		}
	}
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
