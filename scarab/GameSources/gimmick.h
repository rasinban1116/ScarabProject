/*!
@file gimmick.h
@brief�@�v���W�F�N�g�Ŏg�p����M�~�b�N��
*/

#pragma once
#include "stdafx.h"

namespace basecross {
//--------------------------------------------------------------------------------------
///	UI�S�ʂ̕\��
//--------------------------------------------------------------------------------------

	class UIDraw : public GameObject {

		void ScoreDraw();
	public:
		//�\�z
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
///	����R�C��
//--------------------------------------------------------------------------------------
	class GimmickObj : public GameObject {
		Vec3 m_Scale;
		Quat m_Qt;
		Vec3 m_Position;

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
		virtual void OnCollisionExit(shared_ptr<GameObject> &Other)override;
		
	};



//--------------------------------------------------------------------------------------
///	�X�e�[�W�N���A�����I�u�W�F�N�g
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
///	�X�e�[�W�Z���N�g�I�u�W�F�N�g
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
		//�\�z�Ɣj��
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
