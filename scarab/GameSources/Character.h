/*!
@file Character.h
@brief �L�����N�^�[�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	//--------------------------------------------------------------------------------------
	///	�V�[�\�[
	//--------------------------------------------------------------------------------------
	class Seesaw : public GameObject {
		Vec3 m_Position;
		Vec3 m_Scale;
		bool m_flg;

	public :
		Seesaw(const shared_ptr<Stage>&StagePtr,
			const Vec3 &Posion);
		void SetFlg(bool ptrflg) {
			m_flg = ptrflg;
		}
		bool GetFlg() {
			return m_flg;
		}
		Vec3 GetPos() {
			return m_Position;
		}
		Vec3 GetSca() {
			return m_Scale;
		}
		virtual ~Seesaw() override{}
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
	};

	//--------------------------------------------------------------------------------------
	///	�V�[�\�[�̎�
	//--------------------------------------------------------------------------------------
	class SeesawAxis : public GameObject {
		Vec3 m_Position;
		Vec3 m_Scale;
		const shared_ptr<GameObject>& m_ParentPtr;
	public:
		SeesawAxis(const shared_ptr<Stage>&StagePtr,
			const Vec3 &Posion,
			const Vec3 &Scale,
			const shared_ptr<GameObject>& ParentPtr);
		virtual ~SeesawAxis() override{}
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
	};

	//--------------------------------------------------------------------------------------
	///	�v���C���[���i�܂Ȃ��悤�ɋz�����߂̓����蔻��
	//--------------------------------------------------------------------------------------
	class SeesawBox : public GameObject {
		Vec3 m_Position;
		Vec3 m_Scale;
		int boxnum;
		const shared_ptr<GameObject>& m_ParentPtr;
	public :
		SeesawBox(const shared_ptr<Stage>&StagePtr,
			const Vec3 &Position,
			const Vec3 &Scale,
			const int &num,
			const shared_ptr<GameObject>& ParentPtr);
		virtual ~SeesawBox(){}
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other)override;
	};


	//--------------------------------------------------------------------------------------
	///	�Œ�I�u�W�F�N�g
	//--------------------------------------------------------------------------------------
	class FixedBox : public GameObject {
		Vec3 m_Position;
		Vec3 m_Scele;

	public:
		FixedBox(const shared_ptr<Stage>&StagePtr,
			const Vec3 &Posion,
			const Vec3 &Scale
		);
		virtual ~FixedBox();
		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		virtual void OnCollisionEnter(shared_ptr<GameObject>&StagePtr);
	};

	//--------------------------------------------------------------------------------------
	///	�����v�Z����Œ�̎΂߃{�b�N�X
	//--------------------------------------------------------------------------------------
	class SlopeFixedBox : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
		float m_UPic;
		float m_VPic;
		wstring m_Texname;
	public:
		//�\�z�Ɣj��
		SlopeFixedBox(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position,
			float UPic,
			float VPic,
			const wstring& Texname
		);
		virtual ~SlopeFixedBox();
		//������
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		//����
		virtual void OnCollisionEnter(shared_ptr<GameObject>&ptrObj)override;
		virtual void OnCollisionExcute(shared_ptr<GameObject>&ptrObj)override;
	};

	//--------------------------------------------------------------------------------------
	//�@�^�C�����O����Œ�̃{�b�N�X
	//--------------------------------------------------------------------------------------
	class TilingFixedBox : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
		float m_UPic;
		float m_VPic;
		wstring m_Texname;
	public:
		//�\�z�Ɣj��
		TilingFixedBox(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position,
			float UPic,
			float VPic,
			const wstring& Texname
		);
		virtual ~TilingFixedBox();
		//������
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		//����
		virtual void OnCollisionEnter(shared_ptr<GameObject>&ptrObj)override;
		virtual void OnCollisionExcute(shared_ptr<GameObject>&ptrObj)override;
	};


	

	//--------------------------------------------------------------------------------------
	//�@���̂̃J�����}��
	//--------------------------------------------------------------------------------------
	class Cameraman : public GameObject {
		float m_ToPlayerLen;
	public:
		//�\�z�Ɣj��
		Cameraman(const shared_ptr<Stage>& StagePtr,
			float ToPlayerLen
		);
		virtual ~Cameraman();
		//������
		virtual void OnCreate() override;
		//����
		virtual void OnUpdate() override;
	};


	//--------------------------------------------------------------------------------------
	//�@�I�[�v�j���O�J�����}��
	//--------------------------------------------------------------------------------------
	class OpeningCameraman : public GameObject {
		Vec3 m_StartPos;
		Vec3 m_EndPos;
		Vec3 m_AtStartPos;
		Vec3 m_AtEndPos;
		Vec3 m_AtPos;
		float m_TotalTime;
		//�X�e�[�g�}�V�[��
		unique_ptr< StateMachine<OpeningCameraman> >  m_StateMachine;
	public:
		//�\�z�Ɣj��
		OpeningCameraman(const shared_ptr<Stage>& StagePtr);
		virtual ~OpeningCameraman();
		//������
		virtual void OnCreate() override;
		//����
		virtual void OnUpdate() override;
		//�A�N�Z�T
		const unique_ptr<StateMachine<OpeningCameraman>>& GetStateMachine() {
			return m_StateMachine;
		}

		Vec3 GetAtPos() const {
			return m_AtPos;
		}
		void ToGoalEnterBehavior();
		void ToStartEnterBehavior();
		bool ExcuteBehavior(float totaltime);
		void EndStateEnterBehavior();
	};

	//--------------------------------------------------------------------------------------
	//	class OpeningCameramanToGoalState : public ObjState<OpeningCameraman>;
	//--------------------------------------------------------------------------------------
	class OpeningCameramanToGoalState : public ObjState<OpeningCameraman>
	{
		OpeningCameramanToGoalState() {}
	public:
		static shared_ptr<OpeningCameramanToGoalState> Instance();
		virtual void Enter(const shared_ptr<OpeningCameraman>& Obj)override;
		virtual void Execute(const shared_ptr<OpeningCameraman>& Obj)override;
		virtual void Exit(const shared_ptr<OpeningCameraman>& Obj)override;
	};

	//--------------------------------------------------------------------------------------
	//	class OpeningCameramanToStartState : public ObjState<OpeningCameraman>;
	//--------------------------------------------------------------------------------------
	class OpeningCameramanToStartState : public ObjState<OpeningCameraman>
	{
		OpeningCameramanToStartState() {}
	public:
		static shared_ptr<OpeningCameramanToStartState> Instance();
		virtual void Enter(const shared_ptr<OpeningCameraman>& Obj)override;
		virtual void Execute(const shared_ptr<OpeningCameraman>& Obj)override;
		virtual void Exit(const shared_ptr<OpeningCameraman>& Obj)override;
	};

	//--------------------------------------------------------------------------------------
	//	class OpeningCameramanEndState : public ObjState<OpeningCameraman>;
	//--------------------------------------------------------------------------------------
	class OpeningCameramanEndState : public ObjState<OpeningCameraman>
	{
		OpeningCameramanEndState() {}
	public:
		static shared_ptr<OpeningCameramanEndState> Instance();
		virtual void Enter(const shared_ptr<OpeningCameraman>& Obj)override;
		virtual void Execute(const shared_ptr<OpeningCameraman>& Obj)override;
		virtual void Exit(const shared_ptr<OpeningCameraman>& Obj)override;
	};

}
//end basecross
