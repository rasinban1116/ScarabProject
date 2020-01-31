/*!
@file Character.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	//--------------------------------------------------------------------------------------
	///	シーソー
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
	///	シーソーの軸
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
	///	プレイヤーが進まないように吸うための当たり判定
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
	///	固定オブジェクト
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
	//　タイリングする固定のボックス
	//--------------------------------------------------------------------------------------
	class TilingFixedBox : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
		float m_UPic;
		float m_VPic;
		wstring m_Texname;
	public:
		//構築と破棄
		TilingFixedBox(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position,
			float UPic,
			float VPic,
			const wstring& Texname
		);
		virtual ~TilingFixedBox();
		//初期化
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		//操作
		virtual void OnCollisionEnter(shared_ptr<GameObject>&ptrObj)override;
		virtual void OnCollisionExcute(shared_ptr<GameObject>&ptrObj)override;
	};
}
//end basecross
