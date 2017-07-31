// ------------------------------------------------------------------------------------------------ //
// @ file	 : HUDLayer.cpp                                                                         //
// @ brief	 : �w�b�h�A�b�v�f�B�X�v���C�����̃N���X                                                 //
// @ date	 : 2017/06/30                                                                           //
// @ author  : Madoka Nakajima                                                                      //
// @ note	 :                                                                                      //
// @ version : ver.3.00                                                                             //
// ------------------------------------------------------------------------------------------------ // 
/* �w�b�_�t�@�C���̃C���N���[�h */
#include "../../ImaseLib/DirectXTK.h"
#include "PlayHUDLayer.h"

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
	pScene = scene;
	mNum = make_unique<Texture>(L"Resources\\number.png");
	mBiscuitBefore = make_unique<Texture>(L"Resources\\Biscuit_before.png");
	mBiscuitAfter = make_unique<Texture>(L"Resources\\Biscuit_after.png");
	mPause = make_unique<PauseScreen>();
	if (mPause != nullptr)
	{
		mPause->Initialize();
	}
	mStart = make_unique<GameStartScreen>();
	if (mStart != nullptr)
	{
		mStart->Initialize();
	}
	mBisrect.left = 1211;
	mBisrect.top = 40;
	mBisrect.right = 1275;
	mBisrect.bottom = 104;
	mPauseFlag = false;
	mStartFlag = false;
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
	mPause->Update();
	mStart->Update();
}


// ----------------------------------------------------------------------------------------------- //
// @ brief	: �`��                                                                                 //
// @ param	: �Ȃ�                                                                                 //
// @ return : �Ȃ�                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void PlayHUDLayer::Draw()
{
	if (!mpFrag)
	{
		pScene->GetSprite()->Draw(mBiscuitBefore->m_pTexture, mBisrect, Colors::White);
	}
	else
	{
		pScene->GetSprite()->Draw(mBiscuitAfter->m_pTexture, mBisrect, Colors::White);
	}
	if (mPauseFlag)
	{
		mPause->Render();
	}
	if (mStartFlag)
	{
		mStart->Render();
	}
	DrawNum();
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: �����`��                                                                             //
// @ param	: �Ȃ�                                                                                 //
// @ return : �Ȃ�                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void PlayHUDLayer::DrawNum()
{

	// ��Ɨp
	auto num = mCount;
	// ������
	auto sn = 0;
	// ���W
	auto x = 160.0f;
	auto y = 32.0f;
	// �摜�̒��S�_
	auto ox = NumTextureSize / 2.0f;
	auto oy = NumTextureSize / 2.0f;
	// �摜�̕`��͈�
	RECT crect = { 0, 0, NumTextureSize, NumTextureSize };


	if (num == 0)
	{
		/*
			ID3D11ShaderResourceView* texture...�e�N�X�`���̃|�C���^
			FXMVECTOR position...��ʂ̕`��̊�_�i�ǂ��ɕ`�悷�邩�j
			RECT const* sourceRectangle...���̃e�N�X�`���̂ǂ̕�����`�悷�邩
			FXMVECTOR color...�F
			float rotation...��]�p
			XMFLOAT2 const& origin...�`�悷��摜�̊�_
			GXMVECTOR scale...�g�嗦
			SpriteEffects effects
			float layerDepth
		*/
		pScene->GetSprite()->Draw(mNum->m_pTexture, Vector2(x, y), &crect, Colors::White, 0.0f, Vector2(ox, oy), Vector2(1.0f, 1.0f));
	}
	else
	{
		while (num)
		{

			int l = (num % 10) * NumTextureSize;
			int t = 0;
			int r = l + NumTextureSize;
			int b = NumTextureSize;

			int px = x - sn * NumTextureSize;

			// �摜�̕`��͈�
			crect = { l,t,r,b };
			/*
				ID3D11ShaderResourceView* texture...�e�N�X�`���̃|�C���^
				FXMVECTOR position...��ʂ̕`��̊�_�i�ǂ��ɕ`�悷�邩�j
				RECT const* sourceRectangle...���̃e�N�X�`���̂ǂ̕�����`�悷�邩
				FXMVECTOR color...�F
				float rotation...��]�p
				XMFLOAT2 const& origin...�`�悷��摜�̊�_
				GXMVECTOR scale...�g�嗦
				SpriteEffects effects
				float layerDepth
			*/
			pScene->GetSprite()->Draw(mNum->m_pTexture, Vector2(px, y), &crect, Colors::White, 0.0f, Vector2(ox, oy), Vector2(1.0f, 1.0f));
			num /= 10;
			sn++;
		}
	}
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
