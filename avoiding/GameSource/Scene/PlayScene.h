// ------------------------------------------------------------------------------------------------ //
// @ file	 : PlayScene.h                                                                          //
// @ brief	 : �Q�[���V�[���̃w�b�_�t�@�C��                                                         //
// @ date	 : 2017/05/02                                                                           //
// @ author  : Madoka Nakajima                                                                      //
// @ note	 :                                                                                      //
// @ version : ver.3.00                                                                             //
// ------------------------------------------------------------------------------------------------ // 
/* ���d�C���N���[�h�̖h�~ */
#pragma once 
/* �w�b�_�t�@�C���̃C���N���[�h */
// �W�����C�u����
#include <d3d11.h>
#include <simplemath.h>
#include <memory>
// ����w�b�_�t�@�C���i���N���X�̃w�b�_�t�@�C���j
#include "Scene.h"
// ����w�b�_�t�@�C��
#include "../Layer/PlayHUDLayer.h"
#include "../Layer/PlayGameLayer.h"
#include "../Layer/PlayBackGroundLayer.h"

/* �N���X�錾 */
class PlayScene :public Scene
{
	/* �����o�ϐ� */
	// �w�i���C���[
	std::unique_ptr<PlayBackGroundLayer> mBackGround;
	// �Q�[�����C���[
	std::unique_ptr<PlayGameLayer> mGame;
	// HUD���C���[
	std::unique_ptr<PlayHUDLayer> mHUD;
	// �`�攻��t���O
	bool mResultFlag;
public:
	/* �����o�֐� */
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
};
