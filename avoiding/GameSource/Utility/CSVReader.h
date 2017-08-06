// ------------------------------------------------------------------------------------------------ //
// @ file	 : CSVReader.h                                                                          //
// @ brief	 : CSV読み込みのためのクラス                                                            //
// @ date	 : 2017/01/11                                                                           //
// @ author  : Madoka Nakajima                                                                      //
// @ note	 :                                                                                      //
// @ version : ver.3.00                                                                             //
// ------------------------------------------------------------------------------------------------ // 
/* 多重インクルードの防止 */
#pragma once

/* ヘッダファイルのインクルード */
// 入出力
#include <iostream>
// ファイル読み込み
#include <fstream>
// istringstreamを使う為
#include <sstream>
// 文字列
#include <string>
// 動的配列
#include <vector>

/* クラス宣言 */
class CSVReader
{
	/* メンバ変数 */
	// データを格納する配列
	std::vector<std::vector<int>> mData;
	// マップのサイズ
	int mapSize_x;
	int mapSize_z;
	/* メンバ関数 */
	// コンマで区切られた値を取り出す
	std::vector<int> Split(const std::string& str, char delimiter);
public:
	/* メンバ関数 */
	// コンストラクタ
	CSVReader();
	// デストラクタ
	~CSVReader();
	// CSVファイルを読み込む
	bool ReadCSV(wchar_t* filename);
	// 読み込んだファイルの中のデータを取得
	std::vector<std::vector<int>> GetData() { return mData; }
};

