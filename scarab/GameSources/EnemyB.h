/*!
@file Character.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"

namespace basecross{

	//--------------------------------------------------------------------------------------
	//	配置されるオブジェクトの親
	//--------------------------------------------------------------------------------------
	class Enemy : public GameObject {
		//ステートマシーン
		unique_ptr< StateMachine<Enemy> >  m_StateMachine;
		Vec3 m_StartPos;
		float m_StateChangeSize;
		//フォース
		Vec3 m_Force;
		//速度
		Vec3 m_Velocity;
		Vec3 m_Status;
		void ApplyForce();
	protected:
		//構築と破棄
		Enemy(const shared_ptr<Stage>& StagePtr, const Vec3& StartPos);
		virtual ~Enemy();
	public:
		//アクセサ
		const unique_ptr<StateMachine<Enemy>>& GetStateMachine() {
			return m_StateMachine;
		}
		Vec3 GetStartPos() const {
			return m_StartPos;
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
		shared_ptr<GameObject>  GetTarget()const;
		virtual void NearBehavior() = 0;
		virtual void FarBehavior() = 0;
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};

	//--------------------------------------------------------------------------------------
	//	プレイヤーから遠いときの移動
	//--------------------------------------------------------------------------------------
	class EnemyFarState : public ObjState<Enemy>
	{
		EnemyFarState() {}
	public:
		static shared_ptr<EnemyFarState> Instance();
		virtual void Enter(const shared_ptr<Enemy>& Obj)override;
		virtual void Execute(const shared_ptr<Enemy>& Obj)override;
		virtual void Exit(const shared_ptr<Enemy>& Obj)override;
	};

	//--------------------------------------------------------------------------------------
	//	 プレイヤーから近いときの移動
	//--------------------------------------------------------------------------------------
	class EnemyNearState : public ObjState<Enemy>
	{
		EnemyNearState() {}
	public:
		static shared_ptr<EnemyNearState> Instance();
		virtual void Enter(const shared_ptr<Enemy>& Obj)override;
		virtual void Execute(const shared_ptr<Enemy>& Obj)override;
		virtual void Exit(const shared_ptr<Enemy>& Obj)override;
	};


	class LookOn{
		bool lookon;
	public :
		void SetLook(bool ptrlook) {
			lookon = ptrlook;
		}
		bool GetLook() {
			return lookon;
		}
		wstring ToString() {
			if (lookon) {
				return L"true";
			}
			else {
				return L"false";
			}
		}
	};

	//--------------------------------------------------------------------------------------
	//	パスを巡回する配置オブジェクト
	//--------------------------------------------------------------------------------------
	class FollowPathObject : public Enemy, public LookOn {
		Vec3 m_TagePos;
		Vec3 m_StrPos;
		Vec3 m_ParentPtr;
		Vec3 m_Poor;//差
	public:
		//構築と破棄
		FollowPathObject(const shared_ptr<Stage>& StagePtr, const Vec3& StartPos, const Vec3& TagePos);
		virtual ~FollowPathObject();
		//初期化
		virtual void OnCreate() override;
		//操作
		virtual void NearBehavior() override;
		virtual void FarBehavior() override;
		virtual void OnUpdate2() override;
		void DebagMesse();
		Vec3 GetPos() {
			auto pos = GetComponent<Transform>()->GetPosition();
			return pos;
		}
		Vec3 GetRot() {
			auto rot = GetComponent<Transform>()->GetRotation();
			return rot;
		}

	};


	class EnemyEye : public GameObject, public LookOn {
		Vec3 m_StartPos;
		Vec3 m_Rot;
		const shared_ptr<GameObject>& m_ParentPtr;
	public : 
		EnemyEye(const shared_ptr<Stage>& StagePtr, const Vec3& StartPos, const Vec3& Rot, const shared_ptr<GameObject>& ParentPtr);
		virtual ~EnemyEye();
		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other) override;
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};
}
//end basecross
