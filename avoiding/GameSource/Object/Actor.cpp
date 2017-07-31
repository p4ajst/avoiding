// ------------------------------------------------------------------------------------------------ //
// @ file	 : Actor.cpp                                                                            //
// @ brief	 : �o�ꕨ�̊��N���X                                                                   //
// @ date	 : 2017/06/25                                                                           //
// @ author  : Madoka Nakajima                                                                      //
// @ note	 :                                                                                      //
// @ version : ver.3.00                                                                             //
// ------------------------------------------------------------------------------------------------ // 
/* �w�b�_�t�@�C���̃C���N���[�h */
// �搶�̃t���[�����[�N
#include "../../ImaseLib/Direct3D.h"
#include "../../ImaseLib/DirectXTK.h"
// ����w�b�_�t�@�C��
#include "Actor.h"

/* ���O��� */
using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

/* �����o�֐��̒�` */
// ----------------------------------------------------------------------------------------------- //
// @ brief	: ������                                                                               //
// @ param	: �Ȃ�                                                                                 //
// @ return : �Ȃ�                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void Actor::Initialize()
{
	// �����o�ϐ��̏�����
	mDef = make_shared<DGSLEffectFactory>(g_pd3dDevice.Get());
	mDef->SetDirectory(L"Resources");
	mModel = nullptr;
	mPosition = Vector3(0, 0, 0);
	mAngle = 0;
	mScalingFactor = 1;
	mLocalWorld = Matrix::Identity;
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: �X�V                                                                                 //
// @ param	: �Ȃ�                                                                                 //
// @ return : �Ȃ�                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void Actor::Update()
{

}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: �`��                                                                                 //
// @ param	: �Ȃ�                                                                                 //
// @ return : �Ȃ�                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void Actor::Draw(Matrix view, Matrix proj)
{
	Calc();
	mModel->Draw(g_pImmediateContext.Get(), *g_state, mLocalWorld, view, proj);
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: �I��                                                                                 //
// @ param	: �Ȃ�                                                                                 //
// @ return : �Ȃ�                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void Actor::Finalize()
{
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: ���f���̓ǂݍ���                                                                     //
// @ param	: wchar_t* filename                                                                    //
// @ return : �Ȃ�                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void Actor::LoadModel(wchar_t * filename)
{
	mModel = Model::CreateFromCMO(g_pd3dDevice.Get(), filename, *mDef);
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: �s��v�Z                                                                             //
// @ param	: �Ȃ�                                                                                 //
// @ return : �Ȃ�                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void Actor::Calc()
{
	Matrix scale;
	Matrix rotate;
	Matrix trans;

	scale = Matrix::CreateScale(mScalingFactor);
	rotate = Matrix::CreateRotationY(XMConvertToRadians(mAngle));
	trans = Matrix::CreateTranslation(mPosition);

	mLocalWorld = scale * rotate * trans;
}
