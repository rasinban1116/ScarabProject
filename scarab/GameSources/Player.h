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
		Vec3 m_pos;       //プレイヤーのポジション
		bool active;      //プレイヤーが隠れているかどうか
		bool isGrand;

	
	//プレイヤーの動きに必要な関数
		void DrawStrings(); //文字列の表示
		InputHandler<Player> m_InputHandler;	//入力ハンドラー
		Vec3 GetMoveVector()const;				//進行方向を得る
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
		Player(const shared_ptr<Stage>& StagePtr,
			const Vec3 &Position);
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
		virtual void OnCollisionExcute(shared_ptr<GameObject>& Other) override;

		//後更新
		virtual void OnUpdate2() override;
		//Aボタンハンドラ
		void OnPushA();
		//Bボタンハンドラ
		void OnPushB();
		void OnPushDOWN(){}
		void OnPushUP(){}



	};

	//--------------------------------------------------------------------------------------
	//	糞玉
	//--------------------------------------------------------------------------------------
	class UnkoBoll : public Player {
		Vec3 UnkoPos;
		Vec3 UnkoScale;
		Vec3 UnkoRot;
		Vec3 UnkoVelo;

	
	public:
		//構築と破棄
		//--------------------------------------------------------------------------------------
		/*!
		@brief	コンストラクタ
		@param[in]	StagePtr	ステージ
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
		@brief	デストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual ~UnkoBoll() {}
		//アクセサ
		//初期化
		virtual void OnCreate() override;
		//更新
		virtual void OnUpdate() override;
		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other) override;
		virtual void OnCollisionExcute(shared_ptr<GameObject>&Other) override;
		virtual void OnCollisionExit(shared_ptr<GameObject>&Other) override;
		//後更新
		virtual void OnUpdate2() override;
		void Move();
		static float  ScaleUp();
		Vec3 holdon();
		bool active;
	
	};
	
};


//end basecross

