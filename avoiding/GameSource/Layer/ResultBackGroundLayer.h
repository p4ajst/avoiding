// ------------------------------------------------------------------------------------------------ //
// @ file	 :                                                                                      //
// @ brief	 :                                                                                      //
// @ date	 :                                                                                      //
// @ author  :                                                                                      //
// @ note	 :                                                                                      //
// @ version :                                                                                      //
// ------------------------------------------------------------------------------------------------ // 
/* ���d�C���N���[�h�̖h�~ */
#pragma once
/* �w�b�_�t�@�C���̃C���N���[�h */
#include "Layer.h"
/* �N���X�錾 */
class ResultBackGroundLayer :public Layer
{
	/* �����o�ϐ� */
public:
	/* �����o�֐� */
	ResultBackGroundLayer() = default;
	~ResultBackGroundLayer() = default;
	void Initialize(Scene* scene);
	void Update();
	void Draw();
	void Finalize();
};
