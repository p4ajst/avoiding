// ------------------------------------------------------------------------------------------------ //
// @ file	 : MouseCursor.cpp                                                                      //
// @ brief	 : �}�E�X����Ɋւ���N���X                                                             //
// @ date	 : 2017/06/25                                                                           //
// @ author  : Madoka Nakajima                                                                      //
// @ note	 :                                                                                      //
// @ version : ver.3.00                                                                             //
// ------------------------------------------------------------------------------------------------ // 
/* �w�b�_�t�@�C���̃C���N���[�h */
// �搶�̃t���[�����[�N
#include "../../ImaseLib/DirectXTK.h"
// ����w�b�_�t�@�C��
#include "MouseCursor.h"

/* ���O��� */
using namespace DirectX::SimpleMath;

/* �����o�֐��̒�` */
// ----------------------------------------------------------------------------------------------- //
// @ brief	: �����t���R���X�g���N�^                                                               //
// @ param	: int width...�N���C�A���g�̈�̕�                                                     //
// @ param	: int height...�N���C�A���g�̈�̍���                                                  //
// @ return : �Ȃ�                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
MouseCursor::MouseCursor(int width, int height)
	:mNear(width / 2, height / 2, 0)
	, mFar(width / 2, height / 2, 1)
	, mNearClip(0, 0, 0)
	, mFarClip(0, 0, 0)
	, mViewPort
	(
		width / 2,           0, 0, 0,
		        0, -height / 2, 0, 0,
		        0,           0, 1, 0,
		width / 2,  height / 2, 0, 1
	)
{
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: �f�X�g���N�^                                                                         //
// @ param	: �Ȃ�                                                                                 //
// @ return : �Ȃ�                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
MouseCursor::~MouseCursor()
{
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: ������                                                                               //
// @ param	: �Ȃ�                                                                                 //
// @ return : �Ȃ�                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void MouseCursor::Initialize()
{
	// �r���[�|�[�g�̋t�s����v�Z
	mViewPort.Invert(mInvertViewPort);
	// ��ԋ߂��X�N���[����̍��W�ɋt�s���������
	mNearClip = Vector3::Transform(mNear, mInvertViewPort);
	// ��ԉ����X�N���[����̍��W�ɋt�s���������
	mFarClip = Vector3::Transform(mFar, mInvertViewPort);
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: �X�V                                                                                 //
// @ param	: �Ȃ�                                                                                 //
// @ return : �Ȃ�                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void MouseCursor::Update()
{
	// ��ԉ����X�N���[����̍��W�̐ݒ�
	mNear.x = g_mouse.x;
	mNear.y = g_mouse.y;
	// ��ԉ����X�N���[����̍��W�̐ݒ�
	mFar.x = g_mouse.x;
	mFar.y = g_mouse.y;
	// �r���[�|�[�g�̋t�s��𗘗p���ăj�A�N���b�v���g�����X�t�H�[������
	mNearClip = Vector3::Transform(mNear, mInvertViewPort);
	// �r���[�|�[�g�̋t�s��𗘗p���ăt�@�[�N���b�v���g�����X�t�H�[������
	mFarClip = Vector3::Transform(mFar, mInvertViewPort);
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: �}�E�X�̍��W�v�Z                                                                     //
// @ param	: Matrix view...�r���[�s��                                                             //
// @ param	: Matrix proj...�ˉe�s��                                                               //
// @ return : �Ȃ�                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void MouseCursor::Calc(Matrix view, Matrix proj)
{
	Matrix mat;
	Matrix tmp;
	mat = view * proj;
	mat.Invert(tmp);

	mVectorWorldNear = Vector3::Transform(mNearClip, tmp);
	mVectorWorldFar = Vector3::Transform(mFarClip, tmp);
}
// ----------------------------------------------------------------------------------------------- //
// @ brief	:                                                                                      //
// @ param	: Vector3 a...�����̂��钼��                                                           //
// @ param	: Vector3 b...�����̂��钼��                                                           //
// @ param	: Plane p...����                                                                       //
// @ param	: float* t...�����̂��钼���ɑ΂��ĕ��ʂƌ�������l                                    //
// @ param	: Vector3* q...�����_                                                                  //
// @ return : bool...�������Ă��邩�ǂ���                                                                      //
// @ note	: ���A���^�C���Փ˔���o�D�P�V�T                                                       //
// ----------------------------------------------------------------------------------------------- // 
bool MouseCursor::IntersectSegmentPlane(Vector3 a, Vector3 b, Plane p, float* t, Vector3* q)
{
	// �����̂��钼�������ɑ΂��ĕ��ʂƌ������邔�̒l���v�Z
	Vector3 ab = b - a;
	*t = (p.D() - p.Normal().Dot(a)) / p.Normal().Dot(ab);
	// ����[0..1]�̒��ɂ���ꍇ�͌v�Z�������_��Ԃ�
	if (*t >= 0.0f && *t <= 1.0f)
	{
		*q = a + (*t) * ab;
		return true;
	}

	// �����łȂ���Ό����͂Ȃ�
	return false;
}


// ----------------------------------------------------------------------------------------------- //
// @ brief	: ����ab���O�p�`def�̕��ʂɑ΂��Č������Ă��邩�ǂ���                                  //
// @ param	: Vector3 a....�����̓_                                                                //
// @ param	: Vector3 b....�����̓_                                                                //
// @ param	: Vector3 d....�O�p�`�̓_                                                              //
// @ param	: Vector3 e....�O�p�`�̓_                                                              //
// @ param	: Vector3 f....�O�p�`�̓_                                                              //
// @ param	: float* t....                                                                         //
// @ param	: Vector3* q....�������Ă���ʒu                                                       //
// @ return : �������Ă���ꍇ�At�̒l����ь������Ă���ʒuq��Ԃ�                                 //
// @ note	: ���A���^�C���Փ˔���o�D�P�V�T                                                       //
// ----------------------------------------------------------------------------------------------- // 
int MouseCursor::IntersectSegmentPlane(Vector3 a, Vector3 b, Vector3 d, Vector3 e, Vector3 f, float* t, Vector3* q)
{
	Vector3 aa = e - d;
	Vector3 bb = f - d;
	Vector3 n = aa.Cross(bb);
	float dd = n.Dot(d);
	Plane p(n, dd);
	return IntersectSegmentPlane(a, b, p, t, q);
}
