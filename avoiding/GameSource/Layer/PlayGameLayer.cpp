// ------------------------------------------------------------------------------------------------ //
// @ file	 : GameLayer.cpp                                                                        //
// @ brief	 : ゲーム部分のクラス                                                                   //
// @ date	 : 2017/06/30                                                                           //
// @ author  : Madoka Nakajima                                                                      //
// @ note	 :                                                                                      //
// @ version : ver.3.00                                                                             //
// ------------------------------------------------------------------------------------------------ // 
/* ヘッダファイルのインクルード */
// 先生のフレームワーク
#include "../../ImaseLib/Direct3D.h"
#include "../../ImaseLib/DirectXTK.h"
// 自作ヘッダファイル
#include "PlayGameLayer.h"

/* 名前空間 */
using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

/* メンバ関数の定義 */
// ----------------------------------------------------------------------------------------------- //
// @ brief	: 初期化                                                                               //
// @ param	: int width...クライアント領域の幅                                                     //
// @ param	: int height...クライアント領域の高さ                                                  //
// @ return : なし                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void PlayGameLayer::Initialize(Scene* scene)
{
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: 初期化                                                                               //
// @ param	: int width...クライアント領域の幅                                                     //
// @ param	: int height...クライアント領域の高さ                                                  //
// @ return : なし                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void PlayGameLayer::Initialize(Scene* scene, int width, int height)
{
	// シーンの取得
	pScene = scene;
	// エフェクトファクトリの初期化
	mEf = make_shared<EffectFactory>(g_pd3dDevice.Get());
	// ファイルパスを指定
	mEf->SetDirectory(L"Resources");
	// DGSLエフェクトファクトリの初期化
	mDef = make_shared<DGSLEffectFactory>(g_pd3dDevice.Get());
	// ファイルパスの指定
	mDef->SetDirectory(L"Resources");

	// CSV読み込み変数の生成
	mCSV = make_shared<CSVReader>();
	// CSV読み込み
	mCSV->ReadCSV(L"Resources\\mapdata3.csv");
	// 読み込んだデータの取得
	mMapData = mCSV->GetData();
	// マップサイズを取得
	mMapSize_x = mMapData[0].size();
	mMapSize_z = mMapData.size() - 1;
	// マップのオフセットを算出
	mOffset_x = mMapSize_x / 2.0f;
	mOffset_z = mMapSize_z / 2.0f;

	// ボムのモデルの読み込み
	mBombModel = Model::CreateFromCMO(g_pd3dDevice.Get(), L"Resources\\dogbomb1.cmo", *mDef);
	// クッキー床のモデルの読み込み
	mCookieModel = Model::CreateFromCMO(g_pd3dDevice.Get(), L"Resources\\cookie.cmo", *mDef);
	// 穴のモデルの読み込み
	mHoleModel = Model::CreateFromCMO(g_pd3dDevice.Get(), L"Resources\\hole.cmo", *mDef);
	// 網のモデルの読み込み
	mNetModel = Model::CreateFromCMO(g_pd3dDevice.Get(), L"Resources\\net1.cmo", *mDef);

	// マップチップの登録
	mChip[MapChipAttribute::HOLE] = new MapChip(HOLE);
	mChip[MapChipAttribute::HOLE]->SetModel(mHoleModel);
	mChip[MapChipAttribute::COOKIE] = new MapChip(COOKIE);
	mChip[MapChipAttribute::COOKIE]->SetModel(mCookieModel);
	mChip[MapChipAttribute::NET] = new MapChip(NET);
	mChip[MapChipAttribute::NET]->SetModel(mNetModel);

	// マップの生成
	mMap = make_unique<Map>(mMapSize_x, mMapSize_z);
	for (int i = 0; i < mMapSize_z; i++)
	{
		for (int j = 0; j < mMapSize_x; j++)
		{
			// マップの配列を代入
			mMap->Set(j, i, mChip[mMapData[i][j]]);
		}
	}

	// キャラクターの生成
	mKuma = make_shared<Character>();
	// キャラクターの初期化
	mKuma->Initialize();
	// キャラクターのモデルの読み込み
	mKuma->LoadModel(L"Resources\\kumakyun2.cmo");
	// 座標をランダムで設定
	Vector3 kpos = mMap->GetRandomPos(mMapSize_x, mMapSize_z, mOffset_x, mOffset_z);
	// 座標から配列の要素番号を算出
	auto kposs = Vector3(0, 0, 0);
	kposs.x = floorf(kpos.x + mOffset_x);
	kposs.z = floorf(kpos.z + mOffset_z);
	// 移動可能マスになるまで
	while (mMap->GetAttribute((int)(kposs.x), (int)(kposs.z)) != COOKIE)
	{
		// 座標をランダムで設定
		kpos = mMap->GetRandomPos(mMapSize_x, mMapSize_z, mOffset_x, mOffset_z);
		// 座標から配列の要素番号を算出
		kposs.x = floorf(kpos.x + mOffset_x);
		kposs.z = floorf(kpos.z + mOffset_z);
	}
	kpos.x = kposs.x + 0.5f - mOffset_x;
	kpos.z = kposs.z + 0.5f - mOffset_z;
	// 座標をランダムで設定
	mKuma->SetPos(kpos);
	// 速度の設定
	mKuma->SetVel(Vector3(0, 0, 0));

	// アイテムの生成
	mItem = make_shared<Item>();
	// アイテムの初期化
	mItem->Initialize();
	// アイテムのモデルの読み込み
	mItem->LoadModel(L"Resources\\PoPcandy.cmo");
	// 座標をランダムで設定
	Vector3 ipos = mMap->GetRandomPos(mMapSize_x, mMapSize_z, mOffset_x, mOffset_z);
	// 座標から配列の要素番号を算出
	auto iposs = Vector3(0, 0, 0);
	iposs.x = floorf(ipos.x + mOffset_x);
	iposs.z = floorf(ipos.z + mOffset_z);
	// 移動可能マスになるまで
	while (mMap->GetAttribute((int)(iposs.x), (int)(iposs.z)) != COOKIE)
	{
		// 座標をランダムで設定
		ipos = mMap->GetRandomPos(mMapSize_x, mMapSize_z, mOffset_x, mOffset_z);
		// 座標から配列の要素番号を算出
		iposs.x = floorf(ipos.x + mOffset_x);
		iposs.z = floorf(ipos.z + mOffset_z);
	}
	ipos.x = iposs.x + 0.5f - mOffset_x;
	ipos.z = iposs.z + 0.5f - mOffset_z;
	// ｙ座標を高くする
	ipos.y = 1;
	// 座標の設定
	mItem->SetPos(ipos);
	// 拡大率を小さくする
	mItem->SetScale(0.2f);

	// マウスカーソルの生成
	mCursor = make_shared<Cursor>();
	// マウスカーソルの初期化
	mCursor->Initialize(width, height);
	// マウスカーソルのモデルの読み込み
	mCursor->LoadModel(L"Resources\\okiba2.cmo");

	// タイマーのカウントを０に初期化
	mWaitTimer = 0;

	// シーン切替用変数の初期化
	mSceneFlag = false;
	// 描画画像変更用変数の初期化
	mResultFlag = false;
	// ポーズであるか
	mPauseFlag = false;
	// スタートカウント中であるか
	mStartFlag = true;

	// カウンタの初期化
	mCount = 0;

	// スタートスクリーンのフラグ
	msFlag = PlayGameState::START;
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: 更新                                                                                 //
// @ param	: なし                                                                                 //
// @ return : なし                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void PlayGameLayer::Update()
{
	int w = 0;

	// マップチップの中心
	float cx = 0;
	float cz = 0;
	// オブジェクトの中心
	Vector3 oc = Vector3(0, 0, 0);

	// t = 0：near,t = 1：far
	float t = -1;
	// 自機狙いタイミング
	auto timing = 0;


	//// キャラクターの座標
	//Vector3 chpos = Vector3(0, 0, 0);
	//// カーソルの座標
	//Vector3 cpos = Vector3(0,0,0);

	switch (msFlag)
	{
		case PlayGameState::START:
		{
			mStartFlag = false;
			msFlag = PLAY;
			break;
		}
		case PlayGameState::PLAY:
		{
			// ポーズ中でないなら
			if (!mPauseFlag)
			{
				// 自機狙いタイマーをカウント
				// タイマーをカウントアップさせる
				mWaitTimer++;
				// 自機狙いタイミングをランダムで
				timing = rand() % 100 + 1;
				// タイマーが一定値を超えたらボムを生成
				if (mWaitTimer > 180)
				{
					if (timing % 3 == 0)
					{
						// ボムを生成
						mBomb = make_shared<Bomb>();
						mBomb->Initialize();
						mBomb->SetModel(mBombModel);
						Vector3 pos = mKuma->GetPos();
						pos.y = 50;
						mBomb->SetPos(pos);
						mBombs.push_back(mBomb);
						mWaitTimer = 0;
					}
					else
					{
						// ボムを生成
						mBomb = make_shared<Bomb>();
						mBomb->Initialize();
						mBomb->SetModel(mBombModel);
						Vector3 pos = mMap->GetRandomPos(mMapSize_x, mMapSize_z, mOffset_x, mOffset_z);
						pos.y = 50;
						mBomb->SetPos(pos);
						mBombs.push_back(mBomb);
						mWaitTimer = 0;
					}
				}

				// 生成したすべてのボムを更新
				for (int i = 0; i < (int)(mBombs.size()); i++)
				{
					mBombs[i]->Update();
				}
			}

			// ボムと床のあたり判定
			for (int i = 0; i < (int)(mBombs.size()); i++)
			{
				// 座標から配列の要素番号を算出
				Vector3 bombPos = Vector3(0, 0, 0);
				bombPos.x = floorf(mBombs[i]->GetPos().x + mOffset_x);
				bombPos.z = floorf(mBombs[i]->GetPos().z + mOffset_z);

				// ボムと床が接触していたら
				if (mBombs[i]->GetPos().y < 0)
				{
					// 床の属性を確認
					switch (mMap->GetAttribute((int)(bombPos.x), (int)(bombPos.z)))
					{
						// クッキー床なら
					case COOKIE:
						// クッキー床から穴の床に代入
						mMap->Set((int)(bombPos.x), (int)(bombPos.z), mChip[HOLE]);
						break;
						// ネットなら
					case NET:
						// ボムを消す
						mBombs.pop_back();
						break;
						// それ以外なら
					default:
						// 何もしない
						break;
					}
				}
			}

			// キャラクターの移動
			mKuma->Move();
			// 歩数を取得
			mCount = mKuma->GetCount();

			// キャラクターの座標
			Vector3 chpos = Vector3(0, 0, 0);
			chpos.x = floorf(mKuma->GetPos().x + mOffset_x);
			chpos.z = floorf(mKuma->GetPos().z + mOffset_z);

			// キャラクターのいる床の属性を確認
			switch (mMap->GetAttribute((int)(chpos.x), (int)(chpos.z)))
			{
				// 穴床なら
			case HOLE:
				w++;
				while (w < 600)
				{
					// 落下する
					mKuma->Fall();
					w++;
				}
				if (mKuma->GetPos().y <= -25.0f)
				{
					// ゲームを終了する
					mSceneFlag = true;
				}
				break;
				// ネットなら
			case NET:
				// ゲームを終了する
				mSceneFlag = true;
				break;
				// それ以外なら
			default:
				// 何もしない
				break;
			}

			// ボムとキャラクターのあたり判定
			for (int i = 0; i < (int)(mBombs.size()); i++)
			{
				// ボムとプレイヤーのあたり判定
				if (mBombs[i]->GetPos().x < mKuma->GetPos().x + 0.5f && mBombs[i]->GetPos().x + 0.5f > mKuma->GetPos().x &&
					mBombs[i]->GetPos().z < mKuma->GetPos().z + 0.5f && mBombs[i]->GetPos().z + 0.5f > mKuma->GetPos().z &&
					mBombs[i]->GetPos().y < 0)
				{
					mSceneFlag = true;
				}
			}

			// アイテムとキャラクターのあたり判定
			if (mItem->GetPos().x < mKuma->GetPos().x + 0.5f && mItem->GetPos().x + 0.5f > mKuma->GetPos().x &&
				mItem->GetPos().z < mKuma->GetPos().z + 0.5f && mItem->GetPos().z + 0.5f > mKuma->GetPos().z)
			{
				// ゲームを終了する
				mSceneFlag = true;
				// ゲームクリア
				mResultFlag = true;
			}

			// オブジェクトの中心を算出
			oc = Vector3((1.0f / 2.0f), (1.0f / 2.0f), (1.0f / 2.0f));
			// カーソルの更新
			mCursor->GetCursor()->Update();
			// マウスレイとフィールドのあたり判定（P．１７５）
			mCursor->GetCursor()->IntersectSegmentPlane
			(mCursor->GetCursor()->GetNear(), mCursor->GetCursor()->GetFar(), Vector3(0, 0, 0), Vector3(1, 0, 0), Vector3(0, 0, 1), &t, &mResult);
			// カーソルの座標の更新
			mCursorPos = mResult;
			// 計算したものをfloorfで丸める
			mMapOffset_x = (int)(floorf(mCursorPos.x + mOffset_x));
			mMapOffset_z = (int)(floorf(mCursorPos.z + mOffset_z));
			// マップチップの中心を計算
			cx = 1.0f / 2.0f;
			cz = 1.0f / 2.0f;
			// 丸めたものからずらしている分を引く（+0.5f...マップチップの中心）
			mResult.x = static_cast<float>(mMapOffset_x) + cx - mOffset_x;
			mResult.z = static_cast<float>(mMapOffset_z) + cz - mOffset_z;
			
			// カーソルの座標
			Vector3 cpos = Vector3(0, 0, 0);
			// 座標を設定
			cpos = mResult;
			// ｙ座標を少し高くする
			cpos.y += 0.01f;
			// カーソル座標の設定
			mCursor->SetPos(cpos);

			// マウスが右クリックしたら
			if (g_mouseTracker->rightButton)
			{
				// マウス座標が配列の範囲内にあったら
				if (mMapOffset_x >= 0 && mMapOffset_x < mMapSize_x &&
					mMapOffset_z >= 0 && mMapOffset_z < mMapSize_z)
				{
					// フィールドの属性を変える
					mMap->Set(mMapOffset_x, mMapOffset_z, mChip[NET]);
				}
			}
			break;
		}
	}

/*
	auto flag = START;

	switch (flag)
	{
	case START:
		mStartFlag = false;
		break;
	case PLAY:
		// ポーズ中でないなら
		if (!mPauseFlag)
		{
			// 自機狙いタイマーをカウント
			// タイマーをカウントアップさせる
			mWaitTimer++;
			// 自機狙いタイミングをランダムで
			timing = rand() % 100 + 1;
			// タイマーが一定値を超えたらボムを生成
			if (mWaitTimer > 180)
			{
				if (timing % 3 == 0)
				{
					mBomb = make_shared<Bomb>();
					mBomb->Initialize();
					mBomb->SetModel(mBombModel);
					Vector3 pos = mKuma->GetPos();
					pos.y = 50;
					mBomb->SetPos(pos);
					mBombs.push_back(mBomb);
					mWaitTimer = 0;
				}
				else
				{
					mBomb = make_shared<Bomb>();
					mBomb->Initialize();
					mBomb->SetModel(mBombModel);
					Vector3 pos = mMap->GetRandomPos(mMapSize_x, mMapSize_z, mOffset_x, mOffset_z);
					pos.y = 50;
					mBomb->SetPos(pos);
					mBombs.push_back(mBomb);
					mWaitTimer = 0;
				}
			}

			// 生成したすべてのボムを更新
			for (int i = 0; i < mBombs.size(); i++)
			{
				mBombs[i]->Update();
			}
		}

		// ボムと床のあたり判定
		for (int i = 0; i < mBombs.size(); i++)
		{
			// 座標から配列の要素番号を算出
			Vector3 bombPos = Vector3(0, 0, 0);
			bombPos.x = floorf(mBombs[i]->GetPos().x + mOffset_x);
			bombPos.z = floorf(mBombs[i]->GetPos().z + mOffset_z);

			// ボムと床が接触していたら
			if (mBombs[i]->GetPos().y < 0)
			{
				// 床の属性を確認
				switch (mMap->GetAttribute(bombPos.x, bombPos.z))
				{
					// クッキー床なら
				case COOKIE:
					// クッキー床から穴の床に代入
					mMap->Set(bombPos.x, bombPos.z, mChip[HOLE]);
					break;
					// ネットなら
				case NET:
					// ボムを消す
					mBombs.pop_back();
					break;
					// それ以外なら
				default:
					// 何もしない
					break;
				}
			}
		}

		// キャラクターの移動
		mKuma->Move();
		// 歩数を取得
		mCount = mKuma->GetCount();

		// キャラクターの座標
		Vector3 chpos = Vector3(0, 0, 0);
		chpos.x = floorf(mKuma->GetPos().x + mOffset_x);
		chpos.z = floorf(mKuma->GetPos().z + mOffset_z);

		// キャラクターのいる床の属性を確認
		switch (mMap->GetAttribute(chpos.x, chpos.z))
		{
			// 穴床なら
		case HOLE:
			w++;
			while (w < 600)
			{
				// 落下する
				mKuma->Fall();
				w++;
			}
			if (mKuma->GetPos().y <= -25.0f)
			{
				// ゲームを終了する
				mSceneFlag = true;
			}
			break;
			// ネットなら
		case NET:
			// ゲームを終了する
			mSceneFlag = true;
			break;
			// それ以外なら
		default:
			// 何もしない
			break;
		}

		// ボムとキャラクターのあたり判定
		for (int i = 0; i < mBombs.size(); i++)
		{
			// ボムとプレイヤーのあたり判定
			if (mBombs[i]->GetPos().x < mKuma->GetPos().x + 0.5f && mBombs[i]->GetPos().x + 0.5f > mKuma->GetPos().x &&
				mBombs[i]->GetPos().z < mKuma->GetPos().z + 0.5f && mBombs[i]->GetPos().z + 0.5f > mKuma->GetPos().z &&
				mBombs[i]->GetPos().y < 0)
			{
				mSceneFlag = true;

			}
		}

		// アイテムとキャラクターのあたり判定
		if (mItem->GetPos().x < mKuma->GetPos().x + 0.5f && mItem->GetPos().x + 0.5f > mKuma->GetPos().x &&
			mItem->GetPos().z < mKuma->GetPos().z + 0.5f && mItem->GetPos().z + 0.5f > mKuma->GetPos().z)
		{
			// ゲームを終了する
			mSceneFlag = true;
			// ゲームクリア
			mResultFlag = true;
		}

		// オブジェクトの中心を算出
		oc = Vector3((1.0f / 2.0f), (1.0f / 2.0f), (1.0f / 2.0f));
		// カーソルの更新
		mCursor->GetCursor()->Update();
		// マウスレイとフィールドのあたり判定（P．１７５）
		mCursor->GetCursor()->IntersectSegmentPlane
		(mCursor->GetCursor()->GetNear(), mCursor->GetCursor()->GetFar(), Vector3(0, 0, 0), Vector3(1, 0, 0), Vector3(0, 0, 1), &t, &mResult);
		// カーソルの座標の更新
		mCursorPos = mResult;
		// 計算したものをfloorfで丸める
		mMapOffset_x = floorf(mCursorPos.x + mOffset_x);
		mMapOffset_z = floorf(mCursorPos.z + mOffset_z);
		// マップチップの中心を計算
		cx = 1.0f / 2.0f;
		cz = 1.0f / 2.0f;
		// 丸めたものからずらしている分を引く（+0.5f...マップチップの中心）
		mResult.x = static_cast<float>(mMapOffset_x) + cx - mOffset_x;
		mResult.z = static_cast<float>(mMapOffset_z) + cz - mOffset_z;
		// 座標を設定
		Vector3 cpos = mResult;
		// ｙ座標を少し高くする
		cpos.y += 0.01f;
		// カーソル座標の設定
		mCursor->SetPos(cpos);

		// マウスが右クリックしたら
		if (g_mouseTracker->rightButton)
		{
			// マウス座標が配列の範囲内にあったら
			if (mMapOffset_x >= 0 && mMapOffset_x < mMapSize_x &&
				mMapOffset_z >= 0 && mMapOffset_z < mMapSize_z)
			{
				// フィールドの属性を変える
				mMap->Set(mMapOffset_x, mMapOffset_z, mChip[NET]);
			}
		}
		break;
	default:
		break;
	}
*/

/*
	// スタートカウント中でないなら
	if (!mStartFlag)
	{
		// ポーズ中でないなら
		if (!mPauseFlag)
		{
			// 自機狙いタイマーをカウント
			// タイマーをカウントアップさせる
			mWaitTimer++;
			// 自機狙いタイミングをランダムで
			timing = rand() % 100 + 1;
			// タイマーが一定値を超えたらボムを生成
			if (mWaitTimer > 180)
			{
				if (timing % 3 == 0)
				{
					mBomb = make_shared<Bomb>();
					mBomb->Initialize();
					mBomb->SetModel(mBombModel);
					Vector3 pos = mKuma->GetPos();
					pos.y = 50;
					mBomb->SetPos(pos);
					mBombs.push_back(mBomb);
					mWaitTimer = 0;
				}
				else
				{
					mBomb = make_shared<Bomb>();
					mBomb->Initialize();
					mBomb->SetModel(mBombModel);
					Vector3 pos = mMap->GetRandomPos(mMapSize_x, mMapSize_z, mOffset_x, mOffset_z);
					pos.y = 50;
					mBomb->SetPos(pos);
					mBombs.push_back(mBomb);
					mWaitTimer = 0;
				}
			}
	
			// 生成したすべてのボムを更新
			for (int i = 0; i < mBombs.size(); i++)
			{
				mBombs[i]->Update();
			}
		}
	
		// ボムと床のあたり判定
		for (int i = 0; i < mBombs.size(); i++)
		{
			// 座標から配列の要素番号を算出
			Vector3 bombPos = Vector3(0, 0, 0);
			bombPos.x = floorf(mBombs[i]->GetPos().x + mOffset_x);
			bombPos.z = floorf(mBombs[i]->GetPos().z + mOffset_z);
	
			// ボムと床が接触していたら
			if (mBombs[i]->GetPos().y < 0)
			{
				// 床の属性を確認
				switch (mMap->GetAttribute(bombPos.x, bombPos.z))
				{
					// クッキー床なら
				case COOKIE:
					// クッキー床から穴の床に代入
					mMap->Set(bombPos.x, bombPos.z, mChip[HOLE]);
					break;
					// ネットなら
				case NET:
					// ボムを消す
					mBombs.pop_back();
					break;
					// それ以外なら
				default:
					// 何もしない
					break;
				}
			}
		}
	
		// キャラクターの移動
		mKuma->Move();
		// 歩数を取得
		mCount = mKuma->GetCount();
	
		// キャラクターの座標
		Vector3 chpos = Vector3(0, 0, 0);
		chpos.x = floorf(mKuma->GetPos().x + mOffset_x);
		chpos.z = floorf(mKuma->GetPos().z + mOffset_z);
	
		// キャラクターのいる床の属性を確認
		switch (mMap->GetAttribute(chpos.x, chpos.z))
		{
			// 穴床なら
		case HOLE:
			w++;
			while (w < 600)
			{
				// 落下する
				mKuma->Fall();
				w++;
			}
			if (mKuma->GetPos().y <= -25.0f)
			{
				// ゲームを終了する
				mSceneFlag = true;
			}
			break;
			// ネットなら
		case NET:
			// ゲームを終了する
			mSceneFlag = true;
			break;
			// それ以外なら
		default:
			// 何もしない
			break;
		}
	 
		// ボムとキャラクターのあたり判定
		for (int i = 0; i < mBombs.size(); i++)
		{
			// ボムとプレイヤーのあたり判定
			if (mBombs[i]->GetPos().x < mKuma->GetPos().x + 0.5f && mBombs[i]->GetPos().x + 0.5f > mKuma->GetPos().x &&
				mBombs[i]->GetPos().z < mKuma->GetPos().z + 0.5f && mBombs[i]->GetPos().z + 0.5f > mKuma->GetPos().z &&
				mBombs[i]->GetPos().y < 0)
			{
				mSceneFlag = true;
	
			}
		}

		// アイテムとキャラクターのあたり判定
		if (mItem->GetPos().x < mKuma->GetPos().x + 0.5f && mItem->GetPos().x + 0.5f > mKuma->GetPos().x &&
			mItem->GetPos().z < mKuma->GetPos().z + 0.5f && mItem->GetPos().z + 0.5f > mKuma->GetPos().z)
		{
			// ゲームを終了する
			mSceneFlag = true;
			// ゲームクリア
			mResultFlag = true;
		}


		// オブジェクトの中心を算出
		oc = Vector3((1.0f / 2.0f), (1.0f / 2.0f), (1.0f / 2.0f));
		// カーソルの更新
		mCursor->GetCursor()->Update();
		// マウスレイとフィールドのあたり判定（P．１７５）
		mCursor->GetCursor()->IntersectSegmentPlane
		(mCursor->GetCursor()->GetNear(), mCursor->GetCursor()->GetFar(), Vector3(0, 0, 0), Vector3(1, 0, 0), Vector3(0, 0, 1), &t, &mResult);
		// カーソルの座標の更新
		mCursorPos = mResult;
		// 計算したものをfloorfで丸める
		mMapOffset_x = floorf(mCursorPos.x + mOffset_x);
		mMapOffset_z = floorf(mCursorPos.z + mOffset_z);
		// マップチップの中心を計算
		cx = 1.0f / 2.0f;
		cz = 1.0f / 2.0f;
		// 丸めたものからずらしている分を引く（+0.5f...マップチップの中心）
		mResult.x = static_cast<float>(mMapOffset_x) + cx - mOffset_x;
		mResult.z = static_cast<float>(mMapOffset_z) + cz - mOffset_z;
		// 座標を設定
		Vector3 cpos = mResult;
		// ｙ座標を少し高くする
		cpos.y += 0.01f;
		// カーソル座標の設定
		mCursor->SetPos(cpos);

		// マウスが右クリックしたら
		if (g_mouseTracker->rightButton)
		{
			// マウス座標が配列の範囲内にあったら
			if (mMapOffset_x >= 0 && mMapOffset_x < mMapSize_x &&
				mMapOffset_z >= 0 && mMapOffset_z < mMapSize_z)
			{
				// フィールドの属性を変える
				mMap->Set(mMapOffset_x, mMapOffset_z, mChip[NET]);
			}
		}
	}
*/

#pragma region Debug
	// F1キーが押されたら
	if (g_key.F2)
	{
		// シーンを遷移する
		mSceneFlag = true;
	}

	// Escapeキーを押したら
	if (g_key.Escape)
	{
		// ウインドウを閉じる
		PostQuitMessage(0);
	}
#pragma endregion デバッグ用機能
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: 描画                                                                                 //
// @ param	: なし                                                                                 //
// @ return : なし                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void PlayGameLayer::Draw()
{
	Matrix view = pScene->GetCamera()->CreateViewMatrix();
	Matrix proj = pScene->GetCamera()->CreateProjectionMatrix();

	// マップの描画
	mMap->Draw(view, proj);
	// マウスカーソルの座標計算
	mCursor->GetCursor()->Calc(view, proj);
	mCursor->Calc();
	// マウスカーソルの描画
	mCursor->Draw(view, proj);
	// ボムの描画
	for (int i = 0; i< (int)(mBombs.size()); i++)
	{
		mBombs[i]->Draw(view, proj);
	}
	// キャラクターの描画
	mKuma->Draw(view, proj);
	// アイテムの描画
	mItem->Draw(view, proj);
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: 終了                                                                                 //
// @ param	: なし                                                                                 //
// @ return : なし                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void PlayGameLayer::Finalize()
{
	// マップチップの破棄
	delete mChip[MapChipAttribute::COOKIE];
	delete mChip[MapChipAttribute::HOLE];
	delete mChip[MapChipAttribute::NET];
}
