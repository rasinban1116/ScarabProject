/*!
@file Character.cpp
@brief �L�����N�^�[�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	///	�V�[�\�[
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
		//OBB�Փ�j�����t����
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetAfterCollision(AfterCollision::None);

		PsBoxParam param(ptrtrans->GetWorldMatrix(), 100.0, true, PsMotionType::MotionTypeFixed);
		auto ptrPs = AddComponent<RigidbodyBox>(param);
		
		//ptrColl->AddExcludeCollisionTag(L"Grand");
		auto gra = AddComponent<Gravity>();

		//�e�p�t�H�[�}���X�𓾂�
		GetStage()->SetCollisionPerformanceActive(true);
		GetStage()->SetUpdatePerformanceActive(true);
		GetStage()->SetDrawPerformanceActive(true);

		//�e������
		auto ptrShadow = AddComponent<Shadowmap>();
		ptrShadow->SetMeshResource(L"DEFAULT_CUBE");
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetFogEnabled(true);
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		ptrDraw->SetOwnShadowActive(true);
		ptrDraw->SetTextureResource(L"SERECT_TX");

		SetAlphaActive(true);

		//���ɂȂ�I�u�W�F�N�g
		//GetStage()->AddGameObject<SeesawAxis>(m_Position, m_Scale, GetThis<GameObject>());

		//�E�̓����蔻��
		GetStage()->AddGameObject<SeesawBox>(Vec3(m_Position.x + m_Scale.x * 0.5f,
			m_Position.y + 0.5f,
			m_Position.z),
			Vec3(0.2f, 0.5f, m_Scale.z), 2, GetThis<GameObject>());

		//���̓����蔻��
		GetStage()->AddGameObject<SeesawBox>(Vec3(m_Position.x - m_Scale.x * 0.5f,
			m_Position.y + 0.5f,
			m_Position.z),
			Vec3(0.2f, 0.5f, m_Scale.z), 0, GetThis<GameObject>());

		//���ʂ̓����蔻��
		GetStage()->AddGameObject<SeesawBox>(Vec3(m_Position.x,
			m_Position.y + 0.5f,
			m_Position.z + m_Scale.z * 0.5f),
			Vec3(m_Scale.x, 0.5f, 0.2f), 1, GetThis<GameObject>());
	}

	void Seesaw::OnUpdate() {
	}

	//--------------------------------------------------------------------------------------
	///	�V�[�\�[�̎�
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

		//OBB�Փ�j�����t����
		auto ptrCol = AddComponent <CollisionCapsule> ();
		//ptrColl->AddExcludeCollisionTag(L"Grand");
		//auto gira = AddComponent<Gravity>();
		ptrCol->AddExcludeCollisionTag(L"Seesaw");

		//�e�p�t�H�[�}���X�𓾂�
		GetStage()->SetCollisionPerformanceActive(true);
		GetStage()->SetUpdatePerformanceActive(true);
		GetStage()->SetDrawPerformanceActive(true);

		//�e������
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
	///	�V�[�\�[�̓����蔻��
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

		//OBB�Փ�j�����t����
		//auto ptrCol = AddComponent<CollisionObb>();

		//OBB�Փ�j�����t����
		auto ptrColl = AddComponent<CollisionObb>();
		//ptrColl->SetAfterCollision(AfterCollision::None);

		PsBoxParam param(ptrtrans->GetWorldMatrix(), 100.0, true, PsMotionType::MotionTypeFixed);
		auto ptrPs = AddComponent<RigidbodyBox>(param);

		//ptrColl->AddExcludeCollisionTag(L"Grand");
		//auto gira = AddComponent<Gravity>();
		ptrColl->AddExcludeCollisionTag(L"Seesaw");

		//�e�p�t�H�[�}���X�𓾂�
		GetStage()->SetCollisionPerformanceActive(true);
		GetStage()->SetUpdatePerformanceActive(true);
		GetStage()->SetDrawPerformanceActive(true);

		//�e������
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
			//�ʒu�̐ݒ�
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
			//�t���O��false�������瓖���蔻�������
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
///	�Œ�̃I�u�W�F�N�g
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
		//OBB�Փ�j�����t����
		auto ptrColl = AddComponent<CollisionObb>();;
		//ptrColl->AddExcludeCollisionTag(L"Grand");
		auto gira = AddComponent<Gravity>();

		//�e�p�t�H�[�}���X�𓾂�
		GetStage()->SetCollisionPerformanceActive(true);
		GetStage()->SetUpdatePerformanceActive(true);
		GetStage()->SetDrawPerformanceActive(true);

		//�e������
		auto ptrShadow = AddComponent<Shadowmap>();
		ptrShadow->SetMeshResource(L"DEFAULT_CUBE");
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetFogEnabled(true);
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		ptrDraw->SetOwnShadowActive(true);
		ptrDraw->SetTextureResource(L"SERECT_TX");
		//�����v�Z�{�b�N�X
		PsBoxParam param(ptrtrans->GetWorldMatrix(), 0.0f, true, PsMotionType::MotionTypeFixed);
		auto PsPtr = AddComponent<RigidbodyBox>(param);
		SetAlphaActive(true);


	}
	void FixedBox::OnUpdate() {

	}
	void FixedBox::OnCollisionEnter(shared_ptr<GameObject>&Other) {
		

		
	}



	//--------------------------------------------------------------------------------------
	//�@�^�C�����O����Œ�̃{�b�N�X
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
	//������
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
		//�`��R���|�[�l���g�̒ǉ�
		auto PtrDraw = AddComponent<BcPNTStaticDraw>();
		//�`��R���|�[�l���g�Ɍ`��i���b�V���j��ݒ�
		PtrDraw->CreateOriginalMesh(vertices, indices);
		PtrDraw->SetOriginalMeshUse(true);
		PtrDraw->SetFogEnabled(true);
		//�����ɉe���f�肱�ނ悤�ɂ���
		PtrDraw->SetOwnShadowActive(true);
		//�`��R���|�[�l���g�e�N�X�`���̐ݒ�
		PtrDraw->SetTextureResource(m_Texname);
		//�^�C�����O�ݒ�
		PtrDraw->SetSamplerState(SamplerState::LinearWrap);
		//�����v�Z�{�b�N�X
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
