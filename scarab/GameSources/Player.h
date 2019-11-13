/*!
@file Player.h
@brief �v���C���[�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	//--------------------------------------------------------------------------------------
	///	�v���C���[
	//--------------------------------------------------------------------------------------
	class Player : public GameObject {
		//������̕\��
		void DrawStrings();
		//���̓n���h���[
		InputHandler<Player> m_InputHandler;
		//�i�s�����𓾂�
		Vec3 GetMoveVector() const;
		//�v���C���[���g�p����R���g���[���ƃL�[�{�[�h
		Vec2 GetInputState() const;
		//��]�̌�����i�s�����ɂ���
		void RotToHead(const Vec3& Velocity, float LerpFact);
		//�X�P�[�����O�i���a�̑傫���j
		float m_Scale;
		//�v���C���[�̓���
		void Move();
		//�B��Ă��邩�ǂ����̔���
		bool active;
		//�v���C���[�̃X�s�[�h
		float m_Speed;
	public:
		//�\�z�Ɣj��
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�R���X�g���N�^
		@param[in]	StagePtr	�X�e�[�W
		*/
		//--------------------------------------------------------------------------------------
		Player(const shared_ptr<Stage>& StagePtr);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�f�X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		virtual ~Player() {}
		//�A�N�Z�T
		//������
		virtual void OnCreate() override;
		//�X�V
		virtual void OnUpdate() override;
		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other) override;
		virtual void OnCollisionExit(shared_ptr<GameObject>& Other) override;
		//virtual void OnCollisionStay(shared_ptr<GameObject>&Other) override;

		//��X�V
		virtual void OnUpdate2() override;
		//A�{�^���n���h��
		void OnPushA();
		//B�{�^���n���h��
		void OnPushB();



	};
	
};


//end basecross

