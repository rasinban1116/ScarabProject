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
		int m_cursornum;
		bool m_CntrolLock;
		bool m_txflg;
		InputHandler<TitleStage> m_InputHandler;	//���̓n���h���[

	public:
		//�\�z�Ɣj��
		TitleStage() :Stage() {}
		virtual ~TitleStage() {}
		//������
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		void CreateTitleSprite();
		void ControlStick();
		void OnPushA();
		void OnPushB() {}
	};
	//--------------------------------------------------------------------------------------
	///�@�X�e�[�W�N���A�p�X�e�[�W
	//--------------------------------------------------------------------------------------
	class ClearStage :public Stage {
		bool m_CntrolLock;
		//�r���[�̍쐬
		void CreateViewLight();
		void GameSystemObj();
		void System();
		int m_cursornum;
		float m_strSprite;
		float m_sprite;
		float m_spriteif;
		float m_txpos;
		bool m_txflg;
		InputHandler<ClearStage> m_InputHandler;	//���̓n���h���[

	public:
		//�\�z�Ɣj��
		ClearStage() :Stage() {}
		virtual ~ClearStage() {}
		//������
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		void CreateClearSprite();
		void ControlStick();
		void OnPushA();
		void OnPushB() {}
	};

	//--------------------------------------------------------------------------------------
	///�@�X�e�[�W�Z���N�g�p�X�e�[�W
	//--------------------------------------------------------------------------------------
	class SerectStage :public Stage {
		bool m_CntrolLock;
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
		void ControlStick();
		void OnPushA();
		void OnPushB();
		void OnCreateSrectObj();
	};

	//--------------------------------------------------------------------------------------
	///�@�Q�[���I�[�o�[�p�X�e�[�W
	//--------------------------------------------------------------------------------------
	class GameOverStage :public Stage {
		//�r���[�̍쐬
		void CreateViewLight();
		void CreateStage();
		InputHandler<GameOverStage> m_InputHandler;	//���̓n���h���[
		int m_cursornum;
		float m_strSprite;
		float m_sprite;
		float m_spriteif;
		bool m_CntrolLock;
	public:
		//�\�z�Ɣj��
		GameOverStage() :Stage() {}
		virtual ~GameOverStage() {}
		//������
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		void ControlStick();
		void OnPushA();
		void OnPushB();
	};
}
//end basecross

