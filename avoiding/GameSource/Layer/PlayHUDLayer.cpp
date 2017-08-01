// ------------------------------------------------------------------------------------------------ //
// @ file	 : HUDLayer.cpp                                                                         //
// @ brief	 : �w�b�h�A�b�v�f�B�X�v���C�����̃N���X                                                 //
// @ date	 : 2017/06/30                                                                           //
// @ author  : Madoka Nakajima                                                                      //
// @ note	 :                                                                                      //
// @ version : ver.3.00                                                                             //
// ------------------------------------------------------------------------------------------------ // 
/* �w�b�_�t�@�C���̃C���N���[�h */
// �搶�̃t���[�����[�N
#include "../../ImaseLib/DirectXTK.h"
// ����w�b�_�t�@�C��
#include "PlayHUDLayer.h"
#include "../Utility/Common.h"

/* ���O��� */
using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

/* �����o�֐��̒�` */
// ----------------------------------------------------------------------------------------------- //
// @ brief	: ������                                                                               //
// @ param	: Scene* scene...�V�[���̃|�C���^                                                      //
// @ return : �Ȃ�                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void PlayHUDLayer::Initialize(Scene* scene)
{
	// ���݂̃V�[������
	pScene = scene;
	// �����̃e�N�X�`���̐���
	mNum = make_unique<Texture>(L"Resources\\number.png");
	// �r�X�P�b�g�̃e�N�X�`���̐���
	mBiscuitBefore = make_unique<Texture>(L"Resources\\Biscuit_before.png");
	// �r�X�P�b�g�̃e�N�X�`���̐���
	mBiscuitAfter = make_unique<Texture>(L"Resources\\Biscuit_after.png");
	// �|�[�Y��ʂ̐���
	mPause = make_unique<PauseScreen>();
	// �|�[�Y��ʂ�nullptr�łȂ����
	if (mPause != nullptr)
	{
		// �|�[�Y��ʂ̏�����
		mPause->Initialize();
	}
	// �X�^�[�g�X�N���[���̐���
	mStart = make_unique<GameStartScreen>();
	// �X�^�[�g�X�N���[����nullptr�łȂ����
	if (mStart != nullptr)
	{
		// �X�^�[�g�X�N���[���̏�����
		mStart->Initialize();
	}
	// �r�X�P�b�g�̕`��͈͂̐ݒ�
	mBisrect.left = 1211;
	mBisrect.top = 40;
	mBisrect.right = 1275;
	mBisrect.bottom = 104;
	// �|�[�Y���Ă��邩
	mPauseFlag = false;
	// �X�^�[�g�J�E���g���ł��邩
	mStartFlag = false;
	// �r�X�P�b�g�̕`��͈͓��Ƀ}�E�X�J�[�\�������邩
	mpFrag = false;
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: �X�V                                                                                 //
// @ param	: �Ȃ�                                                                                 //
// @ return : �Ȃ�                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void PlayHUDLayer::Update()
{
	// �X�^�[�g�X�N���[���̍X�V
	mStart->Update();
	// �r�X�P�b�g�͈͓̔��ɃJ�[�\���������
	if (g_mouse.x >= mBisrect.left && g_mouse.x <= mBisrect.right &&
		g_mouse.y >= mBisrect.top && g_mouse.y  <= mBisrect.bottom)
	{
		// �t���O��؂�ւ���
		mpFrag = true;
		// ���N���b�N���ꂽ��
		auto bottom = g_mouseTracker->GetLastState();
		if (g_mouseTracker->leftButton == Mouse::ButtonStateTracker::RELEASED)
		{
			if (!mPauseFlag)
			{
				// �t���O��؂�ւ���
				mPauseFlag = true;
			}
			else
			{
				// �t���O��؂�ւ���
				mPauseFlag = false;
			}
		}
	}
	// �����łȂ����
	else
	{
		// �t���O��؂�ւ��Ȃ�
		mpFrag = false;
	}
	// �|�[�Y��ʂ̍X�V
	mPause->Update();
}


// ----------------------------------------------------------------------------------------------- //
// @ brief	: �`��                                                                                 //
// @ param	: �Ȃ�                                                                                 //
// @ return : �Ȃ�                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void PlayHUDLayer::Draw()
{
	// �r�X�P�b�g�̕`��͈͓��Ƀ}�E�X�J�[�\�����Ȃ����
	if (!mpFrag)
	{
		// �r�X�P�b�g�̉摜��`��
		pScene->GetSprite()->Draw(mBiscuitBefore->m_pTexture, mBisrect, Colors::White);
	}
	// �����łȂ����
	else
	{
		// �r�X�P�b�g�̉摜��`��
		pScene->GetSprite()->Draw(mBiscuitAfter->m_pTexture, mBisrect, Colors::White);
	}
	// �|�[�Y���ł����
	if (mPauseFlag)
	{
		// �|�[�Y��ʂ�`��
		mPause->Render();
	}
	// �X�^�[�g�J�E���g���ł����
	if (mStartFlag)
	{
		// �X�^�[�g�X�N���[���̕`��
		mStart->Render();
	}
	// ������`��
	DrawNum(pScene->GetSprite().get(), mNum->m_pTexture, mCount, 160.0f, 32.0f);
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: �I��                                                                                 //
// @ param	: �Ȃ�                                                                                 //
// @ return : �Ȃ�                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void PlayHUDLayer::Finalize()
{
}
