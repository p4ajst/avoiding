// ------------------------------------------------------------------------------------------------ //
// @ file	 : ResultHUDLayer.h                                                                     //
// @ brief	 : ヘッドアップディスプレイ部分のクラス                                                 //
// @ date	 : 2017/07/10                                                                           //
// @ author  : Madoka Nakajima                                                                      //
// @ note	 :                                                                                      //
// ------------------------------------------------------------------------------------------------ // 
/* 多重インクルードの防止 */
#pragma once
/* ヘッダファイルのインクルード */
// 先生のフレームワーク
#include "../../ImaseLib/Texture.h"
// 自作ヘッダファイル
#include "Layer.h"
/* クラス宣言 */
class ResultHUDLayer : public Layer
{
	/* メンバ変数 */
	// シーン遷移用変数
	bool mSceneFlag;
	// 描画画像変更用
	bool mResultFlag;
	// 画像描画用変数
	std::unique_ptr<Texture> mBeforeFrog;
	std::unique_ptr<Texture> mAfterFrog;
	std::unique_ptr<Texture> mBeforeDoor;
	std::unique_ptr<Texture> mAfterDoor;
	std::unique_ptr<Texture> mGameClear;
	std::unique_ptr<Texture> mGameOver;
	// 判定用フラグ
	bool mfFlag;
	bool mdFlag;
	// 画像の描画範囲
	RECT mFrog;
	RECT mDoor;
	RECT mDoorA;

public:
	/* メンバ関数 */
	// 初期化処理
	void Initialize(Scene* scene);
	// 更新処理
	void Update();
	// 描画処理
	void Draw();
	// 終了処理
	void Finalize();
	// フラグの設定
	void SetResultFlag(bool flag) { mResultFlag = flag; }
	// 取得
	bool GetFlag() { return mSceneFlag; }
};
