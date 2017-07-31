// ------------------------------------------------------------------------------------------------ //
// @ file	 : ResultScene.cpp                                                                      //
// @ brief	 : ���U���g�V�[���̃\�[�X�t�@�C��                                                       //
// @ date	 : 2017/05/02                                                                           //
// @ author  : Madoka Nakajima                                                                      //
// @ note	 :                                                                                      //
// @ version : ver.3.00                                                                             //
// ------------------------------------------------------------------------------------------------ // 

/* �w�b�_�t�@�C���̃C���N���[�h */
// �W�����C�u����
#include <simplemath.h>
// �搶�̃t���[�����[�N
#include "../../ImaseLib/Direct3D.h"
#include "../../ImaseLib/DirectXTK.h"
// ����w�b�_�t�@�C��
#include "ResultScene.h"
#include "TitleScene.h"
#include "../Utility/Common.h"


/* ���O��� */
using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

/* �����o�֐��̒�` */
// ----------------------------------------------------------------------------------------------- //
// @ brief	: ����������                                                                           //
// @ param	: int width,int height...��ʃT�C�Y                                                    //
// @ return : �Ȃ�                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void ResultScene::Initialize(int width, int height)
{
	// �X�v���C�g�o�b�`�̐���
	pSprite = make_shared<SpriteBatch>(g_pImmediateContext.Get());
	// �J�����̐���
	pCamera = make_shared<Camera>();

	// �w�i���C���[�̐���
	mBackGround = make_unique<ResultBackGroundLayer>();
	// �w�i���C���[�̏�����
	mBackGround->Initialize(this);
	// �Q�[�����C���[�̐���
	mGame = make_unique<ResultGameLayer>();
	// �Q�[�����C���[�̏�����
	mGame->Initialize(this);
	// HUD���C���[�̐���
	mHUD = make_unique<ResultHUDLayer>();
	// HUD���C���[�̏�����
	mHUD->Initialize(this);
	// �V�[���ؑ֗p�ϐ��̏�����
	mSceneFlag = false;
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: �X�V����                                                                             //
// @ param	: �Ȃ�                                                                                 //
// @ return : �Ȃ�                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void ResultScene::Update()
{
	// �w�i���C���[�̍X�V
	mBackGround->Update();
	// �Q�[�����C���[�̍X�V
	mGame->Update();
	// HUD���C���[�̍X�V
	mHUD->Update();

#pragma region Debug
	// F1�L�[�������ꂽ��
	if (g_key.F3)
	{
		// �V�[����J�ڂ���
		mSceneFlag = true;
	}

	// Escape�L�[����������
	if (g_key.Escape)
	{
		// �E�C���h�E�����
		PostQuitMessage(0);
	}
#pragma endregion �f�o�b�O�p�@�\
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: �`�揈��                                                                             //
// @ param	: Matrix view,Matrix proj...�r���[�s��ƃv���W�F�N�V�����s��                           //
// @ return : �Ȃ�                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void ResultScene::Render()
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
	mHUD->SetResultFlag(mResultFlag);
	// HUD���C���[�̕`��
	mHUD->Draw();
	// �X�v���C�g�o�b�`�̏I���
	pSprite->End();
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: �I������                                                                             //
// @ param	: �Ȃ�                                                                                 //
// @ return : �Ȃ�                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void ResultScene::Finalize()
{
	mGame->Finalize();
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: �V�[���J��                                                                           //
// @ param	: �Ȃ�                                                                                 //
// @ return : Scene*...���N���X�̃|�C���^                                                       //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
Scene* ResultScene::Change()
{
	// �Q�[�����C���[����t���O���擾
	mSceneFlag = mHUD->GetFlag();
	// �t���O���^�Ȃ�i�t���O���U�łȂ�������j
	if (mSceneFlag != false)
	{
		// ���̃V�[���̃|�C���^��Ԃ�
		return new TitleScene();
	}
	// �����łȂ�������
	else
	{
		// nullptr��Ԃ�
		return nullptr;
	}
}
