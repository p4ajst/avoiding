// �Q�l�T�C�g�Fhttp://miffysora.wikidot.com/ja:fileread

#include <fstream>
#include <iostream>
#include <cassert>

#include "BinaryLoader.h"

using namespace std;

BinaryLoader::BinaryLoader()
{
}


BinaryLoader::~BinaryLoader()
{
}

bool BinaryLoader::Load(const char* filename)
{
	// ���͂̃t�@�C���X�g���[���̕ϐ�
	ifstream ifs;
	// �f�[�^���o�C�i���œǂݍ���
	ifs = ifstream(filename, ios::in | ios::binary);
	if (ifs)
	{
		// �o�C�i���f�[�^�̒���
		size_t size = 0;
		// �t�@�C���ʒu���I�[�܂ňړ�
		ifs.seekg(0, ifs.end);
		// �t�@�C���̏I�[�̈ʒu��ۑ�
		size = ifs.tellg();
		// �t�@�C���̏I�[�̈ʒu��ۑ�
		ifs.seekg(0, ifs.beg);
		// �z��̃��T�C�Y
		mData.resize(size);
		// �o�C�i���t�@�C���̓ǂݍ���
		ifs.read(mData.data(), mData.size());
	}
	else
	{
		return false;
	}
}

