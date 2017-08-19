// ------------------------------------------------------------------------------------------------ //
// @ file	 : MouseCursor.h                                                                        //
// @ brief	 : マウス制御に関するクラス                                                             //
// @ date	 : 2017/06/25                                                                           //
// @ author  : Madoka Nakajima                                                                      //
// @ note	 :                                                                                      //
// ------------------------------------------------------------------------------------------------ // 
/* 多重インクルードの防止 */
#pragma once

/* ヘッダファイルのインクルード */
// 自作ヘッダファイル
#include <SimpleMath.h>

/* クラス宣言 */
class MouseCursor
{
	/* メンバ変数 */
private:
	/* スクリーン座標上のカーソルの位置 */
	// 一番近いスクリーン上の座標
	DirectX::SimpleMath::Vector3 mNear;
	// 一番遠いスクリーン上の座標
	DirectX::SimpleMath::Vector3 mFar;
	// ビューポートの逆行列をかけたカーソル
	DirectX::SimpleMath::Vector3 mNearClip;
	// ビューポートの逆行列をかけたカーソル
	DirectX::SimpleMath::Vector3 mFarClip;
	// ビューポート行列
	DirectX::SimpleMath::Matrix mViewPort;
	// ビューポートの逆行列
	DirectX::SimpleMath::Matrix mInvertViewPort;
	// ワールド空間上のベクトル
	DirectX::SimpleMath::Vector3 mVectorWorldNear;
	DirectX::SimpleMath::Vector3 mVectorWorldFar;

	/* メンバ関数 */
public:
	// 引数付きコンストラクタ
	MouseCursor(int width = 640, int height = 480);
	// デストラクタ
	~MouseCursor();
	// 初期化
	void Initialize();
	// 更新
	void Update();
	// マウスの座標計算
	void Calc(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);
	
	bool IntersectSegmentPlane(
		DirectX::SimpleMath::Vector3 a, 
		DirectX::SimpleMath::Vector3 b, 
		DirectX::SimpleMath::Plane p,
		float* t, 
		DirectX::SimpleMath::Vector3* q);
	/* 線分ａｂが三角形ｄｅｆの平面に対して交差しているかどうか。
	交差している場合、ｔの値および交差している位置ｑを返す */
	int IntersectSegmentPlane(
		DirectX::SimpleMath::Vector3 a,
		DirectX::SimpleMath::Vector3 b,
		DirectX::SimpleMath::Vector3 d,
		DirectX::SimpleMath::Vector3 e,
		DirectX::SimpleMath::Vector3 f,
		float* t,
		DirectX::SimpleMath::Vector3* q);

	// getter
	const DirectX::SimpleMath::Vector3 GetNear() { return mVectorWorldNear; }
	const DirectX::SimpleMath::Vector3 GetFar() { return mVectorWorldFar; }
};
