// ------------------------------------------------------------------------------------------------ //
// @ file	 : Field.h                                                                              //
// @ brief	 : �t�B�[���h�N���X                                                                   //
// @ date	 : 2017/10/23                                                                           //
// @ author  : Madoka Nakajima                                                                      //
// @ note	 :                                                                                      //
// @ version : ver.3.00                                                                             //
// ------------------------------------------------------------------------------------------------ // 
/* ���d�C���N���[�h�̖h�~ */
#pragma once
/* �w�b�_�t�@�C���̃C���N���[�h */
// �W�����C�u����
#include <Effects.h>
// ����w�b�_�t�@�C��
#include "../Stage/Attribute.h"
#include "../Stage/Map.h"
#include "../Utility/CSVReader.h"

/* �N���X�錾 */
class Field
{
	/* �����o�ϐ� */
	// DGSL�G�t�F�N�g�t�@�N�g��
	std::shared_ptr<DirectX::DGSLEffectFactory> mDef;
	// �}�b�v
	std::shared_ptr<Map> mMap;
	// �}�b�v�`�b�v
	MapChip* mChip[MapChipAttribute::ATTRIBUTE_NUM];
	// ���̃��f��
	std::shared_ptr<DirectX::Model> mCookieModel;
	// ���̃��f��
	std::shared_ptr<DirectX::Model> mHoleModel;
	// �Ԃ̃��f��
	std::shared_ptr<DirectX::Model> mNetModel;
	// CSV�ǂݍ���
	std::shared_ptr<CSVReader> mCSV;
	// �}�b�v�f�[�^
	std::vector<std::vector<int>> mMapData;
	// �}�b�v�T�C�Y
	int mMapSize_x;
	int mMapSize_z;
	// �}�b�v�̂��炵�Ă��镪
	int mMapOffset_x;
	int mMapOffset_z;

	/* �����o�֐� */
public:
	Field();
	~Field();
	// ������
	void Initialize(wchar_t* mapfile);
	// �X�V
	void Update();
	// �`��
	void Draw(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);
	// �I��
	void Finalize();
	// �}�b�v�`�b�v�̓o�^
	void RegisterMapChip(MapChipAttribute attr, std::shared_ptr<DirectX::Model> model);
	// �}�b�v�̐���
	void CreateMap();
	// �t�B�[���h�̑�����ύX
	void ChangeAttribute(int x,int z,MapChipAttribute attr);
	// �擾
	int GetSizeX() { return mMapSize_x; }
	int GetSizeZ() { return mMapSize_z; }
	int GetOffsetX() { return mMapOffset_x; }
	int GetOffsetZ() { return mMapOffset_z; }

};

