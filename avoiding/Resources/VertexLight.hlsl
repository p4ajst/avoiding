/* �w�b�_�t�@�C���̃C���N���[�h */
#include "Light.hlsli"

// ----------------------------------------------------------------------------------------------- //
// @ brief	: ���_�V�F�[�_                                                                         //
// @ param	: float4 pos : SV_POSITION...���W                                                      //
// @ param	: float3 normal : NORMAL.....�@��                                                      //
// @ param	: float4 tangent : TANGENT...�ڐ�                                                      //
// @ param	: float4 color : COLOR.......�F                                                        //
// @ param	: float2 uv : TEXCOORD0......�e�N�X�`�����W                                            //
// @ return : V2P...���_�V�F�[�_����s�N�Z���V�F�[�_�ւ̃f�[�^�̎󂯓n��                           //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
V2P main(float4 pos : SV_POSITION,float3 normal : NORMAL,float4 tangent : TANGENT,float4 color : COLOR,float2 uv : TEXCOORD0)
{
	// �߂�l�p�ϐ��̒�`
	V2P result;
	// ���W�ƍs����|�����킹��
	result.pos = mul(pos, WorldViewProjection);
	// �����̖@���f�[�^����
	result.normal = normal;
	// �߂�l
	return result;
}