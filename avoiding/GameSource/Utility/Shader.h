// ------------------------------------------------------------------------------------------------ //
// @ file	 : Shader.h                                                                             //
// @ brief	 : �V�F�[�_�[�𗘗p���邽�߂̊֐��Q                                                     //
// @ date	 : 2017/10/19                                                                           //
// @ author  : Madoka Nakajima                                                                      //
// @ note	 :                                                                                      //
// @ version : ver.3.00                                                                             //
// ------------------------------------------------------------------------------------------------ // 
/* ���d�C���N���[�h�̖h�~ */
#pragma once
/* �w�b�_�t�@�C���̃C���N���[�h */
// �X�^���_�[�h���C�u�����֘A 
#include <memory>          // �X�}�[�g�|�C���^���g������
#define _USE_MATH_DEFINES
#include <cmath>           // �Z�p�֐�
#include <iostream>        // IO�X�g���[��

// DirectX�֘A
#include <DirectXMath.h>   // DirectX�̎Z�p�֘A���g������
#include <SimpleMath.h>    // DirectXTK�̊ȈՎZ�p�֘A���g������
#include <DirectXColors.h> // �F�w��̂���

#include <wrl.h>  // Windows �����^�C�� C++ �e���v���[�g ���C�u����

// DGSL�V�F�[�_���g�p���邽�߂̃w�b�_�t�@�C��
#include <Effects.h>
#include <Model.h>
#include <CommonStates.h>

// �o�[�e�b�N�X�V�F�[�_���g�p���邽�߂̃w�b�_�t�@�C��
#include <d3d11.h>
#include <vector>
#include <fstream>
#include <VertexTypes.h>
#include <DirectXMath.h>

// ����w�b�_�t�@�C��
#include "BinaryLoader.h"

namespace mnLib
{
	/* �\���̂̐錾 */
	// �V�F�[�_�ɓn���f�[�^�̍\����
#pragma pack(push,1)
	__declspec(align(16)) struct MatrixesConstant
	{
		DirectX::XMMATRIX WorldViewProjection;   // world * view * projection
		float x;                                 // �����W
		float z;                                 // �����W
		float padding1;                          // ��Ԃ𖄂߂�	
		float padding2;                          // ��Ԃ𖄂߂�	

		// Allocate aligned memory.
		static void* operator new(size_t size)
		{
			// �A���C�����g���擾
			const size_t alignment = __alignof(MatrixesConstant);
			/*
			�@�@�G���[���b�Z�[�W�FAlignedNew > �͂W�o�C�g�A���C�����g�����^�C�v�ɂ̂ݗL���ł��B
			  �@���Ȃ��͔h����__declspec�i�ʒu���킹�j��Y��܂������B
			   */
			static_assert(alignment > 8
				, "AlignedNew is only useful for types with > 8byte alignment.Did you forget a __declspec(align) on TDerved ? ");
			// �A���C�����g�ɍ��킹�ă������[�m��
			void* ptr = _aligned_malloc(size, alignment);
			// �������[�m�ۂł������`�F�b�N
			if (!ptr)
				throw std::bad_alloc();
			// �m�ۂ����������A�h���X��Ԃ�
			return ptr;
		}

		// Free align memory.
		static void operator delete(void* ptr)
		{
			// _aligned_malloc�Ŋm�ۂ����������[�̉��
			_aligned_free(ptr);
		}
	};
#pragma pack(pop)

	// �R���X�^���g�o�b�t�@�̍\����
#pragma pack(push,1)
	struct MatrixesConstants
	{
		DirectX::XMMATRIX WorldViewProjection;
		float x;
		float z;
	};
#pragma pack(pop)

	class Shader
	{
	public:
		/* �����o�ϐ� */
		// �R���X�g���N�^
		Shader();
		// �f�X�g���N�^
		~Shader();
		// �R���X�^���g�o�b�t�@
		std::vector<char> buffer;
		// ���_�V�F�[�_
		Microsoft::WRL::ComPtr<ID3D11VertexShader> vertexShader;
		// �C���v�b�g���C�A�E�g
		Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout;
		// �s�N�Z���V�F�[�_
		Microsoft::WRL::ComPtr<ID3D11PixelShader> pixelShader;
		// �R���X�^���g�o�b�t�@�̃I�u�W�F�N�g
		Microsoft::WRL::ComPtr<ID3D11Buffer> constantBuffer;
		// �R���X�^���g�o�b�t�@�ɓn���f�[�^
		std::unique_ptr<MatrixesConstant> matrixesConstant;
		// ���f��
		std::shared_ptr<DirectX::Model> model;
		// �o�C�i�����[�_�[
		BinaryLoader binary;

		/* �����o�֐� */
		void InitShader(wchar_t* name);

		void CreateShader(const char* vertex, const char* pixel);
		void CreateConstantBuffer();

		void Draw(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);

		std::shared_ptr<DirectX::Model> GetModel() { return model; }
		void SetModel(wchar_t* filename);
	};
}

