// ------------------------------------------------------------------------------------------------ //
// @ file	 : MapChip.h                                                                            //
// @ brief	 : �}�b�v�`�b�v�Ɋւ���N���X                                                           //
// @ date	 : 2017/06/25                                                                           //
// @ author  : Madoka Nakajima                                                                      //
// @ note	 :                                                                                      //
// @ version : ver.3.00                                                                             //
// ------------------------------------------------------------------------------------------------ // 
/* ���d�C���N���[�h�̖h�~ */
#pragma once

/* �w�b�_�t�@�C���̃C���N���[�h */
// ���f�����g����
#include <Model.h>

/* �N���X�錾 */
class MapChip
{
	/* �����o�ϐ� */
	// �X�e�[�W�̑���
	int mAttribute;
	// ���f��
	std::shared_ptr<DirectX::Model> mModel;
public:
	/* �����o�֐� */
	// �R���X�g���N�^
	MapChip();
	// �����t���R���X�g���N�^
	MapChip(int attribute);
	// �f�X�g���N�^
	~MapChip();
	// �����̐ݒ�
	void SetAttribute(int attribute) { mAttribute = attribute; }
	// ���f���̐ݒ�
	void SetModel(std::shared_ptr<DirectX::Model> model) { mModel = model; }
	// �������擾
	int GetAttribute() { return mAttribute; }
	// ���f���̎擾
	std::shared_ptr<DirectX::Model> GetModel() { return mModel; }
};
