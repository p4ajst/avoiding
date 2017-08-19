// ------------------------------------------------------------------------------------------------ //
// @ file	 : Camera.cpp                                                                           //
// @ brief	 : カメラクラスのソースファイル                                                         //
// @ date	 : 2016/09/01                                                                           //
// @ author  : Madoka Nakajima                                                                      //
// @ note	 : 自作カメラクラス                                                                     //
// ------------------------------------------------------------------------------------------------ // 
/* 多重インクルードの防止 */
/* ヘッダファイルのインクルード */
#include "Camera.h"
/* 名前空間 */
using namespace DirectX;
using namespace DirectX::SimpleMath;

/* 関数の定義 */
// ----------------------------------------------------------------------------------------------- //
// @ brief	: 内積                                                                                 //
// @ param	: Vector3 v1                                                                           //
// @ param	: Vector3 v2                                                                           //
// @ return : float dots                                                                           //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
float Dot(DirectX::SimpleMath::Vector3 v1, DirectX::SimpleMath::Vector3 v2)
{
	float dots;
	dots = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	return dots;
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: 外積                                                                                 //
// @ param	: Vector3 v1                                                                           //
// @ param	: Vector3 v2                                                                           //
// @ return : Vector3 crossvec                                                                     //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
Vector3 Cross(DirectX::SimpleMath::Vector3 v1, DirectX::SimpleMath::Vector3 v2)
{
	Vector3 crossvec;
	crossvec.x = v1.y * v2.z - v1.z * v2.y;
	crossvec.y = v1.z * v2.x - v1.x * v2.z;
	crossvec.z = v1.x * v2.y - v1.y * v2.x;
	return crossvec;
}

/* メンバ関数の定義 */
// ----------------------------------------------------------------------------------------------- //
// @ brief	: コンストラクタ                                                                       //
// @ param	: 無し                                                                                 //
// @ return : 無し                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
Camera::Camera()
	:mEye(Vector3(0, 0, 0))
	,mRef(Vector3(0, 0, 10))
	,mUp(Vector3(0, 1, 0))
	,mFovY(XMConvertToRadians(45.0f))
	,mAspect(640.0f / 480.0f)
	,mNearClip(0.1f)
	,mFarClip(1000.0f)
{
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: デストラクタ                                                                         //
// @ param	: 無し                                                                                 //
// @ return : 無し                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
Camera::~Camera()
{
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: 更新処理                                                                             //
// @ param	: 無し                                                                                 //
// @ return : 無し                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void Camera::Update()
{
	CreateViewMatrix();
	CreateProjectionMatrix();
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: ビュー行列を作成 　                                                                  //
// @ param	: 無し                                                                                 //
// @ return : Matrix m_view	                                                                       //
// @ note	: = Matrix::CreateLookAt                                                               //
// ----------------------------------------------------------------------------------------------- // 
Matrix Camera::CreateViewMatrix()
{
	// 視線方向ベクトル
	Vector3 eyeDirection;
	// カメラのｘ方向ベクトル
	Vector3 camera_x;
	// カメラの上方向ベクトル
	Vector3 new_up;
	// 視線方向ベクトルを求める(参照点 - 視点)
	eyeDirection = mEye - mRef;
	// 視線方向ベクトルの正規化
	eyeDirection.Normalize();
	// カメラのｘ方向ベクトルを求める(外積)
	camera_x = Cross(mUp, eyeDirection);
	// カメラのｘ方向ベクトルの正規化
	camera_x.Normalize();
	// カメラの上方向ベクトルを求める(外積)
	new_up = Cross(eyeDirection, camera_x);

	// 行列を作る
	mView.m[0][0] = camera_x.x;
	mView.m[0][1] = new_up.x;
	mView.m[0][2] = eyeDirection.x;
	mView.m[0][3] = 0;
	mView.m[1][0] = camera_x.y;
	mView.m[1][1] = new_up.y;
	mView.m[1][2] = eyeDirection.y;
	mView.m[1][3] = 0;
	mView.m[2][0] = camera_x.z;
	mView.m[2][1] = new_up.z;
	mView.m[2][2] = eyeDirection.z;
	mView.m[2][3] = 0;
	mView.m[3][0] = -(Dot(camera_x, GetEye()));
	mView.m[3][1] = -(Dot(new_up, GetEye()));
	mView.m[3][2] = -(Dot(eyeDirection, GetEye()));
	mView.m[3][3] = 1;

	return mView;
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: プロジェクション行列を作成                                                           //
// @ param	: 無し                                                                                 //
// @ return : Matrix m_projection                                                                  //
// @ note	: = Matrix::CreatePerspectiveFieldOfView                                               //
// ----------------------------------------------------------------------------------------------- // 
Matrix Camera::CreateProjectionMatrix()
{
	mProjection = Matrix::CreatePerspectiveFieldOfView(mFovY, mAspect, mNearClip, mFarClip);
	return mProjection;
}
