/*!
@file GameStage.h
@brief �Q�[���X�e�[�W
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	class GameStage : public Stage {
		//�r���[�̍쐬
		void CreateViewLight();
		//�Œ�̃{�b�N�X�̍쐬
		void CreateFixedBox();
		//�v���C���[�̍쐬
		void CreatePlayer();
		//�G�̍쐬
		void CreateLowEnemy();;
		//�v���C���[���p�������q�I�u�W�F�N�g�̌p��
		void CreatePlayerChild();
		//��������
		void activeboll();
		//�R���W������p�����Œ�{�b�N�X
		void CreateCollisionBox2();
		//�M�~�b�N�p�̃I�u�W�F�N�g����
		void CreateGimmickObj();
	public:
		//�\�z�Ɣj��
		GameStage() :Stage() {}
		virtual ~GameStage() {}
		//������
		virtual void OnCreate()override;
	};


}
//end basecross

