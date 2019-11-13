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
		//文字列の表示
		void DrawStrings();
		//入力ハンドラー
		InputHandler<Player> m_InputHandler;
		//進行方向を得る
		Vec3 GetMoveVector() const;
		//プレイヤーが使用するコントロールとキーボード
		Vec2 GetInputState() const;
		//回転の向きを進行方向にする
		void RotToHead(const Vec3& Velocity, float LerpFact);
		//スケーリング（直径の大きさ）
		float m_Scale;
		//プレイヤーの動き
		void Move();
		//隠れているかどうかの判定
		bool active;
		//プレイヤーのスピード
		float m_Speed;
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

