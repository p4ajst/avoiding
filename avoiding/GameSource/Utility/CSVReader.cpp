﻿// ------------------------------------------------------------------------------------------------ //
// @ file	 : CSVReader.cpp                                                                        //
// @ brief	 : CSV読み込みのためのクラス                                                            //
// @ date	 : 2017/01/11                                                                           //
// @ author  : Madoka Nakajima                                                                      //
// @ note	 :                                                                                      //
// @ version : ver.3.00                                                                             //
// ------------------------------------------------------------------------------------------------ // 
/* ヘッダファイルのインクルード */
// 自作ヘッダファイル
#include "CSVReader.h"

/* 名前空間 */
using namespace std;

/* メンバ関数の定義 */
// ----------------------------------------------------------------------------------------------- //
// @ brief	: コンストラクタ                                                                       //
// @ param	: なし                                                                                 //
// @ return : なし                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
CSVReader::CSVReader()
{
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: デストラクタ                                                                         //
// @ param	: なし                                                                                 //
// @ return : なし                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
CSVReader::~CSVReader()
{
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: CSVデータの読み込み                                                                  //
// @ param	: wchar_t* filename...ファイルパス                                                     //
// @ return : bool...読み込めたら、trueを返す。読み込めなかったらfalseを返す。                     //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
bool CSVReader::ReadCSV(wchar_t* filename)
{
	// 読み込むファイル
	ifstream ifs(filename);
	// ファイルが読み込めなかったら
	if (!ifs.is_open())
	{
		return false;
	}
	// ファイルが終わりじゃない間
	while (!ifs.eof())
	{
		// １行分を格納
		string buff;
		// １行分のコンマで区切られた値を格納
		vector<int> buf;
		// 改行するまで読み込む
		getline(ifs, buff);
		// コンマごと区切られた数値を取り出す
		buf = Split(buff, ',');
		// 値の格納
		mData.push_back(buf);
	}
	return true;
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: １行を読み込む                                                                       //
// @ param	: const string& str...１行分のコンマで区切られた値                                     //
// @ param	: char delimiter...区切る文字                                                          //
// @ return : 読み込んだ１行の文字を格納した配列                                                   //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
vector<int> CSVReader::Split(const string & str, char delimiter)
{
	// ストリングストリーム
	stringstream sstrm(str);
	// コンマが来るまでの文字列を格納
	string buf;
	// 結果を格納する配列
	vector<int> result;

	while (getline(sstrm, buf, delimiter))
	{
		// bufが空っぽじゃなかったら
		if (!buf.empty())
		{
			// 値の格納
			result.push_back(stoi(buf));
		}
	}
	return result;
}

