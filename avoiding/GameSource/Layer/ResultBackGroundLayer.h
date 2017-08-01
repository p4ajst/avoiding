// ------------------------------------------------------------------------------------------------ //
// @ file	 :                                                                                      //
// @ brief	 :                                                                                      //
// @ date	 :                                                                                      //
// @ author  :                                                                                      //
// @ note	 :                                                                                      //
// @ version :                                                                                      //
// ------------------------------------------------------------------------------------------------ // 
/* 多重インクルードの防止 */
#pragma once
/* ヘッダファイルのインクルード */
#include "Layer.h"
/* クラス宣言 */
class ResultBackGroundLayer :public Layer
{
	/* メンバ変数 */
public:
	/* メンバ関数 */
	ResultBackGroundLayer() = default;
	~ResultBackGroundLayer() = default;
	void Initialize(Scene* scene);
	void Update();
	void Draw();
	void Finalize();
};
