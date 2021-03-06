﻿// ------------------------------------------------------------------------------------------------ //
// @ file	 : Attribute.h                                                                          //
// @ brief	 : マップチップの属性をもつヘッダファイル                                               //
// @ date	 : 2017/05/09                                                                           //
// @ author  : Madoka Nakajima                                                                      //
// @ note	 :                                                                                      //
// ------------------------------------------------------------------------------------------------ // 
/* 多重インクルードの防止 */
#pragma once
/* 列挙体 */
// ステージの属性
enum MapChipAttribute
{
	// クッキー床
	COOKIE,
	// 穴
	HOLE,
	// ネット
	NET,
	// 数
	ATTRIBUTE_NUM
};
