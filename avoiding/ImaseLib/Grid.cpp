//--------------------------------------------------------------------------------------
// File: Grid.cpp
//
// �O���b�h��`�悷��N���X
//
// Date: 2015.9.2
// Author: Hideyasu Imase
//--------------------------------------------------------------------------------------
#include <algorithm>
#include <SimpleMath.h>
#include <DirectXColors.h>
#include "Grid.h"
#include "Direct3D.h"
#include "DirectXTK.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//--------------------------------------------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------------------------------------------
Grid::Grid(int w, int h, int size) : m_pInputLayout(nullptr), m_w(w), m_h(h), m_size(size), m_offx(0), m_offy(0)
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
	g_pd3dDevice.Get()->CreateInputLayout( VertexPositionColor::InputElements,
										   VertexPositionColor::InputElementCount,
										   shaderByteCode, byteCodeLength,
										   &m_pInputLayout );
}

//--------------------------------------------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------------------------------------------
Grid::~Grid()
{
	// ���̓��C�A�E�g���������
	if (m_pInputLayout) m_pInputLayout->Release();
}

//--------------------------------------------------------------------------------------
// �`��
//--------------------------------------------------------------------------------------
void Grid::Render()
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

	// �c����`��
	for (int i = 0; i < m_w / m_size + 1; i++)
	{
		VertexPositionColor v1(Vector3(static_cast<float>(m_size * i) + m_offx, 0.0f, 0.0f), Colors::DarkGreen);
		VertexPositionColor v2(Vector3(static_cast<float>(m_size * i) + m_offx, static_cast<float>(m_h), 0.0f), Colors::DarkGreen);
		m_primitiveBatch->DrawLine(v1, v2);
	}
	// ������`��
	for (int i = 0; i < m_h / m_size + 1; i++)
	{
		VertexPositionColor v1(Vector3(0.0f, static_cast<float>(m_size * i) + m_offy, 0.0f), Colors::DarkGreen);
		VertexPositionColor v2(Vector3(static_cast<float>(m_w), static_cast<float>(m_size * i) + m_offy, 0.0f), Colors::DarkGreen);
		m_primitiveBatch->DrawLine(v1, v2);
	}

	m_primitiveBatch->End();
}

//--------------------------------------------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------------------------------------------
GridFloor::GridFloor(float size, int divs) : m_pInputLayout(nullptr), m_size(size), m_divs(divs)
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
GridFloor::~GridFloor()
{
	// ���̓��C�A�E�g���������
	if (m_pInputLayout) m_pInputLayout->Release();
}

//--------------------------------------------------------------------------------------
// �`��
//--------------------------------------------------------------------------------------
void GridFloor::Render(Matrix view, Matrix proj, GXMVECTOR color)
{
	Matrix world = Matrix::Identity;

	g_pImmediateContext->OMSetDepthStencilState(g_state->DepthDefault(), 0);

	m_basicEffect->SetWorld(world);
	m_basicEffect->SetView(view);
	m_basicEffect->SetProjection(proj);

	m_basicEffect->Apply(g_pImmediateContext.Get());
	g_pImmediateContext.Get()->IASetInputLayout(m_pInputLayout);

	m_primitiveBatch->Begin();

	const XMVECTORF32 xAxis = { m_size, 0.f, 0.f };
	const XMVECTORF32 yAxis = { 0.f, 0.f, m_size };

	size_t divs = std::max<size_t>(1, m_divs);
	FXMVECTOR origin = g_XMZero;
	for (size_t i = 0; i <= divs; ++i)
	{
		float fPercent = float(i) / float(divs);
		fPercent = (fPercent * 1.0f) - 0.5f;
		XMVECTOR vScale = XMVectorScale(xAxis, fPercent);
		vScale = XMVectorAdd(vScale, origin);

		VertexPositionColor v1(XMVectorSubtract(vScale, yAxis * 0.5f), color);
		VertexPositionColor v2(XMVectorAdd(vScale, yAxis * 0.5f), color);
		m_primitiveBatch->DrawLine(v1, v2);
	}

	for (size_t i = 0; i <= divs; i++)
	{
		FLOAT fPercent = float(i) / float(divs);
		fPercent = (fPercent * 1.0f) - 0.5f;
		XMVECTOR vScale = XMVectorScale(yAxis, fPercent);
		vScale = XMVectorAdd(vScale, origin);

		VertexPositionColor v1(XMVectorSubtract(vScale, xAxis * 0.5f), color);
		VertexPositionColor v2(XMVectorAdd(vScale, xAxis * 0.5f), color);
		m_primitiveBatch->DrawLine(v1, v2);
	}

	m_primitiveBatch->End();
}

