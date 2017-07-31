//--------------------------------------------------------------------------------------
// File: DebugCamera.cpp
//
// �f�o�b�O�p�J�����N���X
//
// Date: 2015.11.23
// Author: Hideyasu Imase
//--------------------------------------------------------------------------------------
#include "DebugCamera.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

const float DebugCamera::DEFAULT_CAMERA_DISTANCE = 5.0f;

//--------------------------------------------------------------------------------------
// �X�V
//--------------------------------------------------------------------------------------
void DebugCamera::Update()
{
	// �}�E�X�̍��{�^���������ꂽ
	if (g_mouseTracker->leftButton == Mouse::ButtonStateTracker::ButtonState::PRESSED)
	{
		// �}�E�X�̍��W���擾
		m_x = g_mouse.x;
		m_y = g_mouse.y;
	}
	else if (g_mouseTracker->leftButton == Mouse::ButtonStateTracker::ButtonState::RELEASED)
	{
		// ���݂̉�]��ۑ�
		m_xAngle = m_xTmp;
		m_yAngle = m_yTmp;
	}
	// �}�E�X�̃{�^����������Ă�����J�������ړ�������
	if (g_mouse.leftButton)
	{
		Motion(g_mouse.x, g_mouse.y);
	}

	// �}�E�X�̃t�H�C�[���l���擾
	m_scrollWheelValue = g_mouse.scrollWheelValue;
	if (m_scrollWheelValue > 0)
	{
		m_scrollWheelValue = 0;
		DirectXTK_ResetScrollWheelValue();
	}

	// �r���[�s����Z�o����
	Matrix rotY = Matrix::CreateRotationY(m_yTmp);
	Matrix rotX = Matrix::CreateRotationX(m_xTmp);

	Matrix rt = rotY * rotX;

	Vector3 eye(0.0f, 2.0f, 5.0f);
	Vector3 target(0.0f, 0.0f, 0.0f);
	Vector3 up(0.0f, 1.0f, 0.0f);

	eye = Vector3::Transform(eye, rt.Invert());
	eye *= (DEFAULT_CAMERA_DISTANCE - m_scrollWheelValue / 100);
	up = Vector3::Transform(up, rt.Invert());

	m_view = Matrix::CreateLookAt(eye, target, up);
}

//--------------------------------------------------------------------------------------
// �s��̐���
//--------------------------------------------------------------------------------------
void DebugCamera::Motion(int x, int y)
{
	// �}�E�X�|�C���^�̈ʒu�̃h���b�O�J�n�ʒu����̕ψ� (���Βl)
	float dx = (x - m_x) * m_sx;
	float dy = (y - m_y) * m_sy;

	if (dx != 0.0f || dy != 0.0f)
	{
		// �x���̉�]
		float yAngle = dx * XM_PI;
		// �w���̉�]
		float xAngle = dy * XM_PI;

		m_xTmp = m_xAngle + xAngle;
		m_yTmp = m_yAngle + yAngle;
	}
}
