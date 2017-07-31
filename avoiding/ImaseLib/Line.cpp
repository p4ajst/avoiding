//--------------------------------------------------------------------------------------
// File: Line.cpp
//
// ���C����`�悷��N���X
//
// Date: 2015.10.18
// Author: Hideyasu Imase
//--------------------------------------------------------------------------------------
#include <SimpleMath.h>
#include <DirectXColors.h>
#include "Line.h"
#include "Direct3D.h"
#include "DirectXTK.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//--------------------------------------------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------------------------------------------
LineBatch::LineBatch(int w, int h, int size) : m_w(w), m_h(h), m_size(size)
{
	// �G�t�F�N�g�I�u�W�F�N�g����
	m_basicEffect.reset(new BasicEffect(g_pd3dDevice.Get()));
	// ���_�J���[(�L��)
	m_basicEffect->SetVertexColorEnabled(true);
	// �v���~�e�B�u�I�u�W�F�N�g����
	m_primitiveBatch.reset(new PrimitiveBatch<VertexPositionColor>(g_pImmediateContext.Get()));
	// �C���v�b�g���C�A�E�g����
	void const* shaderByteCode;
	size_t byteCodeLength;
	m_basicEffect->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);
	g_pd3dDevice.Get()->CreateInputLayout(VertexPositionColor::InputElements,
		VertexPositionColor::InputElementCount,
		shaderByteCode, byteCodeLength,
		&m_pInputLayout);
}

//--------------------------------------------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------------------------------------------
LineBatch::~LineBatch()
{
	// ���̓��C�A�E�g���������
	if (m_pInputLayout) m_pInputLayout->Release();
}

//--------------------------------------------------------------------------------------
// �`��̊J�n
//--------------------------------------------------------------------------------------
void LineBatch::Begin()
{
	Matrix world, view, proj;

	// �Q�c�p�s����쐬���ăG�t�F�N�g�փZ�b�g
	world = Matrix::Identity;
	view = Matrix::Identity;
	proj = Matrix::CreateTranslation(0.5f, 0.5f, 0.0f) * Matrix::CreateOrthographicOffCenter(0.0f, (float)m_w, (float)m_h, 0.0f, 0.0f, 100.0f);

	m_basicEffect->SetWorld(world);
	m_basicEffect->SetView(view);
	m_basicEffect->SetProjection(proj);

	m_basicEffect->Apply(g_pImmediateContext.Get());
	g_pImmediateContext.Get()->IASetInputLayout(m_pInputLayout);

	m_primitiveBatch->Begin();
}

//--------------------------------------------------------------------------------------
// �`��̊J�n
//--------------------------------------------------------------------------------------
void LineBatch::Begin(Matrix view, Matrix proj)
{
	Matrix world;

	world = Matrix::Identity;

	m_basicEffect->SetWorld(world);
	m_basicEffect->SetView(view);
	m_basicEffect->SetProjection(proj);

	m_basicEffect->Apply(g_pImmediateContext.Get());
	g_pImmediateContext.Get()->IASetInputLayout(m_pInputLayout);

	m_primitiveBatch->Begin();
}

//--------------------------------------------------------------------------------------
// �`��̏I��
//--------------------------------------------------------------------------------------
void LineBatch::End()
{
	m_primitiveBatch->End();
}

//--------------------------------------------------------------------------------------
// �`��
//--------------------------------------------------------------------------------------
void LineBatch::Draw(float x1, float y1, float x2, float y2, XMVECTOR color)
{
	Draw(Vector2(x1, y1), Vector2(x2, y2), color);
}

//--------------------------------------------------------------------------------------
// �`��
//--------------------------------------------------------------------------------------
void LineBatch::Draw(Vector2 p1, Vector2 p2, XMVECTOR color)
{
	VertexPositionColor v1(p1, color);
	VertexPositionColor v2(p2, color);
	m_primitiveBatch->DrawLine(v1, v2);
}

//--------------------------------------------------------------------------------------
// �`��
//--------------------------------------------------------------------------------------
void LineBatch::DrawLine(Vector2 p1, XMVECTOR color)
{
	VertexPositionColor v1((Vector2(p1.x * (float)m_size, -p1.y * (float)m_size) + Vector2(m_w / 2.0f, m_h / 2.0f)), color);
	VertexPositionColor v2(Vector2(m_w / 2.0f, m_h / 2.0f), color);
	m_primitiveBatch->DrawLine(v1, v2);
}

//--------------------------------------------------------------------------------------
// �`��
//--------------------------------------------------------------------------------------
void LineBatch::DrawLine(Vector2 p1, Vector2 p2, XMVECTOR color)
{
	VertexPositionColor v1((Vector2(p1.x * (float)m_size, -p1.y * (float)m_size) + Vector2(m_w / 2.0f, m_h / 2.0f)), color);
	VertexPositionColor v2((Vector2(p2.x * (float)m_size, -p2.y * (float)m_size) + Vector2(m_w / 2.0f, m_h / 2.0f)), color);
	m_primitiveBatch->DrawLine(v1, v2);
}

//--------------------------------------------------------------------------------------
// �`��
//--------------------------------------------------------------------------------------
void LineBatch::Draw(Vector3 p, XMVECTOR color)
{
	VertexPositionColor v1(Vector3(0.0f, 0.0f, 0.0f), color);
	VertexPositionColor v2(p, color);
	m_primitiveBatch->DrawLine(v1, v2);
}

//--------------------------------------------------------------------------------------
// �`��
//--------------------------------------------------------------------------------------
void LineBatch::Draw(Vector3 p1, Vector3 p2, XMVECTOR color)
{
	VertexPositionColor v1(p1, color);
	VertexPositionColor v2(p2, color);
	m_primitiveBatch->DrawLine(v1, v2);
}

