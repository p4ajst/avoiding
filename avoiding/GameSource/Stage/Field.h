// ------------------------------------------------------------------------------------------------ //
// @ file	 : Field.h                                                                              //
// @ brief	 : フィールドクラス                                                                   //
// @ date	 : 2017/10/23                                                                           //
// @ author  : Madoka Nakajima                                                                      //
// @ note	 :                                                                                      //
// @ version : ver.3.00                                                                             //
// ------------------------------------------------------------------------------------------------ // 
/* 多重インクルードの防止 */
#pragma once
/* ヘッダファイルのインクルード */
// 標準ライブラリ
#include <Effects.h>
// 自作ヘッダファイル
#include "../Stage/Attribute.h"
#include "../Stage/Map.h"
#include "../Utility/CSVReader.h"

/* クラス宣言 */
class Field
{
	/* メンバ変数 */
	// DGSLエフェクトファクトリ
	std::shared_ptr<DirectX::DGSLEffectFactory> mDef;
	// マップ
	std::shared_ptr<Map> mMap;
	// マップチップ
	MapChip* mChip[MapChipAttribute::ATTRIBUTE_NUM];
	// 床のモデル
	std::shared_ptr<DirectX::Model> mCookieModel;
	// 穴のモデル
	std::shared_ptr<DirectX::Model> mHoleModel;
	// 網のモデル
	std::shared_ptr<DirectX::Model> mNetModel;
	// CSV読み込み
	std::shared_ptr<CSVReader> mCSV;
	// マップデータ
	std::vector<std::vector<int>> mMapData;
	// マップサイズ
	int mMapSize_x;
	int mMapSize_z;
	// マップのずらしている分
	int mMapOffset_x;
	int mMapOffset_z;

	/* メンバ関数 */
public:
	Field();
	~Field();
	// 初期化
	void Initialize(wchar_t* mapfile);
	// 更新
	void Update();
	// 描画
	void Draw(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);
	// 終了
	void Finalize();
	// マップチップの登録
	void RegisterMapChip(MapChipAttribute attr, std::shared_ptr<DirectX::Model> model);
	// マップの生成
	void CreateMap();
	// フィールドの属性を変更
	void ChangeAttribute(int x,int z,MapChipAttribute attr);
	// 取得
	int GetSizeX() { return mMapSize_x; }
	int GetSizeZ() { return mMapSize_z; }
	int GetOffsetX() { return mMapOffset_x; }
	int GetOffsetZ() { return mMapOffset_z; }

};

