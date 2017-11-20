/* ヘッダファイルのインクルード */
#include "Light.hlsli"

// ----------------------------------------------------------------------------------------------- //
// @ brief	: ピクセルシェーダ                                                                     //
// @ param	: V2P 頂点シェーダから受け渡されたデータ                                               //
// @ return : float4...最終的な色                                                                  //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
float4 main(V2P v2p) : SV_TARGET
{
    // 結果格納用変数
    float4 result;
	// ライトの向き
    const float3 lightDirection = float3(x, 75.0f, z);
	// 法線の正規化
	float3 normal = normalize(v2p.normal);
	// 明るさを計算
	float light = dot(normal, lightDirection);
    result = float4(light.xxx, 1.0f);
    // 最終的な色
	return result;
}