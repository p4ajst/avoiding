/* �w�b�_�t�@�C���̃C���N���[�h */
#include "Light.hlsli"

// ----------------------------------------------------------------------------------------------- //
// @ brief	: ���_�V�F�[�_                                                                         //
// @ param	: V2P ���_�V�F�[�_����󂯓n���ꂽ�f�[�^                                               //
// @ return : float4...�ŏI�I�ȐF                                                                  //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
float4 main(V2P) : SV_TARGET
{
	// ���C�g�̌���
	const float3 lightDirection = float3(Matrixes.x, 75.0f, Matrixes.z);
	// �@���̐��K��
	float3 normal = normalize(pixel.normal);
	// ���邳���v�Z
	float light = dot(normal, lightDirection);
	// �ŏI�I�ȐF
	return float4(light.xxx, 1.0f);
}