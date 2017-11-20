// ------------------------------------------------------------------------------------------------ //
// @ file	 : Field.cpp                                                                            //
// @ brief	 : フィールドクラス                                                                     //
// @ date	 : 2017/10/23                                                                           //
// @ author  : Madoka Nakajima                                                                      //
// @ note	 :                                                                                      //
// @ version : ver.3.00                                                                             //
// ------------------------------------------------------------------------------------------------ // 
/* ヘッダファイルのインクルード */
// 先生のライブラリ
#include "../../ImaseLib/Direct3D.h"
// 自作ヘッダファイル
#include "Field.h"

/* 名前空間 */
using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

/* メンバ関数の定義 */
// ----------------------------------------------------------------------------------------------- //
// @ brief	: コンストラクタ                                                                       //
// @ param	: なし                                                                                 //
// @ return : なし                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
Field::Field()
{
}


// ----------------------------------------------------------------------------------------------- //
// @ brief	: デストラクタ                                                                         //
// @ param	: なし                                                                                 //
// @ return : なし                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
Field::~Field()
{
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: 初期化                                                                               //
// @ param	: wchar_t * mapfile...読み込むＣＳＶデータのファイル名                                 //
// @ return : なし                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void Field::Initialize(wchar_t * mapfile)
{
	// CSV読み込み変数の生成
	mCSV = make_shared<CSVReader>();
	// CSV読み込み
	mCSV->ReadCSV(mapfile);
	// 読み込んだデータの取得
	mMapData = mCSV->GetData();
	// マップサイズを取得
	mMapSize_x = mMapData[0].size();
	mMapSize_z = mMapData.size();
	// マップのオフセットを算出
	mMapOffset_x = mMapSize_x / 2.0f;
	mMapOffset_z = mMapSize_z / 2.0f;


	// クッキー床のモデルの読み込み
	mCookieModel = Model::CreateFromCMO(g_pd3dDevice.Get(), L"Resources\\cookie.cmo", *mDef);
	// 穴のモデルの読み込み
	mHoleModel = Model::CreateFromCMO(g_pd3dDevice.Get(), L"Resources\\hole.cmo", *mDef);
	// 網のモデルの読み込み
	mNetModel = Model::CreateFromCMO(g_pd3dDevice.Get(), L"Resources\\net1.cmo", *mDef);

	// マップチップの登録
	RegisterMapChip(MapChipAttribute::COOKIE, mCookieModel);
	RegisterMapChip(MapChipAttribute::HOLE, mHoleModel);
	RegisterMapChip(MapChipAttribute::NET, mNetModel);

	// マップ生成
	CreateMap();
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: 更新                                                                                 //
// @ param	: なし                                                                                 //
// @ return : なし                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void Field::Update()
{
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: 描画                                                                                 //
// @ param	: Matrix view...ビュー行列                                                             //
// @ param	: Matrix proj...プロジェクション行列                                                   //
// @ return : なし                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void Field::Draw(Matrix view, Matrix proj)
{
	mMap->Draw(view,proj);
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: コンストラクタ                                                                       //
// @ param	: なし                                                                                 //
// @ return : なし                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void Field::Finalize()
{
	// マップチップの破棄
	delete mChip[MapChipAttribute::COOKIE];
	delete mChip[MapChipAttribute::HOLE];
	delete mChip[MapChipAttribute::NET];
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: マップチップの登録                                                                      //
// @ param	: なし                                                                                 //
// @ return : なし                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void Field::RegisterMapChip(MapChipAttribute attr, shared_ptr<DirectX::Model> model)
{
	mChip[attr] = new MapChip(attr);
	mChip[attr]->SetModel(model);
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: コンストラクタ                                                                       //
// @ param	: なし                                                                                 //
// @ return : なし                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void Field::CreateMap()
{
	// マップの生成
	mMap = make_shared<Map>(mMapSize_x, mMapSize_z);
	for (int i = 0; i < mMapSize_z; i++)
	{
		for (int j = 0; j < mMapSize_x; j++)
		{
			// マップの配列を代入
			mMap->Set(j, i, mChip[mMapData[i][j]]);
		}
	}
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: コンストラクタ                                                                       //
// @ param	: なし                                                                                 //
// @ return : なし                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void Field::ChangeAttribute(int x, int z, MapChipAttribute attr)
{
	// フィールドの属性を変える
	mMap->Set(x, z, mChip[attr]);
}

