// ------------------------------------------------------------------------------------------------ //
// @ file	 : HUDLayer.h                                                                           //
// @ brief	 : �w�b�h�A�b�v�f�B�X�v���C�����̃N���X                                                 //
// @ date	 : 2017/06/30                                                                           //
// @ author  : Madoka Nakajima                                                                      //
// @ note	 :                                                                                      //
// @ version : ver.3.00                                                                             //
// ------------------------------------------------------------------------------------------------ // 
/* ���d�C���N���[�h�̖h�~ */
#pragma once

/* �w�b�_�t�@�C���̃C���N���[�h */
#include <memory>
// �搶�̃t���[�����[�N
#include "../../ImaseLib/Texture.h"
// ����w�b�_�t�@�C��
#include "Layer.h"
#include "../Scene/PauseScreen.h"
#include "../Scene/GameStartScreen.h"

/* �萔��` */
static const int NumTextureSize = 64;

/* �N���X�錾 */
class PlayHUDLayer :public Layer
{
private:
	// �e�N�X�`��
	std::shared_ptr<Texture> pTexture;
	// �摜�`��
	std::unique_ptr<Texture> mNum;
	std::unique_ptr<Texture> mBiscuitBefore;
	std::unique_ptr<Texture> mBiscuitAfter;
	std::unique_ptr<PauseScreen> mPause;
	std::unique_ptr<GameStartScreen> mStart;
	// �`��͈�
	RECT mBisrect;
	// �|�[�Y�����H
	bool mPauseFlag;
	// �X�^�[�g�J�E���^�[�����H
	bool mStartFlag;
	// �J�[�\�����摜�̕`��͈͓��ɂ��邩�H
	bool mpFrag;
	// �J�E���^
	int mCount;

	/* �����o�֐� */
public:
	// ������
	void Initialize(Scene* scene);
	// �X�V
	void Update();
	// �`��
	void Draw();
	void DrawNum();
	// �I��
	void Finalize();
	// �J�E���^�̃Z�b�g
	void SetCount(int cnt) { mCount = cnt; }
	// �t���O�̎擾
	bool GetPauseFlag() { return mPauseFlag; }
	bool GetStartFlag() { return mStartFlag; }
};
