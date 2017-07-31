// ------------------------------------------------------------------------------------------------ //
// @ file	 : ResultScene.h                                                                        //
// @ brief	 : ���U���g�V�[���̃w�b�_�t�@�C��                                                       //
// @ date	 : 2017/05/02                                                                           //
// @ author  : Madoka Nakajima                                                                      //
// @ note	 :                                                                                      //
// @ version : ver.3.00                                                                             //
// ------------------------------------------------------------------------------------------------ // 
/* ���d�C���N���[�h�̖h�~ */
#pragma once 
/* �w�b�_�t�@�C���̃C���N���[�h */
// ����w�b�_�t�@�C���i���N���X�̃w�b�_�t�@�C���j
#include "Scene.h"
// ����w�b�_�t�@�C��
#include "../Layer/ResultBackGroundLayer.h"
#include "../Layer/ResultGameLayer.h"
#include "../Layer/ResultHUDLayer.h"

/* �N���X�錾 */
class ResultScene :public Scene
{
	/* �����o�ϐ� */
	// �w�i���C���[
	std::unique_ptr<ResultBackGroundLayer> mBackGround;
	// �Q�[�����C���[
	std::unique_ptr<ResultGameLayer> mGame;
	// HUD���C���[
	std::unique_ptr<ResultHUDLayer> mHUD;
	// �`��摜�ύX�p
	bool mResultFlag;

	/* �����o�֐� */
public:
	// ����������
	void Initialize(int width, int height);
	// �X�V����
	void Update();
	// �`�揈��
	void Render();
	// �I������
	void Finalize();
	// �V�[���J��
	Scene* Change();
	// �t���O�̐ݒ�
	void SetResultFlag(bool flag) { mResultFlag = flag; }
};
