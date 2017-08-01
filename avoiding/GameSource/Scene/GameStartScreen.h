// ------------------------------------------------------------------------------------------------ //
// @ file	 : GameStartScreen.h                                                                    //
// @ brief	 : �Q�[���J�n�O�̃J�E���g�_�E���Ɋւ���N���X                                           //
// @ date	 : 2017/07/18                                                                           //
// @ author  : Madoka Nakajima                                                                      //
// @ note	 :                                                                                      //
// @ version : ver.3.00                                                                             //
// ------------------------------------------------------------------------------------------------ // 
/* ���d�C���N���[�h�̖h�~ */
#pragma once

/* �w�b�_�t�@�C���̃C���N���[�h */
// �W�����C�u����
#include <memory>
#include <SpriteBatch.h>
// �搶�̃t���[�����[�N
#include "../../ImaseLib/Texture.h"
// ����w�b�_�t�@�C��
#include "../Utility/Common.h"

/* �N���X�錾 */
class GameStartScreen
{
	/* �����o�ϐ� */
	// �J�E���^
	int mStartCounter;
	// �J�n�t���O
	bool mStartFlag;
	// �X�v���C�g�o�b�`
	std::unique_ptr<DirectX::SpriteBatch> pSprites;
	// �摜�`��ϐ�
	std::unique_ptr<Texture> mWhite;
	std::unique_ptr<Texture> mNumber;
public:
	/* �����o�֐� */
	// ������
	void Initialize();
	// �X�V
	void Update();
	// �`��
	void Render();
	// �I��
	void Finalize();
	// �t���O�̎擾
	bool GetFlag() { return mStartFlag; }
};

