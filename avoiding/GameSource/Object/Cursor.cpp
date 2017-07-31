// ------------------------------------------------------------------------------------------------ //
// @ file	 : Cursor.cpp                                                                           //
// @ brief	 : �J�[�\���Ɋւ���N���X                                                               //
// @ date	 : 2017/06/25                                                                           //
// @ author  : Madoka Nakajima                                                                      //
// @ note	 :                                                                                      //
// @ version : ver.3.00                                                                             //
// ------------------------------------------------------------------------------------------------ // 
/* ���d�C���N���[�h�̖h�~ */

/* �w�b�_�t�@�C���̃C���N���[�h */
// �搶�̃t���[�����[�N
#include "../../ImaseLib/Direct3D.h"
#include "../../ImaseLib/DirectXTK.h"
// ����w�b�_�t�@�C��
#include "Cursor.h"

/* ���O��� */
using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

/* �����o�֐��̒�` */
// ----------------------------------------------------------------------------------------------- //
// @ brief	: ������                                                                               //
// @ param	: int width...�N���C�A���g�̈�̕�                                                     //
// @ param	: int height...�N���C�A���g�̈�̍���                                                  //
// @ return : �Ȃ�                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void Cursor::Initialize(int width, int height)
{
	// �����o�ϐ��̏�����
	mDef = make_shared<DGSLEffectFactory>(g_pd3dDevice.Get());
	mDef->SetDirectory(L"Resources");
	mModel = nullptr;
	mPosition = Vector3(0, 0, 0);
	mAngle = 0;
	mScalingFactor = 1;
	mLocalWorld = Matrix::Identity;

	mMouseCursor = make_shared<MouseCursor>(width, height);
	mMouseCursor->Initialize();
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: �X�V                                                                                 //
// @ param	: �Ȃ�                                                                                 //
// @ return : �Ȃ�                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void Cursor::Update()
{
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: �X�V                                                                                 //
// @ param	: float ox...�I�t�Z�b�g�̂�                                                            //
// @ param	: float oz...�I�t�Z�b�g�̂�                                                            //
// @ return : �Ȃ�                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void Cursor::Update(float ox, float oz)
{

}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: �`��                                                                                 //
// @ param	: �Ȃ�                                                                                 //
// @ return : �Ȃ�                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void Cursor::Draw(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj)
{
	mMouseCursor->Calc(view, proj);
	/*
		brief    :�`��
		param[in]:�R���e�L�X�g
		param[in]:�X�e�[�g
		param[in]:���[���h�s��
		param[in]:�r���[�s��
		param[in]:�ˉe�s��
		param[in]:���C���[�t���[�����ǂ���
		param[in]:�����_��
	*/
	mModel->Draw(g_pImmediateContext.Get(), *g_state.get(), mLocalWorld, view, proj, false,
		[&]()
	{
		// �u�����h�X�e�[�g�̐ݒ�i�������j
		g_pImmediateContext->OMSetBlendState(g_state->NonPremultiplied(), nullptr, 0xffffffff);
	});
}
