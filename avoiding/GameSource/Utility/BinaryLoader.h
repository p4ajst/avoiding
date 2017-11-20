#pragma once
#include <fstream>
#include <vector>

class BinaryLoader
{
	// �o�C�i���œǂݍ��񂾃f�[�^���i�[����ϐ�
	std::vector<char> mData;
public:
	// �R���X�g���N�^
	BinaryLoader();
	// �f�X�g���N�^
	~BinaryLoader();
	// �o�C�i���f�[�^�̓ǂݍ���
	bool Load(const char* filename);
	// �o�C�i���f�[�^�̎擾
	std::vector<char> GetData() { return mData; }
};