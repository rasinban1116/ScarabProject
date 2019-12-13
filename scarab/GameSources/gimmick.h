/*!
@file gimmick.h
@brief　プロジェクトで使用するギミック類
*/

#pragma once
#include "stdafx.h"

namespace basecross {
//--------------------------------------------------------------------------------------
///	UI全般の表示
//--------------------------------------------------------------------------------------

	class UIDraw : public GameObject {

		void ScoreDraw();
	public:
		//構築
		UIDraw(const shared_ptr<Stage>&StagePtr);
		virtual ~UIDraw();
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		virtual void OnUpdate2()override;
		static void SetScore(float);
		static float GetScore();
	private:
		static float Score;
	};

//--------------------------------------------------------------------------------------
///	うんコイン
//--------------------------------------------------------------------------------------
	class GimmickObj : public GameObject {
		Vec3 m_Scale;
		Quat m_Qt;
		Vec3 m_Position;

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
		virtual void OnCollisionExit(shared_ptr<GameObject> &Other)override;
		
	};



//--------------------------------------------------------------------------------------
///	ステージクリア条件オブジェクト
//--------------------------------------------------------------------------------------
	class StageClearObj : public GameObject{
		Vec3 m_Position;
		Vec3 m_Scele;

	public:
		StageClearObj(const shared_ptr<Stage>&StagePtr,
			const Vec3 &Posion,
			const Vec3 &Scale	
		);
		virtual ~StageClearObj();
		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		virtual void OnCollisionEnter(shared_ptr<GameObject>&StagePtr);
	};



//--------------------------------------------------------------------------------------
///	ステージセレクトオブジェクト
//--------------------------------------------------------------------------------------
	class StageSrectObj : public GameObject {
		Vec3 m_Position;
		Vec3 m_Scele;

	public:
		StageSrectObj(const shared_ptr<Stage>&StagePtr,
			const Vec3 &Posion,
			const Vec3 &Scale
		);
		virtual ~StageSrectObj();
		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		virtual void OnCollisionEnter(shared_ptr<GameObject>&StagePtr);
	};

	class SkyObj : public GameObject {
		Vec3 m_Scale;
		Quat m_Qt;
		Vec3 m_Position;
	public:
		//構築と破棄
		SkyObj(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Quat& Qt,
			const Vec3& Position
		);
		virtual ~SkyObj();

		virtual void OnCreate();
	};

}
//end basecross
