﻿// ------------------------------------------------------------------------------------------------ //
// @ file	 : BackGroundLayer.cpp                                                                  //
// @ brief	 : 背景部分のクラス                                                                     //
// @ date	 : 2017/06/30                                                                           //
// @ author  : Madoka Nakajima                                                                      //
// @ note	 :                                                                                      //
// @ version : ver.3.00                                                                             //
// ------------------------------------------------------------------------------------------------ // 
/* ヘッダファイルのインクルード */
#include <WICTextureLoader.h>
#include "../../ImaseLib/Direct3D.h"
#include "PlayBackGroundLayer.h"
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
void PlayBackGroundLayer::Initialize(Scene* scene)
{

	pScene = scene;

	//mTexture = std::make_shared<SpriteBatch>();

	//const wchar_t* name = L"Resources\\haikei.png";
	//CreateWICTextureFromFile(g_pd3dDevice.Get(), name, nullptr, &mBackGround);
	mBackGround = make_unique<Texture>(L"Resources\\haikei.png");
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: 更新                                                                                 //
// @ param	: なし                                                                                 //
// @ return : なし                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void PlayBackGroundLayer::Update()
{
}


// ----------------------------------------------------------------------------------------------- //
// @ brief	: 描画                                                                                 //
// @ param	: なし                                                                                 //
// @ return : なし                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void PlayBackGroundLayer::Draw()
{
	// 描画位置（l,t,r,b）;
	RECT rect{ 0,0,1280,960 };

	pScene->GetSprite()->Draw(mBackGround->m_pTexture, rect,Colors::White);
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: 終了                                                                                 //
// @ param	: なし                                                                                 //
// @ return : なし                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void PlayBackGroundLayer::Finalize()
{
}
