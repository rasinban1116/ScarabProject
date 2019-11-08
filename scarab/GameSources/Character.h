/*!
@file Character.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"

namespace basecross{


	//--------------------------------------------------------------------------------------
	///	物理計算する固定のボックス
	//--------------------------------------------------------------------------------------
	class FixedPsBox : public GameObject {
		Vec3 m_Scale;
		Quat m_Qt;
		Vec3 m_Position;
	public:
		//構築と破棄
		FixedPsBox(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Quat& Qt,
			const Vec3& Position
		);
		virtual ~FixedPsBox();
		//初期化
		virtual void OnCreate() override;
	};

	//--------------------------------------------------------------------------------------
	//	class FixedBox : public GameObject;
	//--------------------------------------------------------------------------------------
	class FixedBox : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
	public:
		//構築と破棄
		FixedBox(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position
		);
		virtual ~FixedBox();
		//初期化
		virtual void OnCreate() override;
		//操作
	};



	//--------------------------------------------------------------------------------------
	//	追いかける配置オブジェクト
	//--------------------------------------------------------------------------------------

	class SeekObject : public GameObject {
		//ステートマシーン
		unique_ptr< StateMachine<SeekObject> >  m_StateMachine;
		Vec3 m_StartPos;
		float m_StateChangeSize;
		//フォース
		Vec3 m_Force;
		//速度
		Vec3 m_Velocity;
	public:
		//構築と破棄
		SeekObject(const shared_ptr<Stage>& StagePtr, const Vec3& StartPos);
		virtual ~SeekObject();
		//初期化
		virtual void OnCreate() override;
		//アクセサ
		const unique_ptr<StateMachine<SeekObject>>& GetStateMachine() {
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
		//操作
		virtual void OnUpdate() override;
	};

	//--------------------------------------------------------------------------------------
	//	class SeekFarState : public ObjState<SeekObject>;
	//	用途: プレイヤーから遠いときの移動
	//--------------------------------------------------------------------------------------
	class SeekFarState : public ObjState<SeekObject>
	{
		SeekFarState() {}
	public:
		static shared_ptr<SeekFarState> Instance();
		virtual void Enter(const shared_ptr<SeekObject>& Obj)override;
		virtual void Execute(const shared_ptr<SeekObject>& Obj)override;
		virtual void Exit(const shared_ptr<SeekObject>& Obj)override;
	};

	//--------------------------------------------------------------------------------------
	//	class SeekNearState : public ObjState<SeekObject>;
	//	用途: プレイヤーから近いときの移動
	//--------------------------------------------------------------------------------------
	class SeekNearState : public ObjState<SeekObject>
	{
		SeekNearState() {}
	public:
		static shared_ptr<SeekNearState> Instance();
		virtual void Enter(const shared_ptr<SeekObject>& Obj)override;
		virtual void Execute(const shared_ptr<SeekObject>& Obj)override;
		virtual void Exit(const shared_ptr<SeekObject>& Obj)override;
	};


	//--------------------------------------------------------------------------------------
	//	class MoveBox : public GameObject;
	//--------------------------------------------------------------------------------------
	class MoveBox : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
		Vec3 m_Velocity;
		float m_MaxVelocity;
		float m_MinVelocity;
		float m_Deceleration;
	public:
		//構築と破棄
		MoveBox(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position
		);
		virtual ~MoveBox();
		//初期化
		virtual void OnCreate() override;
		//操作
		virtual void OnUpdate() override;
		virtual void OnCollisionExcute(const CollisionPair& Pair) override;
		virtual void OnCollisionExit(const CollisionPair& Pair)override;
	};

	//--------------------------------------------------------------------------------------
	//	class MoveFixedBox : public GameObject;
	//--------------------------------------------------------------------------------------
	class MoveFixedBox : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
	public:
		//構築と破棄
		MoveFixedBox(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position
		);
		virtual ~MoveFixedBox();
		//初期化
		virtual void OnCreate() override;
		//操作
	};

	//--------------------------------------------------------------------------------------
	///	物理計算するアクティブな球体
	//--------------------------------------------------------------------------------------
	class ActivePsSphere : public GameObject {
		float m_Scale;
		Quat m_Qt;
		Vec3 m_Position;
	public:
		//構築と破棄
		ActivePsSphere(const shared_ptr<Stage>& StagePtr,
			float Scale,
			const Quat& Qt,
			const Vec3& Position
		);
		virtual ~ActivePsSphere();
		//初期化
		virtual void OnCreate() override;
	};


}
//end basecross
