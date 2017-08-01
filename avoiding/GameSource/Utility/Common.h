// ------------------------------------------------------------------------------------------------ //
// @ file	 : Common.h                                                                             //
// @ brief	 : �����̃N���X�ɂ܂�����ϐ����܂Ƃ߂ĊO���Q�Ƃ���w�b�_�t�@�C��                       //
// @ date	 : 2017/06/30                                                                           //
// @ author  : Madoka Nakajima                                                                      //
// @ note	 :                                                                                      //
// @ version : ver.3.00                                                                             //
// ------------------------------------------------------------------------------------------------ // 
/* ���d�C���N���[�h�̖h�~ */
#pragma once

/* �w�b�_�t�@�C���̃C���N���[�h */
// �W�����C�u����
#include <SpriteBatch.h>
#include <memory>

/* �萔��` */
static const int TextureSize = 64;

/* �ϐ���` */
extern bool g_mouseFlag;

/* �֐��̃v���g�^�C�v�錾 */
void DrawNum(DirectX::SpriteBatch* sprite, ID3D11ShaderResourceView* resource,int n, float x,float y);

//void DrawNum(std::shared_ptr<SpriteBatch> sprite, ID3D11ShaderResourceView* resource, int n, float x, float y);
