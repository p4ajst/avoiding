// ------------------------------------------------------------------------------------------------ //
// @ file	 : CSVReader.h                                                                          //
// @ brief	 : CSV�ǂݍ��݂̂��߂̃N���X                                                            //
// @ date	 : 2017/01/11                                                                           //
// @ author  : Madoka Nakajima                                                                      //
// @ note	 :                                                                                      //
// @ version : ver.3.00                                                                             //
// ------------------------------------------------------------------------------------------------ // 
/* ���d�C���N���[�h�̖h�~ */
#pragma once

/* �w�b�_�t�@�C���̃C���N���[�h */
// ���o��
#include <iostream>
// �t�@�C���ǂݍ���
#include <fstream>
// istringstream���g����
#include <sstream>
// ������
#include <string>
// ���I�z��
#include <vector>

/* �N���X�錾 */
class CSVReader
{
	/* �����o�ϐ� */
	// �f�[�^���i�[����z��
	std::vector<std::vector<int>> mData;
	// �}�b�v�̃T�C�Y
	int mapSize_x;
	int mapSize_z;
	/* �����o�֐� */
	// �R���}�ŋ�؂�ꂽ�l�����o��
	std::vector<int> Split(const std::string& str, char delimiter);
public:
	/* �����o�֐� */
	// �R���X�g���N�^
	CSVReader();
	// �f�X�g���N�^
	~CSVReader();
	// CSV�t�@�C����ǂݍ���
	bool ReadCSV(wchar_t* filename);
	// �ǂݍ��񂾃t�@�C���̒��̃f�[�^���擾
	std::vector<std::vector<int>> GetData() { return mData; }
};

