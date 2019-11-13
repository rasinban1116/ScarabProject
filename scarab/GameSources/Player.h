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
		
		
	//プレイヤーの動きに必要な関数
		void DrawStrings(); //文字列の表示
		InputHandler<Player> m_InputHandler;	//入力ハンドラー
		Vec3 GetMoveVector() const;				//進行方向を得る
		Vec2 GetInputState() const;				//プレイヤーが使用するコントロールとキーボード
		void RotToHead(const Vec3& Velocity, float LerpFact);		//回転の向きを進行方向にする
		void Move();							//プレイヤーの動き
	
	
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



	};
	
};


//end basecross

