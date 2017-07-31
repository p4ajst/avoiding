// ------------------------------------------------------------------------------------------------ //
// @ file	 : Layer.h                                                                              //
// @ brief	 : レイヤーの基底クラス                                                                 //
// @ date	 : 2017/06/26                                                                           //
// @ author  : Madoka Nakajima                                                                      //
// @ note	 :                                                                                      //
// @ version : ver.3.00                                                                             //
// ------------------------------------------------------------------------------------------------ // 
/* 多重インクルードの防止 */
#pragma once
/* ヘッダファイルのインクルード */
// 標準ライブラリ
#include <simplemath.h>
// 自作ヘッダファイル
#include "../Scene/Scene.h"

/* クラス宣言 */
class Layer
{
protected:
	/* メンバ関数 */
	Scene* pScene;
public:
	// コンストラクタ
	Layer() = default;
	// 仮想デストラクタ
	virtual ~Layer() = default;
	// 初期化
	virtual void Initialize(Scene* scene) = 0;
	// 更新
	virtual void Update() = 0;
	// 描画
	virtual void Draw() = 0;
	// 終了
	virtual void Finalize() = 0;
};
