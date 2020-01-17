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
	//�v���C���[�ɕK�v�Ȋe�ϐ�
		float m_Speed;    //�v���C���[�̃X�s�[�h
		float m_Scale;    //�v���C���[�̑傫���i���a�j
		Vec3 m_PlayVelo;  //�v���C���[�̑��x�x�N�g��
		Vec3 m_pos;       //�v���C���[�̃|�W�V����
		bool active;      //�v���C���[���B��Ă��邩�ǂ���
		bool isGrand;

	
	//�v���C���[�̓����ɕK�v�Ȋ֐�
		void DrawStrings(); //������̕\��
		InputHandler<Player> m_InputHandler;	//���̓n���h���[
		Vec3 GetMoveVector()const;				//�i�s�����𓾂�
		Vec2 GetInputState() const;				//�v���C���[���g�p����R���g���[���ƃL�[�{�[�h
		void RotToHead(const Vec3& Velocity, float LerpFact);		//��]�̌�����i�s�����ɂ���
		void Move();							//�v���C���[�̓���
		void ChangeTrans();                     //�g�����X�t�H�[���ւ̐ݒ�
	
	public:
		//�\�z�Ɣj��
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�R���X�g���N�^
		@param[in]	StagePtr	�X�e�[�W
		*/
		//--------------------------------------------------------------------------------------
		Player(const shared_ptr<Stage>& StagePtr,
			const Vec3 &Position);
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
		virtual void OnCollisionExcute(shared_ptr<GameObject>& Other) override;

		//��X�V
		virtual void OnUpdate2() override;
		//A�{�^���n���h��
		void OnPushA();
		//B�{�^���n���h��
		void OnPushB();
		void OnPushDOWN(){}
		void OnPushUP(){}



	};

	//--------------------------------------------------------------------------------------
	//	����
	//--------------------------------------------------------------------------------------
	class UnkoBoll : public Player {
		Vec3 UnkoPos;
		Vec3 UnkoScale;
		Vec3 UnkoRot;
		Vec3 UnkoVelo;

	
	public:
		//�\�z�Ɣj��
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�R���X�g���N�^
		@param[in]	StagePtr	�X�e�[�W
		*/
		//--------------------------------------------------------------------------------------
		UnkoBoll(const shared_ptr<Stage>& StagePtr,
			const Vec3& Position,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Velocity
			);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�f�X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		virtual ~UnkoBoll() {}
		//�A�N�Z�T
		//������
		virtual void OnCreate() override;
		//�X�V
		virtual void OnUpdate() override;
		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other) override;
		virtual void OnCollisionExcute(shared_ptr<GameObject>&Other) override;
		virtual void OnCollisionExit(shared_ptr<GameObject>&Other) override;
		//��X�V
		virtual void OnUpdate2() override;
		void Move();
		static float  ScaleUp();
		Vec3 holdon();
		bool active;
	
	};
	
};


//end basecross

