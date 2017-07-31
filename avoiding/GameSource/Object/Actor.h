// ------------------------------------------------------------------------------------------------ //
// @ file	 : Actor.h                                                                              //
// @ brief	 : �o�ꕨ�̊��N���X                                                                   //
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
// �c�f�r�k�G�t�F�N�g�t�@�N�g�����g����
#include <Effects.h>
// �X�}�[�g�|�C���^���g����
#include <memory>
// ���f�����g����
#include <Model.h>

/* �N���X�錾 */
class Actor
{
	/* �����o�ϐ� */
protected:
	// DGSL�G�t�F�N�g�t�@�N�g��
	std::shared_ptr<DirectX::DGSLEffectFactory>  mDef;
	// ���f��
	std::shared_ptr<DirectX::Model> mModel;
	// ���W
	DirectX::SimpleMath::Vector3 mPosition;
	// �p�x
	float mAngle;
	// �g�嗦
	float mScalingFactor;
	// ���[�J�����[���h�s��
	DirectX::SimpleMath::Matrix mLocalWorld;

	/* �����o�֐� */
public:
	// �R���X�g���N�^
	Actor() = default;
	// ���z�f�X�g���N�^
	virtual ~Actor() = default;
	// ������
	void Initialize();
	// �X�V
	void Update();
	// �`��
	void Draw(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);
	// �I��
	void Finalize();
	// ���f���̓ǂݍ���
	void LoadModel(wchar_t* filename);
	// �s��v�Z
	void Calc();
	// �����o�ϐ��̐ݒ�
	void SetModel(std::shared_ptr<DirectX::Model> model) { mModel = model; }
	void SetPos(DirectX::SimpleMath::Vector3 pos) { mPosition = pos; }
	void SetAngle(float angle) { mAngle = angle; }
	void SetScale(float scale) { mScalingFactor = scale; }
	// �����o�ϐ��̎擾
	std::shared_ptr<DirectX::Model> GetModel() { return mModel; }
	DirectX::SimpleMath::Vector3 GetPos() { return mPosition; }
	float GetAngle() { return mAngle; }
	float GetScale() { return mScalingFactor; }
};
