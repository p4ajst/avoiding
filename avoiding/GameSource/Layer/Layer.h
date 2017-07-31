// ------------------------------------------------------------------------------------------------ //
// @ file	 : Layer.h                                                                              //
// @ brief	 : ���C���[�̊��N���X                                                                 //
// @ date	 : 2017/06/26                                                                           //
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
#include "../Scene/Scene.h"

/* �N���X�錾 */
class Layer
{
protected:
	/* �����o�֐� */
	Scene* pScene;
public:
	// �R���X�g���N�^
	Layer() = default;
	// ���z�f�X�g���N�^
	virtual ~Layer() = default;
	// ������
	virtual void Initialize(Scene* scene) = 0;
	// �X�V
	virtual void Update() = 0;
	// �`��
	virtual void Draw() = 0;
	// �I��
	virtual void Finalize() = 0;
};
