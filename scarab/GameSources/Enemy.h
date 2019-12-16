#pragma once
#include "stdafx.h"

namespace basecross {

	enum class EnemyLook {
		LookOf,
		LookOn
	};

	class LookFlg {

		bool m_lookflg;

	public :

		void SetLook(bool ptrlook) {
			m_lookflg = ptrlook;
		}

		bool GetLook() {
			return m_lookflg;
		}

		wstring ToString() {
			if (m_lookflg) {
				return L"true";
			} else {
				return L"false";
			}
		}
	};

	class Enemy : public GameObject, public LookFlg{
		unique_ptr< StateMachine<Enemy> >  m_StateMachine;
		Vec3 m_StrPos;
		float m_StateChangeSize;
		//フォース
		Vec3 m_Force;
		//速度
		Vec3 m_Velocity;
		Vec3 m_Status;
		bool m_lookflg;
		Vec3 m_TagePos;
		void ApplyForce();
		Vec3 m_ParentPtr;
		int size;
		EnemyLook m_state;

	public :
		Enemy(const shared_ptr<Stage>& StagePtr, const Vec3& StartPos, const Vec3& TagePos, const int&size);
		virtual ~Enemy();

		//アクセサ
		const unique_ptr<StateMachine<Enemy>>& GetStateMachine() {
			return m_StateMachine;
		}
		Vec3 GetStartPos() const {
			return m_StrPos;
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
		bool GetLook() {
			return m_lookflg;
		}

		shared_ptr<GameObject>  GetTarget()const;
		//virtual void NearBehavior();
		//virtual void FarBehavior();
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};

	//--------------------------------------------------------------------------------------
	//	 プレイヤーから遠いときの移動
	//--------------------------------------------------------------------------------------
	class LookOfState : public ObjState<Enemy>, public LookFlg
	{
		bool m_lookflg;
		LookOfState() {}
	public:
		static shared_ptr<LookOfState> Instance();
		virtual void Enter(const shared_ptr<Enemy>& Obj)override;
		virtual void Execute(const shared_ptr<Enemy>& Obj)override;
		virtual void Exit(const shared_ptr<Enemy>& Obj)override;
	};

	//--------------------------------------------------------------------------------------
	//	 プレイヤーから近いときの移動
	//--------------------------------------------------------------------------------------
	class LookOnState : public ObjState<Enemy>
	{
		LookOnState() {}
	public:
		static shared_ptr<LookOnState> Instance();
		virtual void Enter(const shared_ptr<Enemy>& Obj)override;
		virtual void Execute(const shared_ptr<Enemy>& Obj)override;
		virtual void Exit(const shared_ptr<Enemy>& Obj)override;
	};


	class EnemyEye : public GameObject, public LookFlg{
		Vec3 m_StartPos;
		Vec3 m_Rot;
		const shared_ptr<GameObject>& m_ParentPtr;
	public:
		EnemyEye(const shared_ptr<Stage>& StagePtr, const Vec3& StartPos, const shared_ptr<GameObject>& ParentPtr);
		virtual ~EnemyEye();
		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other) override;
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		void DebagMesse();
	};
}