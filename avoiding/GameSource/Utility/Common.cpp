// ------------------------------------------------------------------------------------------------ //
// @ file	 : Common.h                                                                             //
// @ brief	 : �����̃N���X�ɂ܂�����ϐ����܂Ƃ߂ĊO���Q�Ƃ���w�b�_�t�@�C��                       //
// @ date	 : 2017/06/30                                                                           //
// @ author  : Madoka Nakajima                                                                      //
// @ note	 :                                                                                      //
// @ version : ver.3.00                                                                             //
// ------------------------------------------------------------------------------------------------ // 
/* �w�b�_�t�@�C���̃C���N���[�h */
// �W�����C�u����
#include <simplemath.h>
// ����w�b�_�t�@�C��
#include "Common.h"

/* ���O��� */
using namespace DirectX;
using namespace DirectX::SimpleMath;

/* �֐��̒�` */
// ----------------------------------------------------------------------------------------------- //
// @ brief	: �����`��                                                                             //
// @ param	: �Ȃ�                                                                                 //
// @ return : �Ȃ�                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 

//void DrawNum()
//{
//
//	// ��Ɨp
//	auto num = mCount;
//	// ������
//	auto sn = 0;
//	// ���W
//	auto x = 160.0f;
//	auto y = 32.0f;
//	// �摜�̒��S�_
//	auto ox = NumTextureSize / 2.0f;
//	auto oy = NumTextureSize / 2.0f;
//	// �摜�̕`��͈�
//	RECT crect = { 0, 0, NumTextureSize, NumTextureSize };
//
//
//	if (num == 0)
//	{
//		/*
//		ID3D11ShaderResourceView* texture...�e�N�X�`���̃|�C���^
//		FXMVECTOR position...��ʂ̕`��̊�_�i�ǂ��ɕ`�悷�邩�j
//		RECT const* sourceRectangle...���̃e�N�X�`���̂ǂ̕�����`�悷�邩
//		FXMVECTOR color...�F
//		float rotation...��]�p
//		XMFLOAT2 const& origin...�`�悷��摜�̊�_
//		GXMVECTOR scale...�g�嗦
//		SpriteEffects effects
//		float layerDepth
//		*/
//		pScene->GetSprite()->Draw(mNum->m_pTexture, Vector2(x, y), &crect, Colors::White, 0.0f, Vector2(ox, oy), Vector2(1.0f, 1.0f));
//	}
//	else
//	{
//		while (num)
//		{
//
//			int l = (num % 10) * NumTextureSize;
//			int t = 0;
//			int r = l + NumTextureSize;
//			int b = NumTextureSize;
//
//			int px = x - sn * NumTextureSize;
//
//			// �摜�̕`��͈�
//			crect = { l,t,r,b };
//			/*
//			ID3D11ShaderResourceView* texture...�e�N�X�`���̃|�C���^
//			FXMVECTOR position...��ʂ̕`��̊�_�i�ǂ��ɕ`�悷�邩�j
//			RECT const* sourceRectangle...���̃e�N�X�`���̂ǂ̕�����`�悷�邩
//			FXMVECTOR color...�F
//			float rotation...��]�p
//			XMFLOAT2 const& origin...�`�悷��摜�̊�_
//			GXMVECTOR scale...�g�嗦
//			SpriteEffects effects
//			float layerDepth
//			*/
//			pScene->GetSprite()->Draw(mNum->m_pTexture, Vector2(px, y), &crect, Colors::White, 0.0f, Vector2(ox, oy), Vector2(1.0f, 1.0f));
//			num /= 10;
//			sn++;
//		}
//	}
//}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: �����`��                                                                             //
// @ param	: SpriteBatch* sprite...�摜�̕`�悷���                                               //
// @ param	: ID3D11ShaderResourceView* resource...�e�N�X�`���̃f�[�^                              //
// @ param	: int n...�`�悵��������                                                               //
// @ param	: float x...�`�悵�����ʒu�̂����W                                                     //
// @ param	: float y...�`�悵�����ʒu�̂����W                                                     //
// @ return : �Ȃ�                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void DrawNum(SpriteBatch* sprite, ID3D11ShaderResourceView* resource, int n, float x, float y)
{

	// ��Ɨp
	auto num = n;
	// ������
	auto sn = 0;
	// ���W
	auto px = x;
	auto py = y;

	// �摜�̒��S�_
	auto ox = TextureSize / 2.0f;
	auto oy = TextureSize / 2.0f;
	// �摜�̕`��͈�
	RECT crect = { 0, 0, TextureSize, TextureSize };


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
		sprite->Draw(resource, Vector2(x, y), &crect, Colors::White, 0.0f, Vector2(ox, oy), Vector2(1.0f, 1.0f));
	}
	else
	{
		while (num)
		{

			int l = (num % 10) * TextureSize;
			int t = 0;
			int r = l + TextureSize;
			int b = TextureSize;

			int px = x - sn * TextureSize;

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
			sprite->Draw(resource, Vector2(px, y), &crect, Colors::White, 0.0f, Vector2(ox, oy), Vector2(1.0f, 1.0f));
			num /= 10;
			sn++;
		}
	}
}
