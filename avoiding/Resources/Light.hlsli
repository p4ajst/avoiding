// �R���X�^���g�o�b�t�@�̒�`
cbuffer Matrixes : register(b0)
{
	// ���[���h�s�񁖃r���[�s�񁖎ˉe�s��
	float4x4 WorldViewProjection;
	// �����W
	float x;
	// �����W
	float z;
}

// �\����
// ���_�V�F�[�_����s�N�Z���V�F�[�_�փf�[�^�̎󂯓n��
struct V2P
{
	// ���W
	float4 pos : SV_POSITION;
	// �@��
	float3 normal : NORMAL;
};
