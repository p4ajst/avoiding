// ------------------------------------------------------------------------------------------------ //
// @ file	 : Game.h                                                                               //
// @ brief	 : �Q�[���S�̂��Ǘ�����N���X                                                           //
// @ date	 : 2017/06/25                                                                           //
// @ author  : Madoka Nakajima                                                                      //
// @ note	 :                                                                                      //
// @ version : ver.3.00                                                                             //
// ------------------------------------------------------------------------------------------------ // 
/* ���d�C���N���[�h�̖h�~ */
#pragma once
/* �w�b�_�t�@�C���̃C���N���[�h */
// �W�����C�u����
#include <simplemath.h>
// ����w�b�_�t�@�C��
#include "Scene\Scene.h"
#include "Scene\TitleScene.h"
#include "Scene\PlayScene.h"
#include "Scene\ResultScene.h"

/* �N���X�錾 */
class Game
{
	/* �����o�ϐ� */
private:
	// �V�[���N���X
	Scene* mScene;
	// �N���C�A���g�̈�̑傫��
	int mClientSizeW;
	int mClientSizeH;

	/* �����o�֐� */
public:
	// ������
	void Initialize(int width, int height);
	// �X�V
	void Update();
	// �`��
	void Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);
	// �I��
	void Finalize();
};
