/* ヘッダファイルのインクルード */
#include "Light.hlsli"

// ----------------------------------------------------------------------------------------------- //
// @ brief	: 頂点シェーダ                                                                         //
// @ param	: V2P 頂点シェーダから受け渡されたデータ                                               //
// @ return : float4...最終的な色                                                                  //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
float4 main(V2P) : SV_TARGET
{
	// ライトの向き
	const float3 lightDirection = float3(Matrixes.x, 75.0f, Matrixes.z);
	// 法線の正規化
	float3 normal = normalize(pixel.normal);
	// 明るさを計算
	float light = dot(normal, lightDirection);
	// 最終的な色
	return float4(light.xxx, 1.0f);
}