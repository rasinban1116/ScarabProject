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
		//MyCamera�p�̃r���[
		shared_ptr<SingleView> m_MyCameraView;
		//CSV�t�@�C������A
		CsvFile m_GameStageCsvA;
		//CSV�t�@�C������B
		CsvFile m_GameStageCsvB;
		//�Œ�̃{�b�N�X�̍쐬
		void CreateFixedBox();
		//�Œ�̌X�����{�b�N�X�̍쐬
		void CreateBox();
		//�v���C���[�̍쐬
		void CreatePlayer();
		//�G�̍쐬
		void CreateLowEnemy();;
		//�v���C���[���p�������q�I�u�W�F�N�g�̌p��
		void CreatePlayerChild();
		//�Q�[���N���A�p�̃I�u�W�F�N�g�쐬
		void CreateClearObj();
		//��̍쐬
		void CreateSky();
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

