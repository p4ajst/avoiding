// コンスタントバッファの定義
cbuffer Matrixes : register(b0)
{
	// ワールド行列＊ビュー行列＊射影行列
	float4x4 WorldViewProjection;
	// ｘ座標
	float x;
	// ｚ座標
	float z;
}

// 構造体
// 頂点シェーダからピクセルシェーダへデータの受け渡し
struct V2P
{
	// 座標
	float4 pos : SV_POSITION;
	// 法線
	float3 normal : NORMAL;
};
