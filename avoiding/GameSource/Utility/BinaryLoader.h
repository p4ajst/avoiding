#pragma once
#include <fstream>
#include <vector>

class BinaryLoader
{
	// バイナリで読み込んだデータを格納する変数
	std::vector<char> mData;
public:
	// コンストラクタ
	BinaryLoader();
	// デストラクタ
	~BinaryLoader();
	// バイナリデータの読み込み
	bool Load(const char* filename);
	// バイナリデータの取得
	std::vector<char> GetData() { return mData; }
};