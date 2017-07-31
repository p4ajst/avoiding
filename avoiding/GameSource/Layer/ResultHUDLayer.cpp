// ------------------------------------------------------------------------------------------------ //
// @ file	 : ResultHUDLayer.cpp                                                                   //
// @ brief	 : �w�b�h�A�b�v�f�B�X�v���C�����̃N���X                                                 //
// @ date	 : 2017/07/10                                                                           //
// @ author  : Madoka Nakajima                                                                      //
// @ note	 :                                                                                      //
// @ version : ver.3.00                                                                             //
// ------------------------------------------------------------------------------------------------ // 
// �搶�̃t���[�����[�N
#include "../../ImaseLib/DirectXTK.h"
// ����w�b�_�t�@�C��
#include "ResultHUDLayer.h"

/* ���O��� */
using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

/* �����o�֐��̒�` */
// ----------------------------------------------------------------------------------------------- //
// @ brief	: ����������                                                                           //
// @ param	: Scene* scene...�ǂ̃V�[����                                                          //
// @ return : �Ȃ�                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void ResultHUDLayer::Initialize(Scene* scene)
{
	pScene = scene;

	// �摜�`��p�ϐ�
	mBeforeFrog = make_unique<Texture>(L"Resources\\frog_before.png");
	mAfterFrog = make_unique<Texture>(L"Resources\\frog_After.png");
	mBeforeDoor = make_unique<Texture>(L"Resources\\door_before.png");
	mAfterDoor = make_unique<Texture>(L"Resources\\door_After.png");
	mGameClear = make_unique<Texture>(L"Resources\\GameClear.png");
	mGameOver = make_unique<Texture>(L"Resources\\GameOver.png");

	// ����p�t���O
	mfFlag = false;
	mdFlag = false;
	// �摜�̕`��͈�
	mFrog.left = 200;
	mFrog.top = 600;
	mFrog.right = 456;
	mFrog.bottom = 856;
	mDoor.left = 700;
	mDoor.top = 500;
	mDoor.right = 956;
	mDoor.bottom = 756;
	mDoorA.left = 700;
	mDoorA.top = 500;
	mDoorA.right = 1120;
	mDoorA.bottom = 890;

	// �V�[���ؑ֗p�ϐ��̏�����
	mSceneFlag = false;
	// �`��p�ϐ��̏�����
	mResultFlag = false;
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: �X�V����                                                                             //
// @ param	: �Ȃ�                                                                                 //
// @ return : �Ȃ�                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void ResultHUDLayer::Update()
{
	// �J�G���͈͓̔��ɃJ�[�\���������
	if (g_mouse.x >= mFrog.left && g_mouse.x <= mFrog.right &&
		g_mouse.y >= mFrog.top && g_mouse.y <= mFrog.bottom)
	{
		// �t���O��؂�ւ���
		mfFlag = true;
		// ���N���b�N���ꂽ��
		if (g_mouseTracker->leftButton == Mouse::ButtonStateTracker::RELEASED)
		{
			// �t���O��؂�ւ���
			mSceneFlag = true;
		}
	}
	// �����łȂ����
	else
	{
		// �t���O��؂�ւ��Ȃ�
		mfFlag = false;
	}
	// �h�A�͈͓̔��ɃJ�[�\���������
	if (g_mouse.x >= mDoor.left && g_mouse.x <= mDoor.right &&
		g_mouse.y >= mDoor.top && g_mouse.y <= mDoor.bottom)
	{
		// �t���O��؂�ւ���
		mdFlag = true;
		// ���N���b�N���ꂽ��
		if (g_mouseTracker->leftButton == Mouse::ButtonStateTracker::RELEASED)
		{
			// �E�C���h�E�����
			PostQuitMessage(0);
		}
	}
	// �����łȂ����
	else
	{
		// �t���O��؂�ւ��Ȃ�
		mdFlag = false;
	}
}


// ----------------------------------------------------------------------------------------------- //
// @ brief	: �`�揈��                                                                             //
// @ param	: �Ȃ�                                                                                 //
// @ return : �Ȃ�                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void ResultHUDLayer::Draw()
{
	// �摜�̕`��
	
	// �`��ʒu�il,t,r,b�j;
	RECT rect{ 0,0,1280,480 };

	// ���U���g�t���O���^�ł���Ȃ�
	if (mResultFlag)
	{
		// �Q�[���N���A
		pScene->GetSprite()->Draw(mGameClear->m_pTexture, rect, Colors::White);
	}
	// ���U���g�t���O���U�ł���Ȃ�
	else
	{
		// �Q�[���I�[�o�[
		pScene->GetSprite()->Draw(mGameOver->m_pTexture, rect, Colors::White);
	}

	// �J�G���t���O���U�ł���Ȃ�
	if (!mfFlag)
	{
		pScene->GetSprite()->Draw(mBeforeFrog->m_pTexture, mFrog, Colors::White);
	}
	// �J�G���t���O���^�ł���Ȃ�
	else
	{
		pScene->GetSprite()->Draw(mAfterFrog->m_pTexture, mFrog, Colors::White);
	}
	// �h�A�t���O���U�ł���Ȃ�
	if (!mdFlag)
	{
		pScene->GetSprite()->Draw(mBeforeDoor->m_pTexture, mDoorA, Colors::White);
	}
	// �h�A�t���O�^�ł���Ȃ�
	else
	{
		pScene->GetSprite()->Draw(mAfterDoor->m_pTexture, mDoorA, Colors::White);
	}
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: �I������                                                                             //
// @ param	: �Ȃ�                                                                                 //
// @ return : �Ȃ�                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void ResultHUDLayer::Finalize()
{
}
