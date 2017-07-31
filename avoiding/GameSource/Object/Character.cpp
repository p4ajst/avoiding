// ------------------------------------------------------------------------------------------------ //
// @ file	 : Character.cpp                                                                        //
// @ brief	 : �L�����N�^�[�Ɋւ���N���X                                                           //
// @ date	 : 2017/06/25                                                                           //
// @ author  : Madoka Nakajima                                                                      //
// @ note	 :                                                                                      //
// @ version : ver.3.00                                                                             //
// ------------------------------------------------------------------------------------------------ // 
/* �w�b�_�t�@�C���̃C���N���[�h */
// ����w�b�_�t�@�C��
#include "Character.h"
#include "../../ImaseLib/DirectXTK.h"

/* ���O��� */
using namespace DirectX;
using namespace DirectX::SimpleMath;

/* �����o�֐��̒�` */
// ----------------------------------------------------------------------------------------------- //
// @ brief	: �ړ�                                                                                 //
// @ param	: �Ȃ�                                                                                 //
// @ return : �Ȃ�                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void Character::Move()
{
	if (g_keyTracker->pressed.A)
	{
		mAngle = 270;
		mVelocity = Vector3(-1, 0, 0);
		mPosition += mVelocity;
		mStepCount += 1;
	}
	if (g_keyTracker->pressed.D)
	{
		mAngle = 90;
		mVelocity = Vector3(1, 0, 0);
		mPosition += mVelocity;
		mStepCount += 1;
	}
	if (g_keyTracker->pressed.W)
	{
		mAngle = 180;
		mVelocity = Vector3(0, 0, -1);
		mPosition += mVelocity;
		mStepCount += 1;
	}
	if (g_keyTracker->pressed.S)
	{
		mAngle = 0;
		mVelocity = Vector3(0, 0, 1);
		mPosition += mVelocity;
		mStepCount += 1;
	}
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: ����                                                                                 //
// @ param	: �Ȃ�                                                                                 //
// @ return : �Ȃ�                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void Character::Fall()
{
	// �d��
	float GRAVITY = 0.980665f;

	// ���x���v�Z�i-�d�͉����x �� �����o�ߎ��ԁj
	mVelocity.y = -GRAVITY * 0.0005f;
	mPosition.y += mVelocity.y;
}
