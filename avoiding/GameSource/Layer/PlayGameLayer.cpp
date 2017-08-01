// ------------------------------------------------------------------------------------------------ //
// @ file	 : GameLayer.cpp                                                                        //
// @ brief	 : �Q�[�������̃N���X                                                                   //
// @ date	 : 2017/06/30                                                                           //
// @ author  : Madoka Nakajima                                                                      //
// @ note	 :                                                                                      //
// @ version : ver.3.00                                                                             //
// ------------------------------------------------------------------------------------------------ // 
/* �w�b�_�t�@�C���̃C���N���[�h */
// �搶�̃t���[�����[�N
#include "../../ImaseLib/Direct3D.h"
#include "../../ImaseLib/DirectXTK.h"
// ����w�b�_�t�@�C��
#include "PlayGameLayer.h"

/* ���O��� */
using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

/* �����o�֐��̒�` */
// ----------------------------------------------------------------------------------------------- //
// @ brief	: ������                                                                               //
// @ param	: int width...�N���C�A���g�̈�̕�                                                     //
// @ param	: int height...�N���C�A���g�̈�̍���                                                  //
// @ return : �Ȃ�                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void PlayGameLayer::Initialize(Scene* scene)
{
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: ������                                                                               //
// @ param	: int width...�N���C�A���g�̈�̕�                                                     //
// @ param	: int height...�N���C�A���g�̈�̍���                                                  //
// @ return : �Ȃ�                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void PlayGameLayer::Initialize(Scene* scene, int width, int height)
{
	// �V�[���̎擾
	pScene = scene;
	// �G�t�F�N�g�t�@�N�g���̏�����
	mEf = make_shared<EffectFactory>(g_pd3dDevice.Get());
	// �t�@�C���p�X���w��
	mEf->SetDirectory(L"Resources");
	// DGSL�G�t�F�N�g�t�@�N�g���̏�����
	mDef = make_shared<DGSLEffectFactory>(g_pd3dDevice.Get());
	// �t�@�C���p�X�̎w��
	mDef->SetDirectory(L"Resources");

	// CSV�ǂݍ��ݕϐ��̐���
	mCSV = make_shared<CSVReader>();
	// CSV�ǂݍ���
	mCSV->ReadCSV(L"Resources\\mapdata3.csv");
	// �ǂݍ��񂾃f�[�^�̎擾
	mMapData = mCSV->GetData();
	// �}�b�v�T�C�Y���擾
	mMapSize_x = mMapData[0].size();
	mMapSize_z = mMapData.size() - 1;
	// �}�b�v�̃I�t�Z�b�g���Z�o
	mOffset_x = mMapSize_x / 2.0f;
	mOffset_z = mMapSize_z / 2.0f;

	// �{���̃��f���̓ǂݍ���
	mBombModel = Model::CreateFromCMO(g_pd3dDevice.Get(), L"Resources\\dogbomb1.cmo", *mDef);
	// �N�b�L�[���̃��f���̓ǂݍ���
	mCookieModel = Model::CreateFromCMO(g_pd3dDevice.Get(), L"Resources\\cookie.cmo", *mDef);
	// ���̃��f���̓ǂݍ���
	mHoleModel = Model::CreateFromCMO(g_pd3dDevice.Get(), L"Resources\\hole.cmo", *mDef);
	// �Ԃ̃��f���̓ǂݍ���
	mNetModel = Model::CreateFromCMO(g_pd3dDevice.Get(), L"Resources\\net1.cmo", *mDef);

	// �}�b�v�`�b�v�̓o�^
	mChip[MapChipAttribute::HOLE] = new MapChip(HOLE);
	mChip[MapChipAttribute::HOLE]->SetModel(mHoleModel);
	mChip[MapChipAttribute::COOKIE] = new MapChip(COOKIE);
	mChip[MapChipAttribute::COOKIE]->SetModel(mCookieModel);
	mChip[MapChipAttribute::NET] = new MapChip(NET);
	mChip[MapChipAttribute::NET]->SetModel(mNetModel);

	// �}�b�v�̐���
	mMap = make_unique<Map>(mMapSize_x, mMapSize_z);
	for (int i = 0; i < mMapSize_z; i++)
	{
		for (int j = 0; j < mMapSize_x; j++)
		{
			// �}�b�v�̔z�����
			mMap->Set(j, i, mChip[mMapData[i][j]]);
		}
	}

	// �L�����N�^�[�̐���
	mKuma = make_shared<Character>();
	// �L�����N�^�[�̏�����
	mKuma->Initialize();
	// �L�����N�^�[�̃��f���̓ǂݍ���
	mKuma->LoadModel(L"Resources\\kumakyun2.cmo");
	// ���W�������_���Őݒ�
	Vector3 kpos = mMap->GetRandomPos(mMapSize_x, mMapSize_z, mOffset_x, mOffset_z);
	// ���W����z��̗v�f�ԍ����Z�o
	auto kposs = Vector3(0, 0, 0);
	kposs.x = floorf(kpos.x + mOffset_x);
	kposs.z = floorf(kpos.z + mOffset_z);
	// �ړ��\�}�X�ɂȂ�܂�
	while (mMap->GetAttribute(kposs.x, kposs.z) != COOKIE)
	{
		// ���W�������_���Őݒ�
		kpos = mMap->GetRandomPos(mMapSize_x, mMapSize_z, mOffset_x, mOffset_z);
		// ���W����z��̗v�f�ԍ����Z�o
		kposs.x = floorf(kpos.x + mOffset_x);
		kposs.z = floorf(kpos.z + mOffset_z);
	}
	kpos.x = kposs.x + 0.5f - mOffset_x;
	kpos.z = kposs.z + 0.5f - mOffset_z;
	// ���W�������_���Őݒ�
	mKuma->SetPos(kpos);
	// ���x�̐ݒ�
	mKuma->SetVel(Vector3(0, 0, 0));

	// �A�C�e���̐���
	mItem = make_shared<Item>();
	// �A�C�e���̏�����
	mItem->Initialize();
	// �A�C�e���̃��f���̓ǂݍ���
	mItem->LoadModel(L"Resources\\PoPcandy.cmo");
	// ���W�������_���Őݒ�
	Vector3 ipos = mMap->GetRandomPos(mMapSize_x, mMapSize_z, mOffset_x, mOffset_z);
	// ���W����z��̗v�f�ԍ����Z�o
	auto iposs = Vector3(0, 0, 0);
	iposs.x = floorf(ipos.x + mOffset_x);
	iposs.z = floorf(ipos.z + mOffset_z);
	// �ړ��\�}�X�ɂȂ�܂�
	while (mMap->GetAttribute(iposs.x, iposs.z) != COOKIE)
	{
		// ���W�������_���Őݒ�
		ipos = mMap->GetRandomPos(mMapSize_x, mMapSize_z, mOffset_x, mOffset_z);
		// ���W����z��̗v�f�ԍ����Z�o
		iposs.x = floorf(ipos.x + mOffset_x);
		iposs.z = floorf(ipos.z + mOffset_z);
	}
	ipos.x = iposs.x + 0.5f - mOffset_x;
	ipos.z = iposs.z + 0.5f - mOffset_z;
	// �����W����������
	ipos.y = 1;
	// ���W�̐ݒ�
	mItem->SetPos(ipos);
	// �g�嗦������������
	mItem->SetScale(0.2f);

	// �}�E�X�J�[�\���̐���
	mCursor = make_shared<Cursor>();
	// �}�E�X�J�[�\���̏�����
	mCursor->Initialize(width, height);
	// �}�E�X�J�[�\���̃��f���̓ǂݍ���
	mCursor->LoadModel(L"Resources\\okiba2.cmo");

	// �^�C�}�[�̃J�E���g���O�ɏ�����
	mWaitTimer = 0;

	// �V�[���ؑ֗p�ϐ��̏�����
	mSceneFlag = false;
	// �`��摜�ύX�p�ϐ��̏�����
	mResultFlag = false;
	// �|�[�Y�ł��邩
	mPauseFlag = false;
	// �X�^�[�g�J�E���g���ł��邩
	mStartFlag = true;

	// �J�E���^�̏�����
	mCount = 0;
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: �X�V                                                                                 //
// @ param	: �Ȃ�                                                                                 //
// @ return : �Ȃ�                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void PlayGameLayer::Update()
{
	int w = 0;

	// �}�b�v�`�b�v�̒��S
	float cx = 0;
	float cz = 0;
	// �I�u�W�F�N�g�̒��S
	Vector3 oc = Vector3(0, 0, 0);

	// t = 0�Fnear,t = 1�Ffar
	float t = -1;
	// ���@�_���^�C�~���O
	auto timing = 0;
	// �X�^�[�g�J�E���g���łȂ��Ȃ�
	if (!mStartFlag)
	{
		// �|�[�Y���łȂ��Ȃ�
		if (!mPauseFlag)
		{
			// ���@�_���^�C�}�[���J�E���g
			// �^�C�}�[���J�E���g�A�b�v������
			mWaitTimer++;
			// ���@�_���^�C�~���O�������_����
			timing = rand() % 100 + 1;
			// �^�C�}�[�����l�𒴂�����{���𐶐�
			if (mWaitTimer > 180)
			{
				if (timing % 3 == 0)
				{
					mBomb = make_shared<Bomb>();
					mBomb->Initialize();
					mBomb->SetModel(mBombModel);
					Vector3 pos = mKuma->GetPos();
					pos.y = 50;
					mBomb->SetPos(pos);
					mBombs.push_back(mBomb);
					mWaitTimer = 0;
				}
				else
				{
					mBomb = make_shared<Bomb>();
					mBomb->Initialize();
					mBomb->SetModel(mBombModel);
					Vector3 pos = mMap->GetRandomPos(mMapSize_x, mMapSize_z, mOffset_x, mOffset_z);
					pos.y = 50;
					mBomb->SetPos(pos);
					mBombs.push_back(mBomb);
					mWaitTimer = 0;
				}
			}

			// �����������ׂẴ{�����X�V
			for (int i = 0; i < mBombs.size(); i++)
			{
				mBombs[i]->Update();
			}
		}

		// �{���Ə��̂����蔻��
		for (int i = 0; i < mBombs.size(); i++)
		{
			// ���W����z��̗v�f�ԍ����Z�o
			Vector3 bombPos = Vector3(0, 0, 0);
			bombPos.x = floorf(mBombs[i]->GetPos().x + mOffset_x);
			bombPos.z = floorf(mBombs[i]->GetPos().z + mOffset_z);

			// �{���Ə����ڐG���Ă�����
			if (mBombs[i]->GetPos().y < 0)
			{
				// ���̑������m�F
				switch (mMap->GetAttribute(bombPos.x, bombPos.z))
				{
					// �N�b�L�[���Ȃ�
				case COOKIE:
					// �N�b�L�[�����猊�̏��ɑ��
					mMap->Set(bombPos.x, bombPos.z, mChip[HOLE]);
					break;
					// �l�b�g�Ȃ�
				case NET:
					// �{��������
					mBombs.pop_back();
					break;
					// ����ȊO�Ȃ�
				default:
					// �������Ȃ�
					break;
				}
			}
		}

		// �L�����N�^�[�̈ړ�
		mKuma->Move();
		// �������擾
		mCount = mKuma->GetCount();

		// �L�����N�^�[�̍��W
		Vector3 chpos = Vector3(0, 0, 0);
		chpos.x = floorf(mKuma->GetPos().x + mOffset_x);
		chpos.z = floorf(mKuma->GetPos().z + mOffset_z);

		// �L�����N�^�[�̂��鏰�̑������m�F
		switch (mMap->GetAttribute(chpos.x, chpos.z))
		{
			// �����Ȃ�
		case HOLE:
			w++;
			while (w < 600)
			{
				// ��������
				mKuma->Fall();
				w++;
			}
			if (mKuma->GetPos().y <= -25.0f)
			{
				// �Q�[�����I������
				mSceneFlag = true;
			}
			break;
			// �l�b�g�Ȃ�
		case NET:
			// �Q�[�����I������
			mSceneFlag = true;
			break;
			// ����ȊO�Ȃ�
		default:
			// �������Ȃ�
			break;
		}

		// �{���ƃL�����N�^�[�̂����蔻��
		for (int i = 0; i < mBombs.size(); i++)
		{
			// �{���ƃv���C���[�̂����蔻��
			if (mBombs[i]->GetPos().x < mKuma->GetPos().x + 0.5f && mBombs[i]->GetPos().x + 0.5f > mKuma->GetPos().x &&
				mBombs[i]->GetPos().z < mKuma->GetPos().z + 0.5f && mBombs[i]->GetPos().z + 0.5f > mKuma->GetPos().z &&
				mBombs[i]->GetPos().y < 0)
			{
				mSceneFlag = true;

			}
		}

		// �A�C�e���ƃL�����N�^�[�̂����蔻��
		if (mItem->GetPos().x < mKuma->GetPos().x + 0.5f && mItem->GetPos().x + 0.5f > mKuma->GetPos().x &&
			mItem->GetPos().z < mKuma->GetPos().z + 0.5f && mItem->GetPos().z + 0.5f > mKuma->GetPos().z)
		{
			// �Q�[�����I������
			mSceneFlag = true;
			// �Q�[���N���A
			mResultFlag = true;
		}


		// �I�u�W�F�N�g�̒��S���Z�o
		oc = Vector3((1.0f / 2.0f), (1.0f / 2.0f), (1.0f / 2.0f));
		// �J�[�\���̍X�V
		mCursor->GetCursor()->Update();
		// �}�E�X���C�ƃt�B�[���h�̂����蔻��iP�D�P�V�T�j
		mCursor->GetCursor()->IntersectSegmentPlane
		(mCursor->GetCursor()->GetNear(), mCursor->GetCursor()->GetFar(), Vector3(0, 0, 0), Vector3(1, 0, 0), Vector3(0, 0, 1), &t, &mResult);
		// �J�[�\���̍��W�̍X�V
		mCursorPos = mResult;
		// �v�Z�������̂�floorf�Ŋۂ߂�
		mMapOffset_x = floorf(mCursorPos.x + mOffset_x);
		mMapOffset_z = floorf(mCursorPos.z + mOffset_z);
		// �}�b�v�`�b�v�̒��S���v�Z
		cx = 1.0f / 2.0f;
		cz = 1.0f / 2.0f;
		// �ۂ߂����̂��炸�炵�Ă��镪�������i+0.5f...�}�b�v�`�b�v�̒��S�j
		mResult.x = static_cast<float>(mMapOffset_x) + cx - mOffset_x;
		mResult.z = static_cast<float>(mMapOffset_z) + cz - mOffset_z;
		// ���W��ݒ�
		Vector3 cpos = mResult;
		// �����W��������������
		cpos.y += 0.01f;
		// �J�[�\�����W�̐ݒ�
		mCursor->SetPos(cpos);

		// �}�E�X���E�N���b�N������
		if (g_mouseTracker->rightButton)
		{
			// �}�E�X���W���z��͈͓̔��ɂ�������
			if (mMapOffset_x >= 0 && mMapOffset_x < mMapSize_x &&
				mMapOffset_z >= 0 && mMapOffset_z < mMapSize_z)
			{
				// �t�B�[���h�̑�����ς���
				mMap->Set(mMapOffset_x, mMapOffset_z, mChip[NET]);
			}
		}
	}

#pragma region Debug
	// F1�L�[�������ꂽ��
	if (g_key.F2)
	{
		// �V�[����J�ڂ���
		mSceneFlag = true;
	}

	// Escape�L�[����������
	if (g_key.Escape)
	{
		// �E�C���h�E�����
		PostQuitMessage(0);
	}
#pragma endregion �f�o�b�O�p�@�\
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: �`��                                                                                 //
// @ param	: �Ȃ�                                                                                 //
// @ return : �Ȃ�                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void PlayGameLayer::Draw()
{
	Matrix view = pScene->GetCamera()->CreateViewMatrix();
	Matrix proj = pScene->GetCamera()->CreateProjectionMatrix();

	// �}�b�v�̕`��
	mMap->Draw(view, proj);
	// �}�E�X�J�[�\���̍��W�v�Z
	mCursor->GetCursor()->Calc(view, proj);
	mCursor->Calc();
	// �}�E�X�J�[�\���̕`��
	mCursor->Draw(view, proj);
	// �{���̕`��
	for (int i = 0; i< mBombs.size(); i++)
	{
		mBombs[i]->Draw(view, proj);
	}
	// �L�����N�^�[�̕`��
	mKuma->Draw(view, proj);
	// �A�C�e���̕`��
	mItem->Draw(view, proj);
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: �I��                                                                                 //
// @ param	: �Ȃ�                                                                                 //
// @ return : �Ȃ�                                                                                 //
// @ note	:                                                                                      //
// ----------------------------------------------------------------------------------------------- // 
void PlayGameLayer::Finalize()
{
	// �}�b�v�`�b�v�̔j��
	delete mChip[MapChipAttribute::COOKIE];
	delete mChip[MapChipAttribute::HOLE];
	delete mChip[MapChipAttribute::NET];
}
