// ------------------------------------------------------------------------------------------------ //
// @ file	 : ResultGameLayer.h                                                                    //
// @ brief	 : �Q�[�������̃N���X                                                                   //
// @ date	 : 2017/06/30                                                                           //
// @ author  : Madoka Nakajima                                                                      //
// @ note	 :                                                                                      //
// @ version : ver.3.00                                                                             //
// ------------------------------------------------------------------------------------------------ // 
/* ���d�C���N���[�h�̖h�~ */
#pragma once
/* �w�b�_�t�@�C���̃C���N���[�h */
#include "Layer.h"
/* �N���X�錾 */
class ResultGameLayer:public Layer
{
	/* �����o�ϐ� */
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
};
