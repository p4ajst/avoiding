// ------------------------------------------------------------------------------------------------ //
// @ file	 : PauseScreen.cpp                                                                      //
// @ brief	 : �|�[�Y��ʂ̃\�[�X�t�@�C��                                                           //
// @ date	 : 2017/07/13                                                                           //
// @ author  : Madoka Nakajima                                                                      //
// @ note	 :                                                                                      //
// @ version : ver.3.00                                                                             //
// ------------------------------------------------------------------------------------------------ // 
/* �w�b�_�t�@�C���̃C���N���[�h */
// �搶�̃t���[�����[�N
#include "../../ImaseLib/Direct3D.h"
#include "../../ImaseLib/DirectXTK.h"
// ����w�b�_�t�@�C��
#include "PauseScreen.h"

/* ���O��� */
using namespace std;
using namespace DirectX;

/* �����o�֐��̒�` */
// ----------------------------------------------------------------------------------------------- //
// @ brief	: ������                                                                               //
// @ param	: �Ȃ�                                                                                 //
// @ return : �Ȃ�                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void PauseScreen::Initialize()
{
	pSpriteBatch = make_unique<SpriteBatch>(g_pImmediateContext.Get());
	mChoco = make_unique<Texture>(L"Resources\\DecoWhiteChocolate.png");
}


// ----------------------------------------------------------------------------------------------- //
// @ brief	: �X�V                                                                                 //
// @ param	: �Ȃ�                                                                                 //
// @ return : �Ȃ��@                                                                               //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void PauseScreen::Update()
{
}


// ----------------------------------------------------------------------------------------------- //
// @ brief	: �`��                                                                                 //
// @ param	: �Ȃ�                                                                                 //
// @ return : �Ȃ�                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void PauseScreen::Render()
{
	RECT rect{ 32,105,1247,855 };
	pSpriteBatch->Begin(SpriteSortMode_Deferred, nullptr, nullptr, nullptr, nullptr, [=]
	{
		// �摜�̔���������
		g_pImmediateContext->OMSetBlendState(g_state->NonPremultiplied(), nullptr, 0xFFFFFFFF);
	});
	pSpriteBatch->Draw(mChoco->m_pTexture, rect, Colors::White);
	// �X�v���C�g�o�b�`�̏I���
	pSpriteBatch->End();
}


// ----------------------------------------------------------------------------------------------- //
// @ brief	: �I��                                                                                 //
// @ param	: �Ȃ�                                                                                 //
// @ return : �Ȃ�                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void PauseScreen::Finalize()
{
}
