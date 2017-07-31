// ------------------------------------------------------------------------------------------------ //
// @ file	 : ResultHUDLayer.h                                                                     //
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
class ResultHUDLayer : public Layer
{
	/* �����o�ϐ� */
	// �V�[���J�ڗp�ϐ�
	bool mSceneFlag;
	// �`��摜�ύX�p
	bool mResultFlag;
	// �摜�`��p�ϐ�
	std::unique_ptr<Texture> mBeforeFrog;
	std::unique_ptr<Texture> mAfterFrog;
	std::unique_ptr<Texture> mBeforeDoor;
	std::unique_ptr<Texture> mAfterDoor;
	std::unique_ptr<Texture> mGameClear;
	std::unique_ptr<Texture> mGameOver;
	// ����p�t���O
	bool mfFlag;
	bool mdFlag;
	// �摜�̕`��͈�
	RECT mFrog;
	RECT mDoor;
	RECT mDoorA;

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
	// �t���O�̐ݒ�
	void SetResultFlag(bool flag) { mResultFlag = flag; }
	// �擾
	bool GetFlag() { return mSceneFlag; }
};
