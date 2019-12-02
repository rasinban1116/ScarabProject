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
		//CSV�t�@�C������A
		CsvFile m_GameStageCsvA;
		//CSV�t�@�C������B
		CsvFile m_GameStageCsvB;
		//�Œ�̃{�b�N�X�̍쐬
		void CreateFixedBox();
		//�Œ�̌X�����{�b�N�X�̍쐬
		void CreateFixedSlopeBox();
		//�v���C���[�̍쐬
		void CreatePlayer();
		//�v���C���[���p�������q�I�u�W�F�N�g�̌p��
		void CreatePlayerChild();
		//��������
		void activeboll();
		//�M�~�b�N�p�̃I�u�W�F�N�g����
		void CreateGimmickObj();
		//UI�̕\��
		void CreateUI();
		void GameSystemObj();
	public:
		//�\�z�Ɣj��
		GameStage() :Stage() {}
		virtual ~GameStage() {}
		//������
		virtual void OnCreate()override;
	};


}
//end basecross

