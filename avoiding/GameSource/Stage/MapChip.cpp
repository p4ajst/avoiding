// ------------------------------------------------------------------------------------------------ //
// @ file	 : MapChip.cpp                                                                          //
// @ brief	 : マップチップに関するクラ                                                             //
// @ date	 : 2017/06/25                                                                           //
// @ author  : Madoka Nakajima                                                                      //
// @ note	 :                                                                                      //
// @ version : ver.3.00                                                                             //
// ------------------------------------------------------------------------------------------------ // 
/* ヘッダファイルのインクルード */
#include "MapChip.h"

/* 名前空間 */
using namespace std;
using namespace DirectX;

/* メンバ関数の定義 */
// ----------------------------------------------------------------------------------------------- //
// @ brief	: コンストラクタ                                                                       //
// @ param	: 無し                                                                                 //
// @ return : 無し                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
MapChip::MapChip()
{
	// 初期化
	mAttribute = 0;
	mModel = nullptr;
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: 引数付きコンストラクタ                                                               //
// @ param	: int attribute...整数型の属性                                                         //
// @ return : 無し                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
MapChip::MapChip(int attribute)
{
	mAttribute = attribute;
	mModel = nullptr;
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: デストラクタ                                                                         //
// @ param	: 無し                                                                                 //
// @ return : 無し                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
MapChip::~MapChip()
{

}

