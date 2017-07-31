// ------------------------------------------------------------------------------------------------ //
// @ file	 : TitleScene.h                                                                         //
// @ brief	 : �^�C�g���V�[���̃w�b�_�t�@�C��                                                       //
// @ date	 : 2017/05/02                                                                           //
// @ author  : Madoka Nakajima                                                                      //
// @ note	 :                                                                                      //
// @ version : ver.3.00                                                                             //
// ------------------------------------------------------------------------------------------------ // 
/* ���d�C���N���[�h�̖h�~ */
#pragma once 
/* �w�b�_�t�@�C���̃C���N���[�h */
#include <memory>
#include <Effects.h>
// �搶�̃t���[�����[�N
#include "../../ImaseLib/Texture.h"
// ����w�b�_�t�@�C���i���N���X�̃w�b�_�t�@�C���j
#include "Scene.h"
#include "../Layer/TitleBackGroundLayer.h"
#include "../Layer/TitleGameLayer.h"
#include "../Layer/TitleHUDLayer.h"

/* �N���X�錾 */
class TitleScene :public Scene
{
	/* �����o�ϐ� */
	// �w�i���C���[
	std::unique_ptr<TitleBackGroundLayer> mBackGround;
	// �Q�[�����C���[
	std::unique_ptr<TitleGameLayer> mGame;
	// HUD���C���[
	std::unique_ptr<TitleHUDLayer> mHUD;

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
};
