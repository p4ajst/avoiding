// ------------------------------------------------------------------------------------------------ //
// @ file	 : Character.h                                                                          //
// @ brief	 : �L�����N�^�[�Ɋւ���N���X                                                           //
// @ date	 : 2017/06/25                                                                           //
// @ author  : Madoka Nakajima                                                                      //
// @ note	 :                                                                                      //
// @ version : ver.3.00                                                                             //
// ------------------------------------------------------------------------------------------------ // 
/* ���d�C���N���[�h�̖h�~ */
#pragma once

/* �w�b�_�t�@�C���̃C���N���[�h */
// ����w�b�_�t�@�C��
#include "Actor.h"

/* �N���X�錾 */
class Character :public Actor
{
	/* �����o�ϐ� */
private:
	// ���x
	DirectX::SimpleMath::Vector3 mVelocity;
	// ����
	int mStepCount;
	/* �����o�֐� */
public:
	// �R���X�g���N�^
	Character() = default;
	// �f�X�g���N�^
	~Character() = default;
	// �ړ�
	void Move();
	// ����
	void Fall();
	// �ݒ�
	void SetVel(DirectX::SimpleMath::Vector3 vel) { mVelocity = vel; }
	// �擾
	DirectX::SimpleMath::Vector3 GetVel() { return mVelocity; }
	int GetCount() { return mStepCount; }
};
