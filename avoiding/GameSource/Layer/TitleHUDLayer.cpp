// ------------------------------------------------------------------------------------------------ //
// @ file	 : TitleHUDLayer.cpp                                                                    //
// @ brief	 : �w�b�h�A�b�v�f�B�X�v���C�����̃N���X                                                 //
// @ date	 : 2017/07/10                                                                           //
// @ author  : Madoka Nakajima                                                                      //
// @ note	 :                                                                                      //
// @ version : ver.3.00                                                                             //
// ------------------------------------------------------------------------------------------------ // 
/* �w�b�_�t�@�C���̃C���N���[�h */
// �搶�̃t���[�����[�N
#include "../../ImaseLib/DirectXTK.h"
// ����w�b�_�t�@�C��
#include "TitleHUDLayer.h"
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
void TitleHUDLayer::Initialize(Scene * scene)
{
	// �V�[���J�ڗp�ϐ�
	pScene = scene;

	// �摜�`��p�ϐ��̐���
	mGraph = make_unique<Texture>(L"Resources\\Title3.png");
	mBeforeStart = make_unique<Texture>(L"Resources\\Start_Before.png");
	mAfterStart = make_unique<Texture>(L"Resources\\Start_After.png");
	mBeforeEnd = make_unique<Texture>(L"Resources\\End_Before.png");
	mAfterEnd = make_unique<Texture>(L"Resources\\End_After.png");
	// ����p�t���O
	msFlag = false;
	meFlag = false;

	// �摜�̕`��͈�
	mStart.left   = 425;
	mStart.top    = 400;
	mStart.right  = 825;
	mStart.bottom = 610;

	mEnd.left     = 425;
	mEnd.top      = 650;
	mEnd.right    = 825;
	mEnd.bottom   = 860;

	// �V�[���ؑ֗p�ϐ��̏�����
	mSceneFlag = false;
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: �X�V                                                                                 //
// @ param	: �Ȃ�                                                                                 //
// @ return : �Ȃ�                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void TitleHUDLayer::Update()
{
	// Start�͈̔͂ɃJ�[�\������������
	if (g_mouse.x >= mStart.left && g_mouse.x <= mStart.right &&
		g_mouse.y >= mStart.top && g_mouse.y <= mStart.bottom)
	{
		msFlag = true;
		// ���N���b�N���ꂽ��
		if (g_mouseTracker->leftButton == Mouse::ButtonStateTracker::RELEASED)
		{
			// �t���O��؂�ւ���
			mSceneFlag = true;
		}
	}
	else
	{
		msFlag = false;
	}
	if (g_mouse.x >= mEnd.left && g_mouse.x <= mEnd.right &&
		g_mouse.y >= mEnd.top && g_mouse.y <= mEnd.bottom)
	{
		meFlag = true;
		// ���N���b�N���ꂽ��
		if (g_mouseTracker->leftButton == Mouse::ButtonStateTracker::RELEASED)
		{
			// �E�C���h�E�����
			PostQuitMessage(0);
		}
	}
	else
	{
		meFlag = false;
	}
}


// ----------------------------------------------------------------------------------------------- //
// @ brief	: �`��                                                                                 //
// @ param	: �Ȃ�                                                                                 //
// @ return : �Ȃ�                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void TitleHUDLayer::Draw()
{
	// �摜�̕`��͈�
	RECT rect{ 0,0,1280,480 };
	// �摜�̕`��
	pScene->GetSprite()->Draw(mGraph->m_pTexture, rect, DirectX::Colors::White);
	// �X�^�[�g�t���O���U�ł���Ȃ�
	if (!msFlag)
	{
		pScene->GetSprite()->Draw(mBeforeStart->m_pTexture, mStart, DirectX::Colors::White);
	}
	// �X�^�[�g�t���O���^�ł���Ȃ�
	else
	{
		pScene->GetSprite()->Draw(mAfterStart->m_pTexture, mStart, DirectX::Colors::White);
	}
	// �G���h�t���O���U�ł���Ȃ�
	if (!meFlag)
	{
		pScene->GetSprite()->Draw(mBeforeEnd->m_pTexture, mEnd, DirectX::Colors::White);
	}
	// �G���h�t���O���^�ł���Ȃ�
	else
	{
		pScene->GetSprite()->Draw(mAfterEnd->m_pTexture, mEnd, DirectX::Colors::White);
	}
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: �I��                                                                                 //
// @ param	: �Ȃ�                                                                                 //
// @ return : �Ȃ�                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void TitleHUDLayer::Finalize()
{
}
