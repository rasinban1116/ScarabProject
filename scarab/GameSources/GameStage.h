/*!
@file GameStage.h
@brief �Q�[���X�e�[�W
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	enum class CameraSelect {
		openingCamera,
		myCamera,
		objCamera,
	};

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	class GameStage : public Stage {
		//�r���[�̍쐬
		void CreateViewLight();
		//OpeningCamera�p�̃r���[
		shared_ptr<SingleView> m_OpeningCameraView;
		//MyCamera�p�̃r���[
		shared_ptr<SingleView> m_MyCameraView;
		//ObjCamera�p�̃r���[
		shared_ptr<SingleView> m_ObjCameraView;
		CameraSelect m_CameraSelect;
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
		//��������
		void activeboll();
		//�M�~�b�N�p�̃I�u�W�F�N�g����
		void CreateGimmickObj();
		//�Q�[���N���A�p�̃I�u�W�F�N�g�쐬
		void CreateClearObj();
		//UI�̕\��
		void CreateUI();
		void GameSystemObj();
		//�J�����}���̍쐬
		void CreateCameraman();
	public:
		//�\�z�Ɣj��
		GameStage() :Stage() {}
		virtual ~GameStage() {}
		CameraSelect GetCameraSelect() const {
			return m_CameraSelect;
		}
		//������
		virtual void OnCreate()override;
		void ToMyCamera();
		void ToObjCamera();
	};


}
//end basecross

