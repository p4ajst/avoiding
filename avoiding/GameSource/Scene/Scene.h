// ------------------------------------------------------------------------------------------------ //
// @ file	 : Scene.h                                                                              //
// @ brief	 : シーンの基底クラス                                                                   //
// @ date	 : 2017/05/02                                                                           //
// @ author  : Madoka Nakajima                                                                      //
// @ note	 :                                                                                      //
// @ version : ver.3.00                                                                             //
// ------------------------------------------------------------------------------------------------ // 
/* 多重インクルードを防止 */
#pragma once 
/* ヘッダファイルのインクルード */
// 標準ライブラリ
#include <simplemath.h>
#include <SpriteBatch.h>
#include <memory>
// 自作ヘッダファイル
#include "../Utility/Camera.h"
/* クラス宣言 */
class Scene
{
	/* メンバ変数 */
protected:
	// 遷移判定用変数
	bool mSceneFlag;
	// スプライトバッチ
	std::shared_ptr<DirectX::SpriteBatch> pSprite;
	// カメラ
	std::shared_ptr<Camera> pCamera;
	/* メンバ関数 */
public:
	// コンストラクタ
	Scene() = default;
	// 仮想デストラクタ
	virtual ~Scene() = default;
	// 初期化
	virtual void Initialize(int width, int height) = 0;
	// 更新
	virtual void Update() = 0;
	// 描画
	virtual void Render() = 0;
	// 終了
	virtual void Finalize() = 0;
	// シーン遷移
	virtual Scene* Change() = 0;
	// スプライトバッチの取得
	std::shared_ptr<DirectX::SpriteBatch> GetSprite() { return pSprite; }
	// カメラの取得
	std::shared_ptr<Camera>GetCamera() { return pCamera; }
};
