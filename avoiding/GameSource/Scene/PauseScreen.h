// ------------------------------------------------------------------------------------------------ //
// @ file	 : PauseScreen.h                                                                        //
// @ brief	 : �|�[�Y��ʂ̃w�b�_�t�@�C��                                                           //
// @ date	 : 2017/07/13                                                                           //
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

/* �N���X�錾 */
class PauseScreen
{
	/* �����o�ϐ� */
	// �X�v���C�g�o�b�`
	std::unique_ptr<DirectX::SpriteBatch> pSpriteBatch;
	// �摜�`��ϐ�
	std::unique_ptr<Texture> mChoco;
public:
	/* �����o�֐� */
	// ����������
	void Initialize();
	// �X�V����
	void Update();
	// �`�揈��
	void Render();
	// �I������
	void Finalize();
};
