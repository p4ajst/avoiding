// ------------------------------------------------------------------------------------------------ //
// @ file	 : TitleBackGroundLayer.h                                                               //
// @ brief	 : �w�i���C���[                                                                         //
// @ date	 : 2017/07/10                                                                           //
// @ author  : Madoka Nakajima                                                                      //
// @ note	 :                                                                                      //
// @ version : ver.3.00                                                                             //
// ------------------------------------------------------------------------------------------------ // 
/* ���d�C���N���[�h�̖h�~ */
#pragma once
/* �w�b�_�t�@�C���̃C���N���[�h */
#include "Layer.h"
/* �N���X�錾 */
class TitleBackGroundLayer :public Layer
{
	/* �����o�ϐ� */
	bool mSceneFlag;
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
