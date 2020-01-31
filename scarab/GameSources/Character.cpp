/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	///	シーソー
	//--------------------------------------------------------------------------------------
	Seesaw::Seesaw(const shared_ptr<Stage>& StagePtr, const Vec3& Position) :
		GameObject(StagePtr),
		m_Position(Position)
	{
	}

	void Seesaw::OnCreate() {
		m_flg = true;
		auto ptrtrans = AddComponent<Transform>();
		ptrtrans->SetPosition(m_Position);
		m_Scale = Vec3(2.0f, 0.05f, 5.0f);
		ptrtrans->SetScale(m_Scale);
		AddTag(L"Seesaw");
		//OBB衝突j判定を付ける
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetAfterCollision(AfterCollision::None);

		PsBoxParam param(ptrtrans->GetWorldMatrix(), 100.0, true, PsMotionType::MotionTypeFixed);
		auto ptrPs = AddComponent<RigidbodyBox>(param);
		
		//ptrColl->AddExcludeCollisionTag(L"Grand");
		auto gra = AddComponent<Gravity>();

		//各パフォーマンスを得る
		GetStage()->SetCollisionPerformanceActive(true);
		GetStage()->SetUpdatePerformanceActive(true);
		GetStage()->SetDrawPerformanceActive(true);

		//影をつける
		auto ptrShadow = AddComponent<Shadowmap>();
		ptrShadow->SetMeshResource(L"DEFAULT_CUBE");
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetFogEnabled(true);
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		ptrDraw->SetOwnShadowActive(true);
		ptrDraw->SetTextureResource(L"SERECT_TX");

		SetAlphaActive(true);

		//軸になるオブジェクト
		//GetStage()->AddGameObject<SeesawAxis>(m_Position, m_Scale, GetThis<GameObject>());

		//右の当たり判定
		GetStage()->AddGameObject<SeesawBox>(Vec3(m_Position.x + m_Scale.x * 0.5f,
			m_Position.y + 0.5f,
			m_Position.z),
			Vec3(0.2f, 0.5f, m_Scale.z), 2, GetThis<GameObject>());

		//左の当たり判定
		GetStage()->AddGameObject<SeesawBox>(Vec3(m_Position.x - m_Scale.x * 0.5f,
			m_Position.y + 0.5f,
			m_Position.z),
			Vec3(0.2f, 0.5f, m_Scale.z), 0, GetThis<GameObject>());

		//正面の当たり判定
		GetStage()->AddGameObject<SeesawBox>(Vec3(m_Position.x,
			m_Position.y + 0.5f,
			m_Position.z + m_Scale.z * 0.5f),
			Vec3(m_Scale.x, 0.5f, 0.2f), 1, GetThis<GameObject>());
	}

	void Seesaw::OnUpdate() {
	}

	//--------------------------------------------------------------------------------------
	///	シーソーの軸
	//--------------------------------------------------------------------------------------
	SeesawAxis::SeesawAxis(const shared_ptr<Stage>& StagePtr, const Vec3& Position,
		const Vec3& Scale, const shared_ptr<GameObject>& ParentPtr
	) :
		GameObject(StagePtr),
		m_Position(Position),
		m_Scale(Scale),
		m_ParentPtr(ParentPtr)
	{
	}

	void SeesawAxis::OnCreate() {
		auto ptrtrans = AddComponent<Transform>();
		ptrtrans->SetPosition(m_Position);
		ptrtrans->SetScale(m_Scale);
		ptrtrans->SetParent(m_ParentPtr);
		AddTag(L"Seesaw");

		//OBB衝突j判定を付ける
		auto ptrCol = AddComponent <CollisionCapsule> ();
		//ptrColl->AddExcludeCollisionTag(L"Grand");
		//auto gira = AddComponent<Gravity>();
		ptrCol->AddExcludeCollisionTag(L"Seesaw");

		//各パフォーマンスを得る
		GetStage()->SetCollisionPerformanceActive(true);
		GetStage()->SetUpdatePerformanceActive(true);
		GetStage()->SetDrawPerformanceActive(true);

		//影をつける
		auto ptrShadow = AddComponent<Shadowmap>();
		ptrShadow->SetMeshResource(L"DEFAULT_CAPSULE");
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetFogEnabled(true);
		ptrDraw->SetMeshResource(L"DEFAULT_CAPSULE");
		ptrDraw->SetOwnShadowActive(true);
		ptrDraw->SetTextureResource(L"SERECT_TX");

		SetAlphaActive(true);
	}

	void SeesawAxis::OnUpdate() {

	}

	//--------------------------------------------------------------------------------------
	///	シーソーの当たり判定
	//--------------------------------------------------------------------------------------
	SeesawBox::SeesawBox(const shared_ptr<Stage>& StagePtr, const Vec3& Position,
		const Vec3& Scale, const int& num, const shared_ptr<GameObject>& ParentPtr
	) :
		GameObject(StagePtr),
		m_Position(Position),
		m_Scale(Scale),
		boxnum(num),
		m_ParentPtr(ParentPtr)
	{
	}

	void SeesawBox::OnCreate(){
		auto ptrtrans = AddComponent<Transform>();
		ptrtrans->SetPosition(m_Position);
		ptrtrans->SetScale(m_Scale);
		ptrtrans->SetParent(m_ParentPtr);
		AddTag(L"Seesaw");

		//OBB衝突j判定を付ける
		//auto ptrCol = AddComponent<CollisionObb>();

		//OBB衝突j判定を付ける
		auto ptrColl = AddComponent<CollisionObb>();
		//ptrColl->SetAfterCollision(AfterCollision::None);

		PsBoxParam param(ptrtrans->GetWorldMatrix(), 100.0, true, PsMotionType::MotionTypeFixed);
		auto ptrPs = AddComponent<RigidbodyBox>(param);

		//ptrColl->AddExcludeCollisionTag(L"Grand");
		//auto gira = AddComponent<Gravity>();
		ptrColl->AddExcludeCollisionTag(L"Seesaw");

		//各パフォーマンスを得る
		GetStage()->SetCollisionPerformanceActive(true);
		GetStage()->SetUpdatePerformanceActive(true);
		GetStage()->SetDrawPerformanceActive(true);

		//影をつける
		auto ptrShadow = AddComponent<Shadowmap>();
		ptrShadow->SetMeshResource(L"DEFAULT_CUBE");
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetFogEnabled(true);
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		ptrDraw->SetOwnShadowActive(true);
		ptrDraw->SetTextureResource(L"SERECT_TX");

		SetAlphaActive(true);
	}

	void SeesawBox::OnUpdate(){
		auto ptrtrans = this->GetComponent<Transform>();
		Vec3 ptrPos;
		auto parentSeesaw = dynamic_pointer_cast<Seesaw>(GetComponent<Transform>()->GetParent());
		if (parentSeesaw) {
			//位置の設定
			Vec3 ptrparsca;
			ptrparsca = parentSeesaw->GetSca();
			switch (boxnum)
			{
			case 0:
				ptrPos = Vec3(-ptrparsca.x * 0.5f, m_Scale.y * 0.5f, 0.0f);
				break;
			case 1:
				ptrPos = Vec3(0.0f, m_Scale.y * 0.5f, ptrparsca.z * 0.5f);
				break;
			case 2:
				ptrPos = Vec3(ptrparsca.x * 0.5f, m_Scale.y * 0.5f, 0.0f);
				break;
			}
			//フラグがfalseだったら当たり判定を消す
			if (!parentSeesaw->GetFlg()) {
				GetStage()->SetCollisionPerformanceActive(false);
			}
		}
		ptrtrans->SetPosition(ptrPos);
	}

	void SeesawBox::OnCollisionEnter(shared_ptr<GameObject>& Other) {
		if (Other->FindTag(L"Ground")) {
			auto parentSeesaw = dynamic_pointer_cast<Seesaw>(GetComponent<Transform>()->GetParent());
			if (parentSeesaw) {
				parentSeesaw->SetFlg(false);
			}
		}
	}


//--------------------------------------------------------------------------------------
///	固定のオブジェクト
//--------------------------------------------------------------------------------------
	FixedBox::FixedBox(const shared_ptr<Stage>&StagePtr,
		const Vec3 &Position,
		const Vec3 &Scale
	) :
		GameObject(StagePtr),
		m_Position(Position),
		m_Scele(Scale)
	{}
	FixedBox::~FixedBox() {

	}
	void FixedBox::OnCreate() {
		auto ptrtrans = AddComponent<Transform>();
		ptrtrans->SetPosition(m_Position);
		ptrtrans->SetScale(m_Scele);
		//OBB衝突j判定を付ける
		auto ptrColl = AddComponent<CollisionObb>();;
		//ptrColl->AddExcludeCollisionTag(L"Grand");
		auto gira = AddComponent<Gravity>();

		//各パフォーマンスを得る
		GetStage()->SetCollisionPerformanceActive(true);
		GetStage()->SetUpdatePerformanceActive(true);
		GetStage()->SetDrawPerformanceActive(true);

		//影をつける
		auto ptrShadow = AddComponent<Shadowmap>();
		ptrShadow->SetMeshResource(L"DEFAULT_CUBE");
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetFogEnabled(true);
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		ptrDraw->SetOwnShadowActive(true);
		ptrDraw->SetTextureResource(L"SERECT_TX");
		//物理計算ボックス
		PsBoxParam param(ptrtrans->GetWorldMatrix(), 0.0f, true, PsMotionType::MotionTypeFixed);
		auto PsPtr = AddComponent<RigidbodyBox>(param);
		SetAlphaActive(true);


	}
	void FixedBox::OnUpdate() {

	}
	void FixedBox::OnCollisionEnter(shared_ptr<GameObject>&Other) {
		

		
	}



	//--------------------------------------------------------------------------------------
	//　タイリングする固定のボックス
	//--------------------------------------------------------------------------------------
	TilingFixedBox::TilingFixedBox(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Rotation,
		const Vec3& Position,
		float UPic,
		float VPic,
		const wstring& Texname
	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Position(Position),
		m_UPic(UPic),
		m_VPic(VPic),
		m_Texname(Texname)
	{}
	TilingFixedBox::~TilingFixedBox() {}
	//初期化
	void TilingFixedBox::OnCreate() {
		AddTag(L"Ground");
		auto PtrTrans = GetComponent<Transform>();
		PtrTrans->SetScale(m_Scale);
		PtrTrans->SetRotation(m_Rotation);
		PtrTrans->SetPosition(m_Position);
		auto Coll = AddComponent<CollisionObb>();
		Coll->SetSleepActive(true);
		Coll->SetFixed(true);

		vector<VertexPositionNormalTexture> vertices;
		vector<uint16_t> indices;
		MeshUtill::CreateCube(1.0f, vertices, indices);
		float UCount = m_Scale.x / m_UPic;
		float VCount = m_Scale.z / m_VPic;
		for (size_t i = 0; i < vertices.size(); i++) {
			if (vertices[i].textureCoordinate.x >= 1.0f) {
				vertices[i].textureCoordinate.x = UCount;
			}
			if (vertices[i].textureCoordinate.y >= 1.0f) {
				float FrontBetween = bsm::angleBetweenNormals(vertices[i].normal, Vec3(0, 1, 0));
				float BackBetween = bsm::angleBetweenNormals(vertices[i].normal, Vec3(0, -1, 0));
				if (FrontBetween < 0.01f || BackBetween < 0.01f) {
					vertices[i].textureCoordinate.y = VCount;
				}
			}
		}
		//描画コンポーネントの追加
		auto PtrDraw = AddComponent<BcPNTStaticDraw>();
		//描画コンポーネントに形状（メッシュ）を設定
		PtrDraw->CreateOriginalMesh(vertices, indices);
		PtrDraw->SetOriginalMeshUse(true);
		PtrDraw->SetFogEnabled(true);
		//自分に影が映りこむようにする
		PtrDraw->SetOwnShadowActive(true);
		//描画コンポーネントテクスチャの設定
		PtrDraw->SetTextureResource(m_Texname);
		//タイリング設定
		PtrDraw->SetSamplerState(SamplerState::LinearWrap);
		//物理計算ボックス
		PsBoxParam param(PtrTrans->GetWorldMatrix(), 0.0f, true, PsMotionType::MotionTypeFixed);
		auto PsPtr = AddComponent<RigidbodyBox>(param);
		PtrDraw->SetAlpha(true);
		SetAlphaActive(true);
		//PtrDraw->SetDrawActive(false);
		
	}

	void TilingFixedBox::OnUpdate() {
		auto ptrColl = GetComponent<CollisionObb>();
		auto ptrDraw = GetComponent<BcPNTStaticDraw>();
		ptrColl->SetSleepActive(true);
		if (ptrColl->IsSleep()) {
			ptrDraw->SetDiffuse(Col4(1.0f, 1.0f, 1.0f, 1.0f));
		}

	}

	void TilingFixedBox::OnCollisionEnter(shared_ptr<GameObject>&ptrObj){
		auto Play = ptrObj->GetStage()->GetSharedObject(L"Player", true);
		auto ptrColl = GetComponent<CollisionObb>();
		if (Play) {
			if (ptrColl->IsSleep()) {
				ptrColl->SetSleepActive(false);
			}
		}
	}
	void TilingFixedBox::OnCollisionExcute(shared_ptr<GameObject>&ptrObj) {

			
	}

}
//end basecross
