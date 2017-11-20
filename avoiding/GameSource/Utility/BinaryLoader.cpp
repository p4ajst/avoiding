// 参考サイト：http://miffysora.wikidot.com/ja:fileread

#include <fstream>
#include <iostream>
#include <cassert>

#include "BinaryLoader.h"

using namespace std;

BinaryLoader::BinaryLoader()
{
}


BinaryLoader::~BinaryLoader()
{
}

bool BinaryLoader::Load(const char* filename)
{
	// 入力のファイルストリームの変数
	ifstream ifs;
	// データをバイナリで読み込む
	ifs = ifstream(filename, ios::in | ios::binary);
	if (ifs)
	{
		// バイナリデータの長さ
		size_t size = 0;
		// ファイル位置を終端まで移動
		ifs.seekg(0, ifs.end);
		// ファイルの終端の位置を保存
		size = ifs.tellg();
		// ファイルの終端の位置を保存
		ifs.seekg(0, ifs.beg);
		// 配列のリサイズ
		mData.resize(size);
		// バイナリファイルの読み込み
		ifs.read(mData.data(), mData.size());
	}
	else
	{
		return false;
	}
}

