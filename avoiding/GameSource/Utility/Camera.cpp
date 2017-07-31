// ------------------------------------------------------------------------------------------------ //
// @ file	 : Camera.cpp                                                                           //
// @ brief	 : �J�����N���X�̃\�[�X�t�@�C��                                                         //
// @ date	 : 2016/09/01                                                                           //
// @ author  : Madoka Nakajima                                                                      //
// @ note	 : ����J�����N���X                                                                     //
// @ version : ver.3.00                                                                             //
// ------------------------------------------------------------------------------------------------ // 
/* ���d�C���N���[�h�̖h�~ */
/* �w�b�_�t�@�C���̃C���N���[�h */
#include "Camera.h"
/* ���O��� */
using namespace DirectX;
using namespace DirectX::SimpleMath;

/* �֐��̒�` */
// ----------------------------------------------------------------------------------------------- //
// @ brief	: ����                                                                                 //
// @ param	: Vector3 v1                                                                           //
// @ param	: Vector3 v2                                                                           //
// @ return : float dots                                                                           //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
float Dot(DirectX::SimpleMath::Vector3 v1, DirectX::SimpleMath::Vector3 v2)
{
	float dots;
	dots = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	return dots;
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: �O��                                                                                 //
// @ param	: Vector3 v1                                                                           //
// @ param	: Vector3 v2                                                                           //
// @ return : Vector3 crossvec                                                                     //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
Vector3 Cross(DirectX::SimpleMath::Vector3 v1, DirectX::SimpleMath::Vector3 v2)
{
	Vector3 crossvec;
	crossvec.x = v1.y * v2.z - v1.z * v2.y;
	crossvec.y = v1.z * v2.x - v1.x * v2.z;
	crossvec.z = v1.x * v2.y - v1.y * v2.x;
	return crossvec;
}

/* �����o�֐��̒�` */
// ----------------------------------------------------------------------------------------------- //
// @ brief	: �R���X�g���N�^                                                                       //
// @ param	: ����                                                                                 //
// @ return : ����                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
Camera::Camera()
	:mEye(Vector3(0, 0, 0))
	,mRef(Vector3(0, 0, 10))
	,mUp(Vector3(0, 1, 0))
	,mFovY(XMConvertToRadians(45.0f))
	,mAspect(640.0f / 480.0f)
	,mNearClip(0.1f)
	,mFarClip(1000.0f)
{
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: �f�X�g���N�^                                                                         //
// @ param	: ����                                                                                 //
// @ return : ����                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
Camera::~Camera()
{
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: �X�V����                                                                             //
// @ param	: ����                                                                                 //
// @ return : ����                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void Camera::Update()
{
	CreateViewMatrix();
	CreateProjectionMatrix();
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: �r���[�s����쐬 �@                                                                  //
// @ param	: ����                                                                                 //
// @ return : Matrix m_view	                                                                       //
// @ note	: = Matrix::CreateLookAt                                                               //
// ----------------------------------------------------------------------------------------------- // 
Matrix Camera::CreateViewMatrix()
{
	// ���������x�N�g��
	Vector3 eyeDirection;
	// �J�����̂������x�N�g��
	Vector3 camera_x;
	// �J�����̏�����x�N�g��
	Vector3 new_up;
	// ���������x�N�g�������߂�(�Q�Ɠ_ - ���_)
	eyeDirection = mEye - mRef;
	// ���������x�N�g���̐��K��
	eyeDirection.Normalize();
	// �J�����̂������x�N�g�������߂�(�O��)
	camera_x = Cross(mUp, eyeDirection);
	// �J�����̂������x�N�g���̐��K��
	camera_x.Normalize();
	// �J�����̏�����x�N�g�������߂�(�O��)
	new_up = Cross(eyeDirection, camera_x);

	// �s������
	mView.m[0][0] = camera_x.x;
	mView.m[0][1] = new_up.x;
	mView.m[0][2] = eyeDirection.x;
	mView.m[0][3] = 0;
	mView.m[1][0] = camera_x.y;
	mView.m[1][1] = new_up.y;
	mView.m[1][2] = eyeDirection.y;
	mView.m[1][3] = 0;
	mView.m[2][0] = camera_x.z;
	mView.m[2][1] = new_up.z;
	mView.m[2][2] = eyeDirection.z;
	mView.m[2][3] = 0;
	mView.m[3][0] = -(Dot(camera_x, GetEye()));
	mView.m[3][1] = -(Dot(new_up, GetEye()));
	mView.m[3][2] = -(Dot(eyeDirection, GetEye()));
	mView.m[3][3] = 1;

	return mView;
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: �v���W�F�N�V�����s����쐬                                                           //
// @ param	: ����                                                                                 //
// @ return : Matrix m_projection                                                                  //
// @ note	: = Matrix::CreatePerspectiveFieldOfView                                               //
// ----------------------------------------------------------------------------------------------- // 
Matrix Camera::CreateProjectionMatrix()
{
	mProjection = Matrix::CreatePerspectiveFieldOfView(mFovY, mAspect, mNearClip, mFarClip);
	return mProjection;
}
