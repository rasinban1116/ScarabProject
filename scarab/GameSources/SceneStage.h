/*!
@file SceneStage.h
@brief �V�[���p�̃Q�[���X�e�[�W�Q
*/

#pragma once
#include "stdafx.h"

namespace basecross {
//--------------------------------------------------------------------------------------
///	�^�C�g���p�X�e�[�W
//--------------------------------------------------------------------------------------
	class TitleStage :public Stage {
		//�r���[�̍쐬
		void CreateViewLight();
		void GameSystemObj();
		void System();
		InputHandler<TitleStage> m_InputHandler;	//���̓n���h���[

	public:
		//�\�z�Ɣj��
		TitleStage() :Stage() {}
		virtual ~TitleStage() {}
		//������
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		void OnPushA();
		void OnPushB();
	};
//--------------------------------------------------------------------------------------
///�@�X�e�[�W�N���A�p�X�e�[�W
//--------------------------------------------------------------------------------------
	class ClearStage :public Stage {
		//�r���[�̍쐬
		void CreateViewLight();
		void GameSystemObj();
		void System();
		InputHandler<ClearStage> m_InputHandler;	//���̓n���h���[

	public:
		//�\�z�Ɣj��
		ClearStage() :Stage() {}
		virtual ~ClearStage() {}
		//������
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		void OnPushA();
		void OnPushB();
	};

//--------------------------------------------------------------------------------------
///�@�X�e�[�W�Z���N�g�p�X�e�[�W
//--------------------------------------------------------------------------------------
	class SerectStage :public Stage {
		//�r���[�̍쐬
		void CreateViewLight();
		void CreateStage();
		InputHandler<SerectStage> m_InputHandler;	//���̓n���h���[

	public:
		//�\�z�Ɣj��
		SerectStage() :Stage() {}
		virtual ~SerectStage() {}
		//������
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		void CreatePlayer();
		void OnPushA();
		void OnPushB();
	};

//--------------------------------------------------------------------------------------
///�@�Q�[���I�[�o�[�p�X�e�[�W
//--------------------------------------------------------------------------------------
	class GameOverStage :public Stage {
		//�r���[�̍쐬
		void CreateViewLight();
		void CreateStage();
		InputHandler<GameOverStage> m_InputHandler;	//���̓n���h���[

	public:
		//�\�z�Ɣj��
		GameOverStage() :Stage() {}
		virtual ~GameOverStage() {}
		//������
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		void OnPushA();
		void OnPushB();
	};
}
//end basecross

