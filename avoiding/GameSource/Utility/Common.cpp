// ------------------------------------------------------------------------------------------------ //
// @ file	 : Common.h                                                                             //
// @ brief	 : 複数のクラスにまたがる変数をまとめて外部参照するヘッダファイル                       //
// @ date	 : 2017/06/30                                                                           //
// @ author  : Madoka Nakajima                                                                      //
// @ note	 :                                                                                      //
// @ version : ver.3.00                                                                             //
// ------------------------------------------------------------------------------------------------ // 
/* ヘッダファイルのインクルード */
// 標準ライブラリ
#include <simplemath.h>
// 自作ヘッダファイル
#include "Common.h"

/* 名前空間 */
using namespace DirectX;
using namespace DirectX::SimpleMath;

/* 関数の定義 */
// ----------------------------------------------------------------------------------------------- //
// @ brief	: 数字描画                                                                             //
// @ param	: なし                                                                                 //
// @ return : なし                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 

//void DrawNum()
//{
//
//	// 作業用
//	auto num = mCount;
//	// 文字数
//	auto sn = 0;
//	// 座標
//	auto x = 160.0f;
//	auto y = 32.0f;
//	// 画像の中心点
//	auto ox = NumTextureSize / 2.0f;
//	auto oy = NumTextureSize / 2.0f;
//	// 画像の描画範囲
//	RECT crect = { 0, 0, NumTextureSize, NumTextureSize };
//
//
//	if (num == 0)
//	{
//		/*
//		ID3D11ShaderResourceView* texture...テクスチャのポインタ
//		FXMVECTOR position...画面の描画の基点（どこに描画するか）
//		RECT const* sourceRectangle...元のテクスチャのどの部分を描画するか
//		FXMVECTOR color...色
//		float rotation...回転角
//		XMFLOAT2 const& origin...描画する画像の基点
//		GXMVECTOR scale...拡大率
//		SpriteEffects effects
//		float layerDepth
//		*/
//		pScene->GetSprite()->Draw(mNum->m_pTexture, Vector2(x, y), &crect, Colors::White, 0.0f, Vector2(ox, oy), Vector2(1.0f, 1.0f));
//	}
//	else
//	{
//		while (num)
//		{
//
//			int l = (num % 10) * NumTextureSize;
//			int t = 0;
//			int r = l + NumTextureSize;
//			int b = NumTextureSize;
//
//			int px = x - sn * NumTextureSize;
//
//			// 画像の描画範囲
//			crect = { l,t,r,b };
//			/*
//			ID3D11ShaderResourceView* texture...テクスチャのポインタ
//			FXMVECTOR position...画面の描画の基点（どこに描画するか）
//			RECT const* sourceRectangle...元のテクスチャのどの部分を描画するか
//			FXMVECTOR color...色
//			float rotation...回転角
//			XMFLOAT2 const& origin...描画する画像の基点
//			GXMVECTOR scale...拡大率
//			SpriteEffects effects
//			float layerDepth
//			*/
//			pScene->GetSprite()->Draw(mNum->m_pTexture, Vector2(px, y), &crect, Colors::White, 0.0f, Vector2(ox, oy), Vector2(1.0f, 1.0f));
//			num /= 10;
//			sn++;
//		}
//	}
//}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: 数字描画                                                                             //
// @ param	: SpriteBatch* sprite...画像の描画する為                                               //
// @ param	: ID3D11ShaderResourceView* resource...テクスチャのデータ                              //
// @ param	: int n...描画したい数字                                                               //
// @ param	: float x...描画したい位置のｘ座標                                                     //
// @ param	: float y...描画したい位置のｙ座標                                                     //
// @ return : なし                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void DrawNum(SpriteBatch* sprite, ID3D11ShaderResourceView* resource, int n, float x, float y)
{

	// 作業用
	auto num = n;
	// 文字数
	auto sn = 0;
	// 座標
	auto px = x;
	auto py = y;

	// 画像の中心点
	auto ox = TextureSize / 2.0f;
	auto oy = TextureSize / 2.0f;
	// 画像の描画範囲
	RECT crect = { 0, 0, TextureSize, TextureSize };

	// 数字がゼロなら
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
		sprite->Draw(resource, Vector2(x, y), &crect, Colors::White, 0.0f, Vector2(ox, oy), Vector2(1.0f, 1.0f));
	}
	else
	{
		while (num)
		{
			// 描画範囲の設定
			int l = (num % 10) * TextureSize;
			int t = 0;
			int r = l + TextureSize;
			int b = TextureSize;

			// 座標の設定
			int px = x - sn * TextureSize;

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
			sprite->Draw(resource, Vector2(px, y), &crect, Colors::White, 0.0f, Vector2(ox, oy), Vector2(1.0f, 1.0f));
			// 位を一つ上げる
			num /= 10;
			// 文字数をカウントする
			sn++;
		}
	}
}
