// ------------------------------------------------------------------------------------------------ //
// @ file	 : Scene.h                                                                              //
// @ brief	 : �V�[���̊��N���X                                                                   //
// @ date	 : 2017/05/02                                                                           //
// @ author  : Madoka Nakajima                                                                      //
// @ note	 :                                                                                      //
// @ version : ver.3.00                                                                             //
// ------------------------------------------------------------------------------------------------ // 
/* ���d�C���N���[�h��h�~ */
#pragma once 
/* �w�b�_�t�@�C���̃C���N���[�h */
// �W�����C�u����
#include <simplemath.h>
#include <SpriteBatch.h>
#include <memory>
// ����w�b�_�t�@�C��
#include "../Utility/Camera.h"
/* �N���X�錾 */
class Scene
{
	/* �����o�ϐ� */
protected:
	// �J�ڔ���p�ϐ�
	bool mSceneFlag;
	// �X�v���C�g�o�b�`
	std::shared_ptr<DirectX::SpriteBatch> pSprite;
	// �J����
	std::shared_ptr<Camera> pCamera;
	/* �����o�֐� */
public:
	// �R���X�g���N�^
	Scene() = default;
	// ���z�f�X�g���N�^
	virtual ~Scene() = default;
	// ������
	virtual void Initialize(int width, int height) = 0;
	// �X�V
	virtual void Update() = 0;
	// �`��
	virtual void Render() = 0;
	// �I��
	virtual void Finalize() = 0;
	// �V�[���J��
	virtual Scene* Change() = 0;
	// �X�v���C�g�o�b�`�̎擾
	std::shared_ptr<DirectX::SpriteBatch> GetSprite() { return pSprite; }
	// �J�����̎擾
	std::shared_ptr<Camera>GetCamera() { return pCamera; }
};
