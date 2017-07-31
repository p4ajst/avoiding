// ------------------------------------------------------------------------------------------------ //
// @ file	 : BackGroundLayer.h                                                                    //
// @ brief	 : �w�i�����̃N���X                                                                     //
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
class PlayBackGroundLayer :public Layer
{
	/* �����o�֐� */
public:
	// ������
	void Initialize(Scene* scene);
	// �X�V
	void Update();
	// �`��
	void Draw();
	// �I��
	void Finalize();
};
