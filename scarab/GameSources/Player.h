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
		bool active;      //�v���C���[���B��Ă��邩�ǂ���
		bool isGrand;

		
		
	//�v���C���[�̓����ɕK�v�Ȋ֐�
		void DrawStrings(); //������̕\��
		InputHandler<Player> m_InputHandler;	//���̓n���h���[
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
		Vec3 GetMoveVector()const;				//�i�s�����𓾂�
	};
	//--------------------------------------------------------------------------------------
	//	�v���C���[�̒Ǐ]�I�u�W�F�N�g
	//--------------------------------------------------------------------------------------

	class PlayerChild : public GameObject{
		//�X�e�[�g�}�V�[��
		unique_ptr< StateMachine<PlayerChild> >  m_StateMachine;
		Vec3 m_StartPos;
		float m_StateChangeSize;
		InputHandler<PlayerChild> m_InputHandler;
		//�t�H�[�X
		Vec3 m_Force;
		//���x
		Vec3 m_Velocity;
		//�A�N�e�B�u����
		bool active;
	public:
		//�\�z�Ɣj��
		PlayerChild(const shared_ptr<Stage>& StagePtr, const Vec3& StartPos);
		virtual ~PlayerChild();
		//������
		virtual void OnCreate() override;
		//�A�N�Z�T
		const unique_ptr<StateMachine<PlayerChild>>& GetStateMachine() {
			return m_StateMachine;
		}
		float GetStateChangeSize() const {
			return m_StateChangeSize;
		}
		const Vec3& GetForce()const {
			return m_Force;
		}
		void SetForce(const Vec3& f) {
			m_Force = f;
		}
		void AddForce(const Vec3& f) {
			m_Force += f;
		}
		const Vec3& GetVelocity()const {
			return m_Velocity;
		}
		void SetVelocity(const Vec3& v) {
			m_Velocity = v;
		}
		void ApplyForce();
		Vec3 GetTargetPos()const;
		//����
		virtual void OnUpdate() override;
		//A�{�^���n���h��
		void OnPushA();
		//B�{�^���n���h��
		void OnPushB();
	};

	//--------------------------------------------------------------------------------------
	//	class SeekFarState : public ObjState<PlayerChild>;
	//	�p�r: �v���C���[���牓���Ƃ��̈ړ�
	//--------------------------------------------------------------------------------------
	class PlayerChildFarState : public ObjState<PlayerChild>
	{
		PlayerChildFarState() {}
	public:
		static shared_ptr<PlayerChildFarState> Instancee();
		virtual void Enter(const shared_ptr<PlayerChild>& Obj)override;
		virtual void Execute(const shared_ptr<PlayerChild>& Obj)override;
		virtual void Exit(const shared_ptr<PlayerChild>& Obj)override;
	};

	//--------------------------------------------------------------------------------------
	//	class SeekNearState : public ObjState<PlayerChild>;
	//	�p�r: �v���C���[����߂��Ƃ��̈ړ�
	//--------------------------------------------------------------------------------------
	class PlayerChildNearState : public ObjState<PlayerChild>
	{
		PlayerChildNearState() {}
	public:
		static shared_ptr<PlayerChildNearState> Instance();
		virtual void Enter(const shared_ptr<PlayerChild>& Obj)override;
		virtual void Execute(const shared_ptr<PlayerChild>& Obj)override;
		virtual void Exit(const shared_ptr<PlayerChild>& Obj)override;
	};
//--------------------------------------------------------------------------------------
//	class SeekNearState : public ObjState<PlayerChild>;
//	�p�r: �v���C���[�ɂ��Ă��鎞�̍s��
//--------------------------------------------------------------------------------------

	class PlayerChildStayState :public ObjState<PlayerChild> {
		PlayerChildStayState(){}
	public:
		static shared_ptr<PlayerChildStayState> Instance();
		virtual void Enter(const shared_ptr<PlayerChild>&Obj)override;
		virtual void Execute(const shared_ptr<PlayerChild>&Obj)override;
		virtual void Exit(const shared_ptr<PlayerChild>&Obj)override;
	};
	
};


//end basecross

