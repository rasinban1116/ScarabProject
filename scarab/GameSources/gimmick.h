/*!
@file gimmick.h
@brief　プロジェクトで使用するギミック類
*/

#pragma once
#include "stdafx.h"

namespace basecross {
//--------------------------------------------------------------------------------------
///	うんコイン
//--------------------------------------------------------------------------------------
	class GimmickObj : public GameObject {
		Vec3 m_Scale;
		Quat m_Qt;
		Vec3 m_Position;
		float Score;

	public:
		//構築と破棄
		GimmickObj(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Quat& Qt,
			const Vec3& Position
		);
		virtual ~GimmickObj();
		//初期化
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		virtual void OnCollisionEnter(shared_ptr<GameObject>&Other)override;
		float GetScore();
	};

	class UIDraw : public GameObject {
		void ScoreDraw();
	public:
		//構築
		UIDraw(const shared_ptr<Stage>&StagePtr);
		virtual ~UIDraw();
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		virtual void OnUpdate2()override;
		

	};
}
//end basecross
