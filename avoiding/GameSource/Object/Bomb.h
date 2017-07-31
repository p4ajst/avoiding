// ------------------------------------------------------------------------------------------------ //
// @ file	 : Bomb.h                                                                               //
// @ brief	 : ���e�Ɋւ���N���X                                                                   //
// @ date	 : 2017/06/25                                                                           //
// @ author  : Madoka Nakajima                                                                      //
// @ note	 :                                                                                      //
// @ version : ver.3.00                                                                             //
// ------------------------------------------------------------------------------------------------ // 
/* ���d�C���N���[�h�̖h�~ */
#pragma once

/* �w�b�_�t�@�C���̃C���N���[�h */
#include <vector>
// ����w�b�_�t�@�C��
#include "Actor.h"
#include "../Stage/Map.h"

/* �萔��` */
// �d��
static const float GRAVITY = 0.980665f;

/* �N���X�錾 */
class Bomb :public Actor
{
	/* �����o�ϐ� */
private:
	// �{���̔z��
	std::vector<std::shared_ptr<Bomb>> mBombs;
	// ���x
	DirectX::SimpleMath::Vector3 mVelocity;
	// map
	std::shared_ptr<Map> mMap;
	// ��������
	float mTime;
	// �t���O
	bool mFlag;

	/* �����o�֐� */
public:
	// �R���X�g���N�^
	Bomb() = default;
	// �f�X�g���N�^
	~Bomb() = default;
	// ������
	void Initialize();
	// �X�V
	void Update();
	// ���R����
	void FreeFall();
	// ���W�ɑ��x�𑫂�
	void AddPos();
	// �ݒ�
	void SetVel(DirectX::SimpleMath::Vector3 vel) { mVelocity = vel; }
	//void SetFlag(bool flag) { mFlag = flag; }
	// �擾
	DirectX::SimpleMath::Vector3 GetVel() { return mVelocity; }
	bool GetFlag() { return mFlag; }
};