#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	敵本体
	//--------------------------------------------------------------------------------------
	class Enemy : public GameObject{
		unique_ptr< StateMachine<Enemy> >  m_StateMachine;
		Vec3 m_StrPos;
		float m_StateChangeSize;
		//フォース
		Vec3 m_Force;
		//速度
		Vec3 m_Velocity;
		Vec3 m_Status;
		Vec3 m_TagePos;
		void ApplyForce();
		Vec3 m_ParentPtr;
		int size;
		wstring tex;
		wstring model;
		bool m_lookflg;


	public :
		Enemy(const shared_ptr<Stage>& StagePtr, const Vec3& StartPos, const Vec3& TagePos, const int&size,
			const wstring ptrtex, const wstring ptrmodel);
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
		void SetLook(bool ptrlookflg) {
			m_lookflg = ptrlookflg;
		}
		wstring GetModelname() {
			return model;
		}

		shared_ptr<GameObject>  GetTarget()const;
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		void OnCollisionEnter(shared_ptr<GameObject>& Other);
	};

	//--------------------------------------------------------------------------------------
	//	 プレイヤーから遠いときの移動
	//--------------------------------------------------------------------------------------
	class LookOfState : public ObjState<Enemy>
	{
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

	//--------------------------------------------------------------------------------------
	//	 敵の視界
	//--------------------------------------------------------------------------------------
	class EnemyEye : public GameObject{
		Vec3 m_StartPos;
		Vec3 m_Rot;
		const shared_ptr<GameObject>& m_ParentPtr;
	public:
		//ParentPtr 親のクラス
		EnemyEye(const shared_ptr<Stage>& StagePtr, const Vec3& StartPos, const shared_ptr<GameObject>& ParentPtr);
		virtual ~EnemyEye();
		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other) override;
		virtual void OnCreate() override;
		virtual void OnUpdate() override;


	};
}