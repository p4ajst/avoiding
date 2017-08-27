// ------------------------------------------------------------------------------------------------ //
// @ file	 : GameLayer.h                                                                          //
// @ brief	 : ゲーム部分のクラス                                                                   //
// @ date	 : 2017/06/30                                                                           //
// @ author  : Madoka Nakajima                                                                      //
// @ note	 :                                                                                      //
// ------------------------------------------------------------------------------------------------ // 
/* 多重インクルードの防止 */
#pragma once
/* ヘッダファイルのインクルード */
// 標準ライブラリ
#include <simplemath.h>
#include <Effects.h>
#include <memory>
#include <vector>
// 自作ヘッダファイル
#include "Layer.h"

#include "../Object/Bomb.h"
#include "../Object/Character.h"
#include "../Object/Cursor.h"
#include "../Object/Item.h"
#include "../Stage/Attribute.h"
#include "../Stage/Map.h"
#include "../Utility/CSVReader.h"
#include "../Utility/MouseCursor.h"

/* 列挙体宣言 */
enum PlayGameState
{
	START,
	PLAY
};

/* クラス宣言 */
class PlayGameLayer : public Layer
{
	/* メンバ変数 */
	// エフェクトファクトリ
	std::shared_ptr<DirectX::EffectFactory> mEf;
	// DGSLエフェクトファクトリ
	std::shared_ptr<DirectX::DGSLEffectFactory> mDef;

	// ボム
	std::shared_ptr<Bomb> mBomb;
	std::vector<std::shared_ptr<Bomb>> mBombs;
	// くまきゅん
	std::shared_ptr<Character> mKuma;
	// マウスカーソル
	std::shared_ptr<Cursor> mCursor;
	// アイテム
	std::shared_ptr<Item> mItem;
	// マップ
	std::shared_ptr<Map> mMap;
	// マップチップ
	MapChip* mChip[MapChipAttribute::ATTRIBUTE_NUM];

	// ボムのモデル
	std::shared_ptr<DirectX::Model> mBombModel;
	// クッキー床のモデル
	std::shared_ptr<DirectX::Model> mCookieModel;
	// 穴のモデル
	std::shared_ptr<DirectX::Model> mHoleModel;
	// 網のモデル
	std::shared_ptr<DirectX::Model> mNetModel;

	// マウスカーソルの座標
	DirectX::SimpleMath::Vector3 mCursorPos;
	// マウスレイとフィールドとのあたり判定の関数の戻り値
	DirectX::SimpleMath::Vector3 mResult;
	// カーソルの座標＋ずらしている分
	int mMapOffset_x;
	int mMapOffset_z;

	// CSV読み込み
	std::shared_ptr<CSVReader> mCSV;
	// マップデータ
	std::vector<std::vector<int>> mMapData;
	// マップサイズ
	int mMapSize_x;
	int mMapSize_z;
	// マップチップのずらしてる分（オフセット）
	float mOffset_x;
	float mOffset_z;

	// ボムの生成タイマー
	float mWaitTimer;

	// シーン切替用変数
	bool mSceneFlag;
	
	// 描画画像変更用
	bool mResultFlag;
	// ポーズ中か
	bool mPauseFlag;
	// スタートフラグ
	bool mStartFlag;
	bool msFlag;
	// 落下中か
	bool mFallFlag;
	// カウンタ
	int mCount;
public:
	/* メンバ関数 */
	// 初期化
	void Initialize(Scene* scene);
	void Initialize(Scene* scene, int width, int height);
	// 更新
	void Update();
	// 描画
	void Draw();
	// 終了
	void Finalize();
	// 初期配置
	DirectX::SimpleMath::Vector3 InitialPlacement(int mapSize_x, int mapSize_z, float offset_x, float offset_z);
	// 座標から配列の要素番号を算出
	DirectX::SimpleMath::Vector3 CalculateElementNumber(DirectX::SimpleMath::Vector3 pos, int offset_x, int offset_z);
	// マップチップの登録
	void RegisterMapChip(MapChipAttribute attr, std::shared_ptr<DirectX::Model> model);
	// 設定
	void SetPauseFlag(bool flag) { mPauseFlag = flag; }
	void SetStartFlag(bool flag) { mStartFlag = flag; }
	// 取得
	bool GetResultFlag() { return mResultFlag; }
	bool GetStartFlag() { return mStartFlag; }
	bool GetFlag() { return mSceneFlag; }
	int GetCount() { return mCount; }
};
