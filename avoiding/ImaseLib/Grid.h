//--------------------------------------------------------------------------------------
// File: Grid.h
//
// �O���b�h��`�悷��N���X
//
// Date: 2015.5.13
// Author: Hideyasu Imase
//--------------------------------------------------------------------------------------
#pragma once

#include <Windows.h>
#include <Effects.h>
#include <PrimitiveBatch.h>
#include <VertexTypes.h>
#include <SimpleMath.h>

//--------------------------------------------------------------------------------------
//�@�O���b�h�`��N���X
//--------------------------------------------------------------------------------------
class Grid
{
	// �G�t�F�N�g
	std::unique_ptr<DirectX::BasicEffect> m_basicEffect;

	// �v���~�e�B�u�o�b�`
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>> m_primitiveBatch;

	// �C���v�b�g���C�A�E�g
	ID3D11InputLayout* m_pInputLayout;

	// �O���b�h�`��G���A�̕��ƍ����Ɗi�q�̃T�C�Y
	int m_w, m_h, m_size;

	// �I�t�Z�b�g
	int m_offx, m_offy;

public:
	// �R���X�g���N�^
	Grid(int w, int h, int size);

	// �f�X�g���N�^
	~Grid();

	// �`��
	void Render();

	// �O���b�h�̃T�C�Y��ݒ肷��֐�
	void SetGripInfo(int w, int h, int size)
	{
		m_w = w;
		m_h = h;
		m_size = size;
	}

	// �I�t�Z�b�g�̐ݒ�
	void SetOffset(int offx, int offy)
	{
		m_offx = offx;
		m_offy = offy;
	}
};

//--------------------------------------------------------------------------------------
//�@�O���b�h��̏��`��N���X
//--------------------------------------------------------------------------------------
class GridFloor
{
	// �G�t�F�N�g
	std::unique_ptr<DirectX::BasicEffect> m_basicEffect;

	// �v���~�e�B�u�o�b�`
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>> m_primitiveBatch;

	// �C���v�b�g���C�A�E�g
	ID3D11InputLayout* m_pInputLayout;

	// ���̈�ӂ̃T�C�Y
	float m_size;

	// ������
	int m_divs;

public:
	// �R���X�g���N�^�i���̈�ӂ̃T�C�Y�A��ӂ̕������j
	GridFloor(float size, int divs);

	// �f�X�g���N�^
	~GridFloor();

	// �`��i�r���[�s��A�ˉe�s��j
	void Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj, DirectX::GXMVECTOR color = DirectX::Colors::Gray);
};



