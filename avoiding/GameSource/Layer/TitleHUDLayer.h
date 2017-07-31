// ------------------------------------------------------------------------------------------------ //
// @ file	 : TitleHUDLayer.h                                                                      //
// @ brief	 : �w�b�h�A�b�v�f�B�X�v���C�����̃N���X                                                 //
// @ date	 : 2017/07/10                                                                           //
// @ author  : Madoka Nakajima                                                                      //
// @ note	 :                                                                                      //
// @ version : ver.3.00                                                                             //
// ------------------------------------------------------------------------------------------------ // 
/* ���d�C���N���[�h�̖h�~ */
#pragma once
/* �w�b�_�t�@�C���̃C���N���[�h */
// �搶�̃t���[�����[�N
#include "../../ImaseLib/Texture.h"
// ����w�b�_�t�@�C��
#include "Layer.h"


/* �N���X�錾 */
class TitleHUDLayer :public Layer
{
	/* �����o�ϐ� */
	// �V�[���J�ڗp�ϐ�
	bool mSceneFlag;
	// �摜�`��p�ϐ�
	std::unique_ptr<Texture> mGraph;
	std::unique_ptr<Texture> mBeforeStart;
	std::unique_ptr<Texture> mAfterStart;
	std::unique_ptr<Texture> mBeforeEnd;
	std::unique_ptr<Texture> mAfterEnd;
	// ����p�t���O
	bool msFlag;
	bool meFlag;
	// �摜�̕`��͈�
	RECT mStart;
	RECT mEnd;

public:
	/* �����o�֐� */
	// ����������
	void Initialize(Scene* scene);
	// �X�V����
	void Update();
	// �`�揈��
	void Draw();
	// �I������
	void Finalize();
	// �擾
	bool GetFlag() { return mSceneFlag; }
};
