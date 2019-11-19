/*!
@file Player.h
@brief プレイヤーなど
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	//--------------------------------------------------------------------------------------
	///	プレイヤー
	//--------------------------------------------------------------------------------------
	class Player : public GameObject {
	//プレイヤーに必要な各変数
		float m_Speed;    //プレイヤーのスピード
		float m_Scale;    //プレイヤーの大きさ（直径）
		Vec3 m_PlayVelo;  //プレイヤーの速度ベクトル
		bool active;      //プレイヤーが隠れているかどうか
		bool isGrand;

		
		
	//プレイヤーの動きに必要な関数
		void DrawStrings(); //文字列の表示
		InputHandler<Player> m_InputHandler;	//入力ハンドラー
		Vec2 GetInputState() const;				//プレイヤーが使用するコントロールとキーボード
		void RotToHead(const Vec3& Velocity, float LerpFact);		//回転の向きを進行方向にする
		void Move();							//プレイヤーの動き
		void ChangeTrans();                     //トランスフォームへの設定
		
	
	public:
		//構築と破棄
		//--------------------------------------------------------------------------------------
		/*!
		@brief	コンストラクタ
		@param[in]	StagePtr	ステージ
		*/
		//--------------------------------------------------------------------------------------
		Player(const shared_ptr<Stage>& StagePtr);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	デストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual ~Player() {}
		//アクセサ
		//初期化
		virtual void OnCreate() override;
		//更新
		virtual void OnUpdate() override;
		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other) override;
		virtual void OnCollisionExit(shared_ptr<GameObject>& Other) override;
		//virtual void OnCollisionStay(shared_ptr<GameObject>&Other) override;

		//後更新
		virtual void OnUpdate2() override;
		//Aボタンハンドラ
		void OnPushA();
		//Bボタンハンドラ
		void OnPushB();
		Vec3 GetMoveVector()const;				//進行方向を得る
	};
	//--------------------------------------------------------------------------------------
	//	プレイヤーの追従オブジェクト
	//--------------------------------------------------------------------------------------

	class PlayerChild : public GameObject{
		//ステートマシーン
		unique_ptr< StateMachine<PlayerChild> >  m_StateMachine;
		Vec3 m_StartPos;
		float m_StateChangeSize;
		InputHandler<PlayerChild> m_InputHandler;
		//フォース
		Vec3 m_Force;
		//速度
		Vec3 m_Velocity;
		//アクティブ判定
		bool active;
	public:
		//構築と破棄
		PlayerChild(const shared_ptr<Stage>& StagePtr, const Vec3& StartPos);
		virtual ~PlayerChild();
		//初期化
		virtual void OnCreate() override;
		//アクセサ
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
		//操作
		virtual void OnUpdate() override;
		//Aボタンハンドラ
		void OnPushA();
		//Bボタンハンドラ
		void OnPushB();
	};

	//--------------------------------------------------------------------------------------
	//	class SeekFarState : public ObjState<PlayerChild>;
	//	用途: プレイヤーから遠いときの移動
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
	//	用途: プレイヤーから近いときの移動
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
//	用途: プレイヤーについている時の行動
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

