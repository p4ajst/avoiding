// ------------------------------------------------------------------------------------------------ //
// @ file	 : GameStartScreen.cpp                                                                  //
// @ brief	 : �Q�[���J�n�O�̃J�E���g�_�E���Ɋւ���N���X                                           //
// @ date	 : 2017/07/18                                                                           //
// @ author  : Madoka Nakajima                                                                      //
// @ note	 :                                                                                      //
// @ version : ver.3.00                                                                             //
// ------------------------------------------------------------------------------------------------ // 
/* ���d�C���N���[�h�̖h�~ */
/* �w�b�_�t�@�C���̃C���N���[�h */
// �W�����C�u����
#include <simplemath.h>
// �搶�̃t���[�����[�N
#include "../../ImaseLib/Direct3D.h"
#include "../../ImaseLib/DirectXTK.h"
// ����w�b�_�t�@�C��
#include "GameStartScreen.h"

/* ���O��� */
using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

/* �����o�֐��̒�` */
// ----------------------------------------------------------------------------------------------- //
// @ brief	: ����������                                                                           //
// @ param	: �Ȃ�                                                                                 //
// @ return : �Ȃ�                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void GameStartScreen::Initialize()
{
	// �J�E���^�̏�����
	mStartCounter = 3;
	// �t���O�̏�����
	mStartFlag = false;
	// �X�v���C�g�o�b�`�̏�����
	pSprites = make_unique<SpriteBatch>(g_pImmediateContext.Get());
	// �摜�̏�����
	mWhite = make_unique<Texture>(L"Resources\\screen.png");
	mNumber = make_unique<Texture>(L"Resources\\number.png");
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: �X�V����                                                                             //
// @ param	: �Ȃ�                                                                                 //
// @ return : �Ȃ�                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void GameStartScreen::Update()
{
	// �t���O���U�ł���Ȃ�
	if (!mStartFlag)
	{
		// �J�E���^��i�߂�
		mStartCounter--;
		// �J�E���^���O��菬�����Ȃ�����
		if (mStartCounter < 0)
		{
			// �t���O��^�ɂ���
			mStartFlag = true;
		}
	}
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: �`�揈��                                                                             //
// @ param	: �Ȃ�                                                                                 //
// @ return : �Ȃ�                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void GameStartScreen::Render()
{
	// �摜�̕`��͈�
	RECT rect = { 0,0,1280,960 };
	auto x = mStartCounter * TextureSize;
	auto w = x + TextureSize;
	RECT crect = { x, 0, w, TextureSize};

	pSprites->Begin(SpriteSortMode_Deferred, nullptr, nullptr, nullptr, nullptr, [=]
	{
		// �摜�̔���������
		g_pImmediateContext->OMSetBlendState(g_state->NonPremultiplied(), nullptr, 0xFFFFFFFF);
	});
	pSprites->Draw(mWhite->m_pTexture, rect, Colors::White);
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
	pSprites->Draw(mNumber->m_pTexture, Vector2(640.0f,480.0f),&crect,Colors::White,0.0f,Vector2(32.0f,32.0f),Vector2(1.0f, 1.0f));
	// �X�v���C�g�o�b�`�̏I���
	pSprites->End();

	// 
	// 
	// 
	// 
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: �I������                                                                             //
// @ param	: �Ȃ�                                                                                 //
// @ return : �Ȃ�                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void GameStartScreen::Finalize()
{
	// 
	// 
	// 
	// 
	// 
}
