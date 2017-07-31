// ------------------------------------------------------------------------------------------------ //
// @ file	 : Actor.h                                                                              //
// @ brief	 : 登場物の基底クラス                                                                   //
// @ date	 : 2017/06/25                                                                           //
// @ author  : Madoka Nakajima                                                                      //
// @ note	 :                                                                                      //
// @ version : ver.3.00                                                                             //
// ------------------------------------------------------------------------------------------------ // 
/* 多重インクルードの防止 */
#pragma once

/* ヘッダファイルのインクルード */
// 標準ライブラリ
#include <simplemath.h>
// ＤＧＳＬエフェクトファクトリを使う為
#include <Effects.h>
// スマートポインタを使う為
#include <memory>
// モデルを使う為
#include <Model.h>

/* クラス宣言 */
class Actor
{
	/* メンバ変数 */
protected:
	// DGSLエフェクトファクトリ
	std::shared_ptr<DirectX::DGSLEffectFactory>  mDef;
	// モデル
	std::shared_ptr<DirectX::Model> mModel;
	// 座標
	DirectX::SimpleMath::Vector3 mPosition;
	// 角度
	float mAngle;
	// 拡大率
	float mScalingFactor;
	// ローカルワールド行列
	DirectX::SimpleMath::Matrix mLocalWorld;

	/* メンバ関数 */
public:
	// コンストラクタ
	Actor() = default;
	// 仮想デストラクタ
	virtual ~Actor() = default;
	// 初期化
	void Initialize();
	// 更新
	void Update();
	// 描画
	void Draw(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);
	// 終了
	void Finalize();
	// モデルの読み込み
	void LoadModel(wchar_t* filename);
	// 行列計算
	void Calc();
	// メンバ変数の設定
	void SetModel(std::shared_ptr<DirectX::Model> model) { mModel = model; }
	void SetPos(DirectX::SimpleMath::Vector3 pos) { mPosition = pos; }
	void SetAngle(float angle) { mAngle = angle; }
	void SetScale(float scale) { mScalingFactor = scale; }
	// メンバ変数の取得
	std::shared_ptr<DirectX::Model> GetModel() { return mModel; }
	DirectX::SimpleMath::Vector3 GetPos() { return mPosition; }
	float GetAngle() { return mAngle; }
	float GetScale() { return mScalingFactor; }
};
