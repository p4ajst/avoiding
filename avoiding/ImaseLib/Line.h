//--------------------------------------------------------------------------------------
// File: Line.h
//
// ���C����`�悷��N���X
//
// Date: 2015.10.18
// Author: Hideyasu Imase
//--------------------------------------------------------------------------------------
#pragma once

#include <Windows.h>
#include <Effects.h>
#include <PrimitiveBatch.h>
#include <VertexTypes.h>
#include <SimpleMath.h>
#include <DirectXColors.h>

// ���C���N���X
class LineBatch
{
	// �G�t�F�N�g
	std::unique_ptr<DirectX::BasicEffect> m_basicEffect;

	// �v���~�e�B�u�o�b�`
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>> m_primitiveBatch;

	// �C���v�b�g���C�A�E�g
	ID3D11InputLayout* m_pInputLayout;

	// ��ʃT�C�Y
	int m_w, m_h;

	// �O���b�h�T�C�Y
	int m_size;

public:
	// �R���X�g���N�^
	LineBatch(int w, int h, int size);

	// �f�X�g���N�^
	~LineBatch();

	// �`��J�n
	void Begin();
	void Begin(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);

	// �`��I��
	void End();

	// �`��
	void Draw(float x1, float y1, float x2, float y2, DirectX::XMVECTOR color = DirectX::Colors::White);

	// �`��
	void Draw(DirectX::SimpleMath::Vector2 p1, DirectX::SimpleMath::Vector2 p2, DirectX::XMVECTOR color = DirectX::Colors::White);

	// �`��
	void DrawLine(DirectX::SimpleMath::Vector2 p1, DirectX::XMVECTOR color = DirectX::Colors::White);

	// �`��
	void DrawLine(DirectX::SimpleMath::Vector2 p1, DirectX::SimpleMath::Vector2 p2, DirectX::XMVECTOR color = DirectX::Colors::White);

	// �`��
	void Draw(DirectX::SimpleMath::Vector3 p, DirectX::XMVECTOR color = DirectX::Colors::White);

	// �`��
	void Draw(DirectX::SimpleMath::Vector3 p1, DirectX::SimpleMath::Vector3 p3, DirectX::XMVECTOR color = DirectX::Colors::White);
};
