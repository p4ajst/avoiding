// ------------------------------------------------------------------------------------------------ //
// @ file	 : MouseCursor.cpp                                                                      //
// @ brief	 : マウス制御に関するクラス                                                             //
// @ date	 : 2017/06/25                                                                           //
// @ author  : Madoka Nakajima                                                                      //
// @ note	 :                                                                                      //
// ------------------------------------------------------------------------------------------------ // 
/* ヘッダファイルのインクルード */
// 先生のフレームワーク
#include "../../ImaseLib/DirectXTK.h"
// 自作ヘッダファイル
#include "MouseCursor.h"

/* 名前空間 */
using namespace DirectX::SimpleMath;

/* メンバ関数の定義 */
// ----------------------------------------------------------------------------------------------- //
// @ brief	: 引数付きコンストラクタ                                                               //
// @ param	: int width...クライアント領域の幅                                                     //
// @ param	: int height...クライアント領域の高さ                                                  //
// @ return : なし                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
MouseCursor::MouseCursor(int width, int height)
	:mNear((float)width / 2.0f, (float)height / 2.0f, 0.0f)
	, mFar((float)width / 2.0f, (float)height / 2.0f, 1.0f)
	, mNearClip(0.0f, 0.0f, 0.0f)
	, mFarClip (0.0f, 0.0f, 0.0f)
	, mViewPort
	(
		(float)width / 2.0f,                    0.0f, 0.0f, 0.0f,
		               0.0f, (float)(-height) / 2.0f, 0.0f, 0.0f,
		               0.0f,                    0.0f, 1.0f, 0.0f,
		(float)width / 2.0f,    (float)height / 2.0f, 0.0f, 1.0f
	)
{
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: デストラクタ                                                                         //
// @ param	: なし                                                                                 //
// @ return : なし                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
MouseCursor::~MouseCursor()
{
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: 初期化                                                                               //
// @ param	: なし                                                                                 //
// @ return : なし                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void MouseCursor::Initialize()
{
	// ビューポートの逆行列を計算
	mViewPort.Invert(mInvertViewPort);
	// 一番近いスクリーン上の座標に逆行列をかける
	mNearClip = Vector3::Transform(mNear, mInvertViewPort);
	// 一番遠いスクリーン上の座標に逆行列をかける
	mFarClip = Vector3::Transform(mFar, mInvertViewPort);
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: 更新                                                                                 //
// @ param	: なし                                                                                 //
// @ return : なし                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void MouseCursor::Update()
{
	// 一番遠いスクリーン上の座標の設定
	mNear.x = (float)g_mouse.x;
	mNear.y = (float)g_mouse.y;
	// 一番遠いスクリーン上の座標の設定
	mFar.x = (float)g_mouse.x;
	mFar.y = (float)g_mouse.y;
	// ビューポートの逆行列を利用してニアクリップをトランスフォームする
	mNearClip = Vector3::Transform(mNear, mInvertViewPort);
	// ビューポートの逆行列を利用してファークリップをトランスフォームする
	mFarClip = Vector3::Transform(mFar, mInvertViewPort);
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: マウスの座標計算                                                                     //
// @ param	: Matrix view...ビュー行列                                                             //
// @ param	: Matrix proj...射影行列                                                               //
// @ return : なし                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void MouseCursor::Calc(Matrix view, Matrix proj)
{
	Matrix mat;
	Matrix tmp;
	mat = view * proj;
	mat.Invert(tmp);

	mVectorWorldNear = Vector3::Transform(mNearClip, tmp);
	mVectorWorldFar = Vector3::Transform(mFarClip, tmp);
}
// ----------------------------------------------------------------------------------------------- //
// @ brief	:                                                                                      //
// @ param	: Vector3 a...方向のある直線                                                           //
// @ param	: Vector3 b...方向のある直線                                                           //
// @ param	: Plane p...平面                                                                       //
// @ param	: float* t...方向のある直線に対して平面と交差する値                                    //
// @ param	: Vector3* q...交差点                                                                  //
// @ return : bool...交差しているかどうか                                                          //
// @ note	: リアルタイム衝突判定Ｐ．１７５                                                       //
// ----------------------------------------------------------------------------------------------- // 
bool MouseCursor::IntersectSegmentPlane(Vector3 a, Vector3 b, Plane p, float* t, Vector3* q)
{
	// 方向のある直線ａｂに対して平面と交差するｔの値を計算
	Vector3 ab = b - a;
	*t = (p.D() - p.Normal().Dot(a)) / p.Normal().Dot(ab);
	// ｔが[0..1]の中にある場合は計算し交差点を返す
	if (*t >= 0.0f && *t <= 1.0f)
	{
		*q = a + (*t) * ab;
		return true;
	}

	// そうでなければ交差はない
	return false;
}


// ----------------------------------------------------------------------------------------------- //
// @ brief	: 線分abが三角形defの平面に対して交差しているかどうか                                  //
// @ param	: Vector3 a....線分の点                                                                //
// @ param	: Vector3 b....線分の点                                                                //
// @ param	: Vector3 d....三角形の点                                                              //
// @ param	: Vector3 e....三角形の点                                                              //
// @ param	: Vector3 f....三角形の点                                                              //
// @ param	: float* t....                                                                         //
// @ param	: Vector3* q....交差している位置                                                       //
// @ return : 交差している場合、tの値および交差している位置qを返す                                 //
// @ note	: リアルタイム衝突判定Ｐ．１７５                                                       //
// ----------------------------------------------------------------------------------------------- // 
int MouseCursor::IntersectSegmentPlane(Vector3 a, Vector3 b, Vector3 d, Vector3 e, Vector3 f, float* t, Vector3* q)
{
	Vector3 aa = e - d;
	Vector3 bb = f - d;
	Vector3 n = aa.Cross(bb);
	float dd = n.Dot(d);
	Plane p(n, dd);
	return IntersectSegmentPlane(a, b, p, t, q);
}
