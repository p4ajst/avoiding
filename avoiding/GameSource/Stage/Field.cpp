// ------------------------------------------------------------------------------------------------ //
// @ file	 : Field.cpp                                                                            //
// @ brief	 : �t�B�[���h�N���X                                                                     //
// @ date	 : 2017/10/23                                                                           //
// @ author  : Madoka Nakajima                                                                      //
// @ note	 :                                                                                      //
// @ version : ver.3.00                                                                             //
// ------------------------------------------------------------------------------------------------ // 
/* �w�b�_�t�@�C���̃C���N���[�h */
// �搶�̃��C�u����
#include "../../ImaseLib/Direct3D.h"
// ����w�b�_�t�@�C��
#include "Field.h"

/* ���O��� */
using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

/* �����o�֐��̒�` */
// ----------------------------------------------------------------------------------------------- //
// @ brief	: �R���X�g���N�^                                                                       //
// @ param	: �Ȃ�                                                                                 //
// @ return : �Ȃ�                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
Field::Field()
{
}


// ----------------------------------------------------------------------------------------------- //
// @ brief	: �f�X�g���N�^                                                                         //
// @ param	: �Ȃ�                                                                                 //
// @ return : �Ȃ�                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
Field::~Field()
{
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: ������                                                                               //
// @ param	: wchar_t * mapfile...�ǂݍ��ނb�r�u�f�[�^�̃t�@�C����                                 //
// @ return : �Ȃ�                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void Field::Initialize(wchar_t * mapfile)
{
	// CSV�ǂݍ��ݕϐ��̐���
	mCSV = make_shared<CSVReader>();
	// CSV�ǂݍ���
	mCSV->ReadCSV(mapfile);
	// �ǂݍ��񂾃f�[�^�̎擾
	mMapData = mCSV->GetData();
	// �}�b�v�T�C�Y���擾
	mMapSize_x = mMapData[0].size();
	mMapSize_z = mMapData.size();
	// �}�b�v�̃I�t�Z�b�g���Z�o
	mMapOffset_x = mMapSize_x / 2.0f;
	mMapOffset_z = mMapSize_z / 2.0f;


	// �N�b�L�[���̃��f���̓ǂݍ���
	mCookieModel = Model::CreateFromCMO(g_pd3dDevice.Get(), L"Resources\\cookie.cmo", *mDef);
	// ���̃��f���̓ǂݍ���
	mHoleModel = Model::CreateFromCMO(g_pd3dDevice.Get(), L"Resources\\hole.cmo", *mDef);
	// �Ԃ̃��f���̓ǂݍ���
	mNetModel = Model::CreateFromCMO(g_pd3dDevice.Get(), L"Resources\\net1.cmo", *mDef);

	// �}�b�v�`�b�v�̓o�^
	RegisterMapChip(MapChipAttribute::COOKIE, mCookieModel);
	RegisterMapChip(MapChipAttribute::HOLE, mHoleModel);
	RegisterMapChip(MapChipAttribute::NET, mNetModel);

	// �}�b�v����
	CreateMap();
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: �X�V                                                                                 //
// @ param	: �Ȃ�                                                                                 //
// @ return : �Ȃ�                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void Field::Update()
{
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: �`��                                                                                 //
// @ param	: Matrix view...�r���[�s��                                                             //
// @ param	: Matrix proj...�v���W�F�N�V�����s��                                                   //
// @ return : �Ȃ�                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void Field::Draw(Matrix view, Matrix proj)
{
	mMap->Draw(view,proj);
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: �R���X�g���N�^                                                                       //
// @ param	: �Ȃ�                                                                                 //
// @ return : �Ȃ�                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void Field::Finalize()
{
	// �}�b�v�`�b�v�̔j��
	delete mChip[MapChipAttribute::COOKIE];
	delete mChip[MapChipAttribute::HOLE];
	delete mChip[MapChipAttribute::NET];
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: �}�b�v�`�b�v�̓o�^                                                                      //
// @ param	: �Ȃ�                                                                                 //
// @ return : �Ȃ�                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void Field::RegisterMapChip(MapChipAttribute attr, shared_ptr<DirectX::Model> model)
{
	mChip[attr] = new MapChip(attr);
	mChip[attr]->SetModel(model);
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: �R���X�g���N�^                                                                       //
// @ param	: �Ȃ�                                                                                 //
// @ return : �Ȃ�                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void Field::CreateMap()
{
	// �}�b�v�̐���
	mMap = make_shared<Map>(mMapSize_x, mMapSize_z);
	for (int i = 0; i < mMapSize_z; i++)
	{
		for (int j = 0; j < mMapSize_x; j++)
		{
			// �}�b�v�̔z�����
			mMap->Set(j, i, mChip[mMapData[i][j]]);
		}
	}
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: �R���X�g���N�^                                                                       //
// @ param	: �Ȃ�                                                                                 //
// @ return : �Ȃ�                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void Field::ChangeAttribute(int x, int z, MapChipAttribute attr)
{
	// �t�B�[���h�̑�����ς���
	mMap->Set(x, z, mChip[attr]);
}

