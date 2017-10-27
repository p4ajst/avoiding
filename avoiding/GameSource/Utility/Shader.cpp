// ------------------------------------------------------------------------------------------------ //
// @ file	 : Shader.cpp                                                                           //
// @ brief	 : �V�F�[�_�[�𗘗p���邽�߂̊֐��Q                                                     //
// @ date	 : 2017/10/19                                                                           //
// @ author  : Madoka Nakajima                                                                      //
// @ note	 :                                                                                      //
// @ version : ver.3.00                                                                             //
// ------------------------------------------------------------------------------------------------ // 
/* �w�b�_�t�@�C���̃C���N���[�h */
// �W�����C�u����
#include <fstream>
#include <simplemath.h>
// �搶�̃��C�u����
#include "../../ImaseLib/Direct3D.h"
#include "../../ImaseLib/DirectXTK.h"
// ����w�b�_�t�@�C��
#include "Shader.h"

/* ���O��� */
// ComPtr���g����
using namespace Microsoft::WRL;
// unique_ptr���g����
using namespace std;
// DirectX�̋@�\���g����
using namespace DirectX;
// SimpleMath�̋@�\���g����
using namespace DirectX::SimpleMath;
// ���얼�O���
using namespace mnLib;

/* �����o�֐��̒�` */


// ----------------------------------------------------------------------------------------------- //
// @ brief	: �R���X�g���N�^                                                                       //
// @ param	: �Ȃ�                                                                                 //
// @ return : �Ȃ�                                                                                 //
// @ note	: ���얼�O��ԓ��̊֐�                                                                 //
// ----------------------------------------------------------------------------------------------- // 
mnLib::Shader::Shader()
{
	// ���f���ɋ������
	model = nullptr;
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: �f�X�g���N�^                                                                         //
// @ param	: �Ȃ�                                                                                 //
// @ return : �Ȃ�                                                                                 //
// @ note	: ���얼�O��ԓ��̊֐�                                                                 //
// ----------------------------------------------------------------------------------------------- // 
mnLib::Shader::~Shader()
{

}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: �V�F�[�_�[��ݒ肷�郂�f���̏�����                                                   //
// @ param	: wchar_t* name...�ǂݍ��ރ��f���̃t�@�C����                                           //
// @ return : �Ȃ�                                                                                 //
// @ note	: ���얼�O��ԓ��̊֐�                                                                 //
// ----------------------------------------------------------------------------------------------- // 
void mnLib::Shader::InitShader(wchar_t * name)
{
	DGSLEffectFactory fx(g_pd3dDevice.Get());
	fx.SetDirectory(L"Resources");
	model = Model::CreateFromCMO(g_pd3dDevice.Get(), name, fx);
}


// ----------------------------------------------------------------------------------------------- //
// @ brief	: �V�F�[�_�[���쐬����                                                                 //
// @ param	: const char * vertex...���_�V�F�[�_�[�̃t�@�C����                                     //
// @ param	: const char * pixel...�s�N�Z���V�F�[�_�̃t�@�C����                                    //
// @ return : �Ȃ�                                                                                 //
// @ note	: ���얼�O��ԓ��̊֐�                                                                 //
// ----------------------------------------------------------------------------------------------- // 
void mnLib::Shader::CreateShader(const char * vertex, const char * pixel)
{
	// ���_�V�F�[�_
	binary.Load(vertex);
	// ���_�V�F�[�_�̍쐬�i�������j
	g_pd3dDevice.Get()->CreateVertexShader(buffer.data(), buffer.size(), nullptr, vertexShader.GetAddressOf());
	/*
	�C���v�b�g���C�A�E�g
	���͂���v�f�́A���W�E�@���E�ڐ��E�F�E�e�N�X�`�����W
	*/
	g_pd3dDevice.Get()->CreateInputLayout
	(
		// ���̗͂v�f�w��
		VertexPositionNormalTangentColorTexture::InputElements,
		// ���̗͂v�f��
		VertexPositionNormalTangentColorTexture::InputElementCount,
		// ���_�V�F�[�_
		buffer.data(),
		// ���_�V�F�[�_�̃T�C�Y
		buffer.size(),
		// �C���v�b�g���C�A�E�g�̎擾
		inputLayout.GetAddressOf()
	);

	// �s�N�Z���V�F�[�_
	binary.Load(pixel);
	// �s�N�Z���V�F�[�_�̍쐬�i�������j
	g_pd3dDevice.Get()->CreatePixelShader(buffer.data(), buffer.size(), nullptr, pixelShader.GetAddressOf());
}

// ----------------------------------------------------------------------------------------------- //
// @ brief	: �R���X�^���g�o�b�t�@�̏�����                                                         //
// @ param	: �Ȃ�                                                                                 //
// @ return : �Ȃ�                                                                                 //
// @ note	: ���얼�O��ԓ��̊֐�                                                                 //
// ----------------------------------------------------------------------------------------------- // 
void mnLib::Shader::CreateConstantBuffer()
{
	// �R���X�^���g�o�b�t�@�̏�������
	D3D11_BUFFER_DESC bufferDesc = {};
	// �T�C�Y
	bufferDesc.ByteWidth = sizeof(MatrixesConstant);
	// �ꏊ�F�r�f�I�������ɍ쐬
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	// �ڑ��F�R���X�^���g�o�b�t�@
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	// CPU����̃A�N�Z�X�F��������
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	// �g��Ȃ�
	bufferDesc.MiscFlags = 0;
	// �g��Ȃ�
	bufferDesc.StructureByteStride = 0;

	// �R���X�^���g�o�b�t�@�̍쐬
	g_pd3dDevice.Get()->CreateBuffer(&bufferDesc, nullptr, constantBuffer.GetAddressOf());
	matrixesConstant.reset(new MatrixesConstant());
}


// ----------------------------------------------------------------------------------------------- //
// @ brief	: �`��                                                                                 //
// @ param	: Matrix view...�r���[�s��                                                             //
// @ param	: Matrix proj...�ˉe�s��                                                               //
// @ return : �Ȃ�                                                                                 //
// @ note	: ���얼�O��ԓ��̊֐�                                                                 //
// ----------------------------------------------------------------------------------------------- // 
void mnLib::Shader::Draw(Matrix view, Matrix proj)
{
	// ���[���h�s��
	Matrix world = Matrix::Identity;
	// ���[���h���r���[���v���W�F�N�V����
	Matrix wvp = Matrix::Identity;

	// ���[���h���r���[���v���W�F�N�V�����̕ϐ��ɂ��ꂼ���������
	wvp *= world;
	wvp *= view;
	wvp *= proj;

	// �R���X�^���g�o�b�t�@�̐ݒ�
	// ���ݒ莞��Transpose����i�]�u�s��j
	matrixesConstant->WorldViewProjection = wvp.Transpose();

	// �`��
	model->Draw(g_pImmediateContext.Get(), *g_state.get(), world, view, proj, false, [&]()
	{
		// GPU�̃R���X�^���g�o�b�t�@�ɃA�N�Z�X����A�h���X�̎擾
		D3D11_MAPPED_SUBRESOURCE mappedResource;
		g_pImmediateContext.Get()->Map(constantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
		// GPU��̃R���X�^���g�o�b�t�@�Ƀf�[�^�𑗂�
		*(MatrixesConstant*)mappedResource.pData = *matrixesConstant.get();
		g_pImmediateContext.Get()->Unmap(constantBuffer.Get(), 0);

		// �C���v�b�g���C�A�E�g�̐ݒ�
		g_pImmediateContext.Get()->IASetInputLayout(inputLayout.Get());
		// �o�[�e�b�N�X�V�F�[�_�̐ݒ�
		g_pImmediateContext.Get()->VSSetShader(vertexShader.Get(), nullptr, 0);

		// �o�[�e�b�N�X�V�F�[�_�ɓn���R���X�^���g�o�b�t�@
		ID3D11Buffer * buffer[] = { constantBuffer.Get() };
		g_pImmediateContext.Get()->VSSetConstantBuffers(0, 1, buffer);

		// �s�N�Z���V�F�[�_�̐ݒ�
		g_pImmediateContext.Get()->PSSetShader(pixelShader.Get(), nullptr, 0);
	});
}

void mnLib::Shader::SetModel(wchar_t * filename)
{
	InitShader(filename);
}
