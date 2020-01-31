/*!
@file Character.h
@brief �L�����N�^�[�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	//--------------------------------------------------------------------------------------
	///	�V�[�\�[
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
	///	�V�[�\�[�̎�
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
	///	�v���C���[���i�܂Ȃ��悤�ɋz�����߂̓����蔻��
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
	///	�Œ�I�u�W�F�N�g
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
	//�@�^�C�����O����Œ�̃{�b�N�X
	//--------------------------------------------------------------------------------------
	class TilingFixedBox : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
		float m_UPic;
		float m_VPic;
		wstring m_Texname;
	public:
		//�\�z�Ɣj��
		TilingFixedBox(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position,
			float UPic,
			float VPic,
			const wstring& Texname
		);
		virtual ~TilingFixedBox();
		//������
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		//����
		virtual void OnCollisionEnter(shared_ptr<GameObject>&ptrObj)override;
		virtual void OnCollisionExcute(shared_ptr<GameObject>&ptrObj)override;
	};
}
//end basecross
