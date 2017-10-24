/* ヘッダファイルのインクルード */
#include "Light.hlsli"

// ----------------------------------------------------------------------------------------------- //
// @ brief	: 頂点シェーダ                                                                         //
// @ param	: float4 pos : SV_POSITION...座標                                                      //
// @ param	: float3 normal : NORMAL.....法線                                                      //
// @ param	: float4 tangent : TANGENT...接線                                                      //
// @ param	: float4 color : COLOR.......色                                                        //
// @ param	: float2 uv : TEXCOORD0......テクスチャ座標                                            //
// @ return : V2P...頂点シェーダからピクセルシェーダへのデータの受け渡し                           //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
V2P main(float4 pos : SV_POSITION,float3 normal : NORMAL,float4 tangent : TANGENT,float4 color : COLOR,float2 uv : TEXCOORD0)
{
	// 戻り値用変数の定義
	V2P result;
	// 座標と行列を掛け合わせる
	result.pos = mul(pos, WorldViewProjection);
	// 引数の法線データを代入
	result.normal = normal;
	// 戻り値
	return result;
}