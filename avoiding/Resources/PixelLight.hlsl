/* �w�b�_�t�@�C���̃C���N���[�h */
#include "Light.hlsli"

// ----------------------------------------------------------------------------------------------- //
// @ brief	: �s�N�Z���V�F�[�_                                                                     //
// @ param	: V2P ���_�V�F�[�_����󂯓n���ꂽ�f�[�^                                               //
// @ return : float4...�ŏI�I�ȐF                                                                  //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
float4 main(V2P v2p) : SV_TARGET
{
    // ���ʊi�[�p�ϐ�
    float4 result;
	// ���C�g�̌���
    const float3 lightDirection = float3(x, 75.0f, z);
	// �@���̐��K��
	float3 normal = normalize(v2p.normal);
	// ���邳���v�Z
	float light = dot(normal, lightDirection);
    result = float4(light.xxx, 1.0f);
    // �ŏI�I�ȐF
	return result;
}