// ------------------------------------------------------------------------------------------------ //
// @ file	 : Cursor.h                                                                             //
// @ brief	 : �J�[�\���Ɋւ���N���X                                                           //
// @ date	 : 2017/06/25                                                                           //
// @ author  : Madoka Nakajima                                                                      //
// @ note	 :                                                                                      //
// @ version : ver.3.00                                                                             //
// ------------------------------------------------------------------------------------------------ // 
/* ���d�C���N���[�h�̖h�~ */
#pragma once
/* �w�b�_�t�@�C���̃C���N���[�h */
// ����w�b�_�t�@�C��
#include "Actor.h"
#include "../Utility/MouseCursor.h"

/* �N���X�錾 */
class Cursor :public Actor
{
	/* �����o�ϐ� */
	// �}�E�X����
	std::shared_ptr<MouseCursor> mMouseCursor;
	/* �����o�֐� */
public:
	// �R���X�g���N�^
	Cursor() = default;
	// �f�X�g���N�^
	~Cursor() = default;
	// ������
	void Initialize(int width, int height);
	// �X�V
	void Update();
	void Update(float ox, float oz);
	// �`��
	void Draw(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);
	// �擾
	std::shared_ptr<MouseCursor> GetCursor() { return mMouseCursor; }
};