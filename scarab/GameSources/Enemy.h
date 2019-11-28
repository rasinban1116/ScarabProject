/*!
@file ProjectShader.h
@brief プロジェクトで使用するシェーダー
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	class Enemy_Low : public GameObject {
		Vec3 m_Scale; //大きさ
		Vec3 m_Pos; //位置
		float m_Speed; //動くスピード
		float m_SeekSpeed;
		Vec3 m_playerPos; //プレイヤーの位置
		Vec3 m_targetPos; //目的地
		Vec3 m_strPos; //最初の位置

		bool m_walkflg;//巡回する場所にいるかどうか

		Vec3 p_balance;// プレイヤーとの距離

		int horizoncase;//どの行動を行わせるか


		int m_vertical;//左右どちらに進むか
		int m_side; //上下どちらに進むか
		int m_strvertical;
		int m_strside;
		float m_initial; //差の設定
		float s_balance; //横の差
		float v_balance; //縦の差
		int s_case; //どっちからどっちに進むか
		int v_case;
		bool moveflag; //UpDateで一回だけやるやつ
		int m_spin; //スタートの位置
		int spin_case; //どちら周りか

	public : 
		Enemy_Low(const shared_ptr<Stage>& StagePtr, 
			const Vec3& Scale,
			const Vec3& strPos,
			const Vec3& tagePos);
		virtual ~Enemy_Low();
		//初期化
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		virtual void OnUpdate2() override;
		void SetState();
		void MoveChange();
		void Seek();
		void Walk();
		void Horizon();
		float m_sqrt(float s);
	};
	



	//class Enemy_Horizon : public Enemy_Low {
	//		Vec3 m_Scale;
	//		Quat m_Qt;
	//		Vec3 m_Position;
	//	public:
	//		//構築と破棄
	//		Enemy_Horizon(const shared_ptr<Stage>& StagePtr,
	//			const Vec3& Scale,
	//			const Quat& Qt,
	//			const Vec3& Position
	//		);
	//		virtual ~Enemy_Horizon();
	//		//初期化
	//		virtual void OnCreate() override;
	//		virtual void OnUpdate() override;
	//};
}
//end basecross

