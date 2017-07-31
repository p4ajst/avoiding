// ------------------------------------------------------------------------------------------------ //
// @ file	 : Camera.h                                                                             //
// @ brief	 : �J�����N���X�̃w�b�_�t�@�C��                                                         //
// @ date	 : 2016/09/01                                                                           //
// @ author  : Madoka Nakajima                                                                      //
// @ note	 : ����J�����N���X                                                                     //
// @ version : ver.3.00                                                                             //
// ------------------------------------------------------------------------------------------------ //
/* ���d�C���N���[�h�̖h�~ */
#pragma once 
/* �w�b�_�t�@�C���̃C���N���[�h */
// �W�����C�u����
#include <SimpleMath.h>

/* �֐��̃v���g�^�C�v�錾 */
// ����
float Dot(DirectX::SimpleMath::Vector3 v1, DirectX::SimpleMath::Vector3 v2);
// �O��
DirectX::SimpleMath::Vector3 Cross(DirectX::SimpleMath::Vector3 v1, DirectX::SimpleMath::Vector3 v2);

/* �N���X�錾 */
class Camera
{
	/* �����o�ϐ� */
protected:
	/* �r���[�s�� */
	// ���_
	DirectX::SimpleMath::Vector3 mEye;
	// �����X(�Q�Ɠ_)
	DirectX::SimpleMath::Vector3 mRef;
	// �J�����̏����
	DirectX::SimpleMath::Vector3 mUp;
	// �r���[�s��
	DirectX::SimpleMath::Matrix mView;

	/* �v���W�F�N�V�����s��(�ˉe�s��) */
	// ��������p
	float mFovY;
	// �A�X�y�N�g��
	float mAspect;
	// �j�A�N���b�v
	float mNearClip;
	// �t�@�[�N���b�v
	float mFarClip;
	// �v���W�F�N�V�����s��
	DirectX::SimpleMath::Matrix mProjection;

	/* �����o�֐� */
public:
	// �R���X�g���N�^
	Camera();
	// �f�X�g���N�^
	~Camera();

	// �X�V����
	void Update();

	// ���_�̐ݒ�
	void SetEye(DirectX::SimpleMath::Vector3 eye) { mEye = eye; }
	// �Q�Ɠ_�̐ݒ�
	void SetRef(DirectX::SimpleMath::Vector3 ref) { mRef = ref; }
	// ������x�N�g���̐ݒ�
	void SetUp(DirectX::SimpleMath::Vector3 up) { mUp = up; }
	// ���_�̎擾
	DirectX::SimpleMath::Vector3 GetEye() { return mEye; }
	// �Q�Ɠ_�̎擾
	DirectX::SimpleMath::Vector3 GetRef() { return mRef; }
	// ������x�N�g���̎擾
	DirectX::SimpleMath::Vector3 GetUp() { return mUp; }

	// ��������p�̐ݒ�
	void SetFovY(float fovY) { mFovY = fovY; }
	// �A�X�y�N�g��̐ݒ�
	void SetAspect(float aspect) { mAspect = aspect; }
	// �j�A�N���b�v�̐ݒ�
	void SetNearClip(float nearClip) { mNearClip = nearClip; }
	// �t�@�[�N���b�v�̐ݒ�
	void SetFarClip(float farClip) { mFarClip = farClip; }

	// �r���[�s����쐬
	DirectX::SimpleMath::Matrix CreateViewMatrix();
	// �v���W�F�N�V�����s����쐬
	DirectX::SimpleMath::Matrix CreateProjectionMatrix();

	// �r���[�s����擾
	DirectX::SimpleMath::Matrix GetViewMat() { return mView; }
	// �v���W�F�N�V�����s����擾
	DirectX::SimpleMath::Matrix GetProjMat() { return mProjection; }
};
