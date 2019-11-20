/*!
@file gimmick.h
@brief�@�v���W�F�N�g�Ŏg�p����M�~�b�N��
*/

#pragma once
#include "stdafx.h"

namespace basecross {
//--------------------------------------------------------------------------------------
///	����R�C��
//--------------------------------------------------------------------------------------
	class GimmickObj : public GameObject {
		Vec3 m_Scale;
		Quat m_Qt;
		Vec3 m_Position;
		float Score;

	public:
		//�\�z�Ɣj��
		GimmickObj(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Quat& Qt,
			const Vec3& Position
		);
		virtual ~GimmickObj();
		//������
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		virtual void OnCollisionEnter(shared_ptr<GameObject>&Other)override;
		float GetScore();
	};

	class UIDraw : public GameObject {
		void ScoreDraw();
	public:
		//�\�z
		UIDraw(const shared_ptr<Stage>&StagePtr);
		virtual ~UIDraw();
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		virtual void OnUpdate2()override;
		

	};
}
//end basecross
