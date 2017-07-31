// ------------------------------------------------------------------------------------------------ //
// @ file	 : Map.h                                                                                //
// @ brief	 : �}�b�v�Ɋւ���N���X                                                                 //
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
#include "MapChip.h"

/* �N���X�錾 */
class Map
{
	/* �����o�ϐ� */
	// �}�b�v�`�b�v�̔z��
	MapChip** mMapChip;
	// �}�b�v�̕��ƍ���
	int mWidth;
	int mHeight;
public:
	/* �����o�֐� */
	// �R���X�g���N�^
	Map(int width, int height);
	// �f�X�g���N�^
	~Map();
	// �}�b�v�`�b�v�̓o�^
	void Set(int x, int y, MapChip* chip);
	// �񎟌��z��̓Y��������ꎟ���z��̓Y�����ɂ���
	int ToIndex(int x, int y);
	// �`��
	void Draw(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);
	// �}�b�v�`�b�v�ԍ�����}�E�X�J�[�\���̍��W���擾
	DirectX::SimpleMath::Vector3 GetPos(int x, int z, int ox, int oz);
	// �������擾
	DirectX::SimpleMath::Vector3 GetRandomPos(int x, int z, float ox, float oz);
	// �}�b�v�`�b�v�̑������擾
	int GetAttribute(int x, int z);
};
