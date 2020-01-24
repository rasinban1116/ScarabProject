/*!
@file Character.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	//--------------------------------------------------------------------------------------
	///	シーソー
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
	///	シーソーの軸
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
	///	プレイヤーが進まないように吸うための当たり判定
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
	///	固定オブジェクト
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
	///	物理計算する固定の斜めボックス
	//--------------------------------------------------------------------------------------
	class SlopeFixedBox : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
		float m_UPic;
		float m_VPic;
		wstring m_Texname;
	public:
		//構築と破棄
		SlopeFixedBox(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position,
			float UPic,
			float VPic,
			const wstring& Texname
		);
		virtual ~SlopeFixedBox();
		//初期化
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		//操作
		virtual void OnCollisionEnter(shared_ptr<GameObject>&ptrObj)override;
		virtual void OnCollisionExcute(shared_ptr<GameObject>&ptrObj)override;
	};

	//--------------------------------------------------------------------------------------
	//　タイリングする固定のボックス
	//--------------------------------------------------------------------------------------
	class TilingFixedBox : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
		float m_UPic;
		float m_VPic;
		wstring m_Texname;
	public:
		//構築と破棄
		TilingFixedBox(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position,
			float UPic,
			float VPic,
			const wstring& Texname
		);
		virtual ~TilingFixedBox();
		//初期化
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		//操作
		virtual void OnCollisionEnter(shared_ptr<GameObject>&ptrObj)override;
		virtual void OnCollisionExcute(shared_ptr<GameObject>&ptrObj)override;
	};


	

	//--------------------------------------------------------------------------------------
	//　球体のカメラマン
	//--------------------------------------------------------------------------------------
	class Cameraman : public GameObject {
		float m_ToPlayerLen;
	public:
		//構築と破棄
		Cameraman(const shared_ptr<Stage>& StagePtr,
			float ToPlayerLen
		);
		virtual ~Cameraman();
		//初期化
		virtual void OnCreate() override;
		//操作
		virtual void OnUpdate() override;
	};


	//--------------------------------------------------------------------------------------
	//　オープニングカメラマン
	//--------------------------------------------------------------------------------------
	class OpeningCameraman : public GameObject {
		Vec3 m_StartPos;
		Vec3 m_EndPos;
		Vec3 m_AtStartPos;
		Vec3 m_AtEndPos;
		Vec3 m_AtPos;
		float m_TotalTime;
		//ステートマシーン
		unique_ptr< StateMachine<OpeningCameraman> >  m_StateMachine;
	public:
		//構築と破棄
		OpeningCameraman(const shared_ptr<Stage>& StagePtr);
		virtual ~OpeningCameraman();
		//初期化
		virtual void OnCreate() override;
		//操作
		virtual void OnUpdate() override;
		//アクセサ
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
