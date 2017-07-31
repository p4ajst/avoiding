// ------------------------------------------------------------------------------------------------ //
// @ file	 : MouseCursor.h                                                                        //
// @ brief	 : �}�E�X����Ɋւ���N���X                                                             //
// @ date	 : 2017/06/25                                                                           //
// @ author  : Madoka Nakajima                                                                      //
// @ note	 :                                                                                      //
// @ version : ver.3.00                                                                             //
// ------------------------------------------------------------------------------------------------ // 
/* ���d�C���N���[�h�̖h�~ */
#pragma once

/* �w�b�_�t�@�C���̃C���N���[�h */
// ����w�b�_�t�@�C��
#include <SimpleMath.h>

/* �N���X�錾 */
class MouseCursor
{
	/* �����o�ϐ� */
private:
	/* �X�N���[�����W��̃J�[�\���̈ʒu */
	// ��ԋ߂��X�N���[����̍��W
	DirectX::SimpleMath::Vector3 mNear;
	// ��ԉ����X�N���[����̍��W
	DirectX::SimpleMath::Vector3 mFar;
	// �r���[�|�[�g�̋t�s����������J�[�\��
	DirectX::SimpleMath::Vector3 mNearClip;
	// �r���[�|�[�g�̋t�s����������J�[�\��
	DirectX::SimpleMath::Vector3 mFarClip;
	// �r���[�|�[�g�s��
	DirectX::SimpleMath::Matrix mViewPort;
	// �r���[�|�[�g�̋t�s��
	DirectX::SimpleMath::Matrix mInvertViewPort;
	// ���[���h��ԏ�̃x�N�g��
	DirectX::SimpleMath::Vector3 mVectorWorldNear;
	DirectX::SimpleMath::Vector3 mVectorWorldFar;

	/* �����o�֐� */
public:
	// �����t���R���X�g���N�^
	MouseCursor(int width = 640, int height = 480);
	// �f�X�g���N�^
	~MouseCursor();
	// ������
	void Initialize();
	// �X�V
	void Update();
	// �}�E�X�̍��W�v�Z
	void Calc(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);
	
	bool IntersectSegmentPlane(
		DirectX::SimpleMath::Vector3 a, 
		DirectX::SimpleMath::Vector3 b, 
		DirectX::SimpleMath::Plane p,
		float* t, 
		DirectX::SimpleMath::Vector3* q);
	/* �����������O�p�`�������̕��ʂɑ΂��Č������Ă��邩�ǂ����B
	�������Ă���ꍇ�A���̒l����ь������Ă���ʒu����Ԃ� */
	int IntersectSegmentPlane(
		DirectX::SimpleMath::Vector3 a,
		DirectX::SimpleMath::Vector3 b,
		DirectX::SimpleMath::Vector3 d,
		DirectX::SimpleMath::Vector3 e,
		DirectX::SimpleMath::Vector3 f,
		float* t,
		DirectX::SimpleMath::Vector3* q);

	// getter
	const DirectX::SimpleMath::Vector3 GetNear() { return mVectorWorldNear; }
	const DirectX::SimpleMath::Vector3 GetFar() { return mVectorWorldFar; }
};
