// ------------------------------------------------------------------------------------------------ //
// @ file	 : PlayScene.cpp                                                                        //
// @ brief	 : �Q�[���V�[���̃\�[�X�t�@�C��                                                         //
// @ date	 : 2017/05/02                                                                           //
// @ author  : Madoka Nakajima                                                                      //
// @ note	 :                                                                                      //
// @ version : ver.3.00                                                                             //
// ------------------------------------------------------------------------------------------------ // 
/* �w�b�_�t�@�C���̃C���N���[�h */
#include <SpriteBatch.h>
// �搶�̃t���[�����[�N
#include "../../ImaseLib/Direct3D.h"
#include "../../ImaseLib/DirectXTK.h"
// ����w�b�_�t�@�C��
#include "PlayScene.h"
#include "ResultScene.h"

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
void PlayScene::Initialize(int width, int height)
{
	// �X�v���C�g�o�b�`�̐���
	pSprite = make_shared<SpriteBatch>(g_pImmediateContext.Get());
	// �J�����̐���
	pCamera = make_shared<Camera>();
	// �V�[���J�ڗp�ϐ��̏������ifalse�ɂ��邱�ƂőJ�ڂ��Ȃ��j
	mSceneFlag = false;
	// �w�i���C���[�̐���
	mBackGround = make_unique<PlayBackGroundLayer>();
	// �w�i���C���[�̏�����
	mBackGround->Initialize(this);
	// �Q�[�����C���[�̐���
	mGame = make_unique<PlayGameLayer>();
	// �Q�[�����C���[�̏�����
	mGame->Initialize(this,width, height);
	// HUD���C���[�̐���
	mHUD = make_unique<PlayHUDLayer>();
	// HUD���C���[�̏�����
	mHUD->Initialize(this);
	mResultFlag = false;
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: �X�V                                                                                 //
// @ param	: �Ȃ�                                                                                 //
// @ return : �Ȃ��@                                                                               //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void PlayScene::Update()
{
	// ���_�̐ݒ�
	pCamera->SetEye(Vector3(0.0f, 15.0f, 25.0f));
	pCamera->SetRef(Vector3(0.0f, 0.0f, 0.0f));
	// �w�i���C���[�̍X�V
	mBackGround->Update();
	// �Q�[�����C���[�̍X�V
	mGame->SetPauseFlag(mHUD->GetPauseFlag());
	mGame->SetStartFlag(mHUD->GetStartFlag());
	mGame->Update();
	// HUD���C���[�̍X�V
	mHUD->Update();
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: �`��                                                                                 //
// @ param	: Matrix view...�r���[�s��                                                             //
// @ param	: Matrix proj...�ˉe�s��                                                               //
// @ return : �Ȃ�                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void PlayScene::Render()
{
	// �w�i���C���[�̕`��
	mBackGround->Draw();
	// �Q�[�����C���[�̕`��
	mGame->Draw();
	// �X�v���C�g�o�b�`�̎n�܂�i�����������j
	pSprite->Begin(SpriteSortMode_Deferred, nullptr, nullptr, nullptr, nullptr, [=]
	{
		// �摜�̔���������
		g_pImmediateContext->OMSetBlendState(g_state->NonPremultiplied(), nullptr, 0xFFFFFFFF);
	});
	// �Q�[���Ŏ擾�����J�E���^��ݒ�
	mHUD->SetCount(mGame->GetCount());
	// HUD���C���[�̕`��
	mHUD->Draw();
	// �X�v���C�g�o�b�`�̏I���
	pSprite->End();
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: �I��                                                                                 //
// @ param	: �Ȃ�                                                                                 //
// @ return : �Ȃ�                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void PlayScene::Finalize()
{
	mGame->Finalize();
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: �V�[���J��                                                                           //
// @ param	: �Ȃ�                                                                                 //
// @ return : Scene*...���N���X�̃|�C���^                                                       //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
Scene* PlayScene::Change()
{
	// �Q�[�����C���[����t���O���擾
	mSceneFlag = mGame->GetFlag();
	mResultFlag = mGame->GetResultFlag();
	// �t���O���^�Ȃ�i�t���O���U�łȂ�������j
	if (mSceneFlag != false)
	{
		// ���̃V�[���̃|�C���^��Ԃ�
		auto sceneFlag = new ResultScene();
		sceneFlag->SetResultFlag(mResultFlag);
		return sceneFlag;
	}
	// �����łȂ�������
	else
	{
		// nullptr��Ԃ�
		return nullptr;
	}
}
