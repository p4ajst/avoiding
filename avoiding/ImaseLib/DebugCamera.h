//--------------------------------------------------------------------------------------
// File: DebugCamera.h
//
// �f�o�b�O�p�J�����N���X
//
// Date: 2015.11.23
// Author: Hideyasu Imase
//--------------------------------------------------------------------------------------
#pragma once

#include "DirectXTK.h"
#include <SimpleMath.h>

// �f�o�b�O�p�J�����N���X
class DebugCamera
{
	// �J�����̋���
	static const float DEFAULT_CAMERA_DISTANCE;

	// ����]
	float m_yAngle, m_yTmp;

	// �c��]
	float m_xAngle, m_xTmp;

	// �h���b�O���ꂽ���W
	int m_x, m_y;

	float m_sx, m_sy;

	// �������ꂽ�r���[�s��
	DirectX::SimpleMath::Matrix m_view;

	// �X�N���[���t�H�C�[���l
	int m_scrollWheelValue;

private:

	void Motion(int x, int y);

public:
	// �R���X�g���N�^
	DebugCamera(int w, int h)
		: m_yAngle(0.0f), m_yTmp(0.0f), m_xAngle(0.0f), m_xTmp(0.0f), m_x(0), m_y(0), m_scrollWheelValue(0)
	{
		// ��ʃT�C�Y�ɑ΂��鑊�ΓI�ȃX�P�[���ɒ���
		m_sx = 1.0f / (float)w;
		m_sy = 1.0f / (float)h;
		m_view = DirectX::SimpleMath::Matrix::Identity;
	}

	// �X�V
	void Update();

	DirectX::SimpleMath::Matrix GetCameraMatrix()
	{
		return m_view;
	}
};
