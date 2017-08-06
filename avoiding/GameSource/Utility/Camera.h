// ------------------------------------------------------------------------------------------------ //
// @ file	 : Camera.h                                                                             //
// @ brief	 : カメラクラスのヘッダファイル                                                         //
// @ date	 : 2016/09/01                                                                           //
// @ author  : Madoka Nakajima                                                                      //
// @ note	 : 自作カメラクラス                                                                     //
// @ version : ver.3.00                                                                             //
// ------------------------------------------------------------------------------------------------ //
/* 多重インクルードの防止 */
#pragma once 
/* ヘッダファイルのインクルード */
// 標準ライブラリ
#include <SimpleMath.h>

/* 関数のプロトタイプ宣言 */
// 内積
float Dot(DirectX::SimpleMath::Vector3 v1, DirectX::SimpleMath::Vector3 v2);
// 外積
DirectX::SimpleMath::Vector3 Cross(DirectX::SimpleMath::Vector3 v1, DirectX::SimpleMath::Vector3 v2);

/* クラス宣言 */
class Camera
{
	/* メンバ変数 */
protected:
	/* ビュー行列 */
	// 視点
	DirectX::SimpleMath::Vector3 mEye;
	// 注視店(参照点)
	DirectX::SimpleMath::Vector3 mRef;
	// カメラの上方向
	DirectX::SimpleMath::Vector3 mUp;
	// ビュー行列
	DirectX::SimpleMath::Matrix mView;

	/* プロジェクション行列(射影行列) */
	// 垂直視野角
	float mFovY;
	// アスペクト比
	float mAspect;
	// ニアクリップ
	float mNearClip;
	// ファークリップ
	float mFarClip;
	// プロジェクション行列
	DirectX::SimpleMath::Matrix mProjection;

	/* メンバ関数 */
public:
	// コンストラクタ
	Camera();
	// デストラクタ
	~Camera();

	// 更新処理
	void Update();

	// 視点の設定
	void SetEye(DirectX::SimpleMath::Vector3 eye) { mEye = eye; }
	// 参照点の設定
	void SetRef(DirectX::SimpleMath::Vector3 ref) { mRef = ref; }
	// 上方向ベクトルの設定
	void SetUp(DirectX::SimpleMath::Vector3 up) { mUp = up; }
	// 視点の取得
	DirectX::SimpleMath::Vector3 GetEye() { return mEye; }
	// 参照点の取得
	DirectX::SimpleMath::Vector3 GetRef() { return mRef; }
	// 上方向ベクトルの取得
	DirectX::SimpleMath::Vector3 GetUp() { return mUp; }

	// 垂直視野角の設定
	void SetFovY(float fovY) { mFovY = fovY; }
	// アスペクト比の設定
	void SetAspect(float aspect) { mAspect = aspect; }
	// ニアクリップの設定
	void SetNearClip(float nearClip) { mNearClip = nearClip; }
	// ファークリップの設定
	void SetFarClip(float farClip) { mFarClip = farClip; }

	// ビュー行列を作成
	DirectX::SimpleMath::Matrix CreateViewMatrix();
	// プロジェクション行列を作成
	DirectX::SimpleMath::Matrix CreateProjectionMatrix();

	// ビュー行列を取得
	DirectX::SimpleMath::Matrix GetViewMat() { return mView; }
	// プロジェクション行列を取得
	DirectX::SimpleMath::Matrix GetProjMat() { return mProjection; }
};
