// ------------------------------------------------------------------------------------------------ //
// @ file	 : GameLayer.h                                                                          //
// @ brief	 : �Q�[�������̃N���X                                                                   //
// @ date	 : 2017/06/30                                                                           //
// @ author  : Madoka Nakajima                                                                      //
// @ note	 :                                                                                      //
// @ version : ver.3.00                                                                             //
// ------------------------------------------------------------------------------------------------ // 
/* ���d�C���N���[�h�̖h�~ */
#pragma once
/* �w�b�_�t�@�C���̃C���N���[�h */
// �W�����C�u����
#include <simplemath.h>
#include <Effects.h>
#include <memory>
#include <vector>
// ����w�b�_�t�@�C��
#include "Layer.h"

#include "../Object/Bomb.h"
#include "../Object/Character.h"
#include "../Object/Cursor.h"
#include "../Object/Item.h"
#include "../Stage/Attribute.h"
#include "../Stage/Map.h"
#include "../Utility/CSVReader.h"
#include "../Utility/MouseCursor.h"

/* �N���X�錾 */
class PlayGameLayer : public Layer
{
	/* �����o�ϐ� */
	// �G�t�F�N�g�t�@�N�g��
	std::shared_ptr<DirectX::EffectFactory> mEf;
	// DGSL�G�t�F�N�g�t�@�N�g��
	std::shared_ptr<DirectX::DGSLEffectFactory> mDef;

	// �{��
	std::shared_ptr<Bomb> mBomb;
	std::vector<std::shared_ptr<Bomb>> mBombs;
	// ���܂����
	std::shared_ptr<Character> mKuma;
	// �}�E�X�J�[�\��
	std::shared_ptr<Cursor> mCursor;
	// �A�C�e��
	std::shared_ptr<Item> mItem;
	// �}�b�v
	std::shared_ptr<Map> mMap;
	// �}�b�v�`�b�v
	MapChip* mChip[MapChipAttribute::ATTRIBUTE_NUM];

	// �{���̃��f��
	std::shared_ptr<DirectX::Model> mBombModel;
	// �N�b�L�[���̃��f��
	std::shared_ptr<DirectX::Model> mCookieModel;
	// ���̃��f��
	std::shared_ptr<DirectX::Model> mHoleModel;
	// �Ԃ̃��f��
	std::shared_ptr<DirectX::Model> mNetModel;

	// �}�E�X�J�[�\���̍��W
	DirectX::SimpleMath::Vector3 mCursorPos;
	// �}�E�X���C�ƃt�B�[���h�Ƃ̂����蔻��̊֐��̖߂�l
	DirectX::SimpleMath::Vector3 mResult;
	// �J�[�\���̍��W�{���炵�Ă��镪
	int mMapOffset_x;
	int mMapOffset_z;

	// CSV�ǂݍ���
	std::shared_ptr<CSVReader> mCSV;
	// �}�b�v�f�[�^
	std::vector<std::vector<int>> mMapData;
	// �}�b�v�T�C�Y
	int mMapSize_x;
	int mMapSize_z;
	// �}�b�v�`�b�v�̂��炵�Ă镪�i�I�t�Z�b�g�j
	float mOffset_x;
	float mOffset_z;

	// �{���̐����^�C�}�[
	float mWaitTimer;

	// �V�[���ؑ֗p�ϐ�
	bool mSceneFlag;
	
	// �`��摜�ύX�p
	bool mResultFlag;
	// �|�[�Y����
	bool mPauseFlag;
	// �X�^�[�g�t���O
	bool mStartFlag;
	// �J�E���^
	int mCount;
public:
	/* �����o�֐� */
	// ������
	void Initialize(Scene* scene);
	void Initialize(Scene* scene, int width, int height);
	// �X�V
	void Update();
	// �`��
	void Draw();
	// �I��
	void Finalize();
	// �ݒ�
	void SetPauseFlag(bool flag) { mPauseFlag = flag; }
	void SetStartFlag(bool flag) { mStartFlag = flag; }
	// �擾
	bool GetResultFlag() { return mResultFlag; }
	bool GetFlag() { return mSceneFlag; }
	int GetCount() { return mCount; }
};
