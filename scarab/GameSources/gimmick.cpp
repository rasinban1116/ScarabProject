/*!
@file gimmick.cpp
@brief �v���W�F�N�g�Ŏg�p����M�~�b�N����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
//--------------------------------------------------------------------------------------
///	UI	
//--------------------------------------------------------------------------------------
	
	float UIDraw::Score;
	UIDraw::UIDraw(const shared_ptr<Stage>&Stageptr) :
		GameObject(Stageptr)	
	{
	}

	UIDraw::~UIDraw(){}
	void UIDraw::OnCreate(){
		Score = 0;
		//�����������
		auto ptrString = AddComponent<StringSprite>();
		ptrString->SetText(L"");
		ptrString->SetTextRect(Rect2D<float>(16.0f, 16.0f, 640.0f, 480.0f));
	}

	void UIDraw::OnUpdate() {
		//ScoreDraw();
	}

	void UIDraw::OnUpdate2() {

	}

	void UIDraw::ScoreDraw() {
		wstring Scoreptr(L"SCORE:\t");
		Scoreptr += Util::FloatToWStr(Score, 1, Util::FloatModify::Fixed) + L",\t";
		auto fps = App::GetApp()->GetStepTimer().GetFramesPerSecond();
		//wstring strFps(L"FPS: ");
		//strFps += Util::UintToWStr(fps);
		//strFps += L"\nElapsedTime: ";
		//wstring str = Scoreptr;
		//�����������
		auto ptrString = GetComponent<StringSprite>();
		ptrString->SetText(Scoreptr);
	}
	void UIDraw::SetScore(float x) {
		Score += x;

	}


//--------------------------------------------------------------------------------------
///	����R�C��	
//--------------------------------------------------------------------------------------
	//�\�z�Ɣj��
	GimmickObj::GimmickObj(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Quat& Qt,
		const Vec3& Position
	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Qt(Qt),
		m_Position(Position)
	{}

	GimmickObj::~GimmickObj() {
		OnDestroy();
	}
	//������
	void GimmickObj::OnCreate() {

		auto ptrTrans = GetComponent<Transform>();
		AddTag(L"Slope");

		ptrTrans->SetScale(m_Scale);
		ptrTrans->SetQuaternion(m_Qt);
		ptrTrans->SetPosition(m_Position);

		//OBB�Փ�j�����t����
		auto ptrColl = AddComponent<CollisionObb>();;
		//�e�p�t�H�[�}���X�𓾂�
		GetStage()->SetCollisionPerformanceActive(true);
		GetStage()->SetUpdatePerformanceActive(true);
		GetStage()->SetDrawPerformanceActive(true);

		//�e������
		auto ptrShadow = AddComponent<Shadowmap>();
		ptrShadow->SetMeshResource(L"DEFAULT_CUBE");
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetFogEnabled(true);
		ptrDraw->SetMeshResource(L"unko");
		ptrDraw->SetOwnShadowActive(true);
		ptrDraw->SetTextureResource(L"UNKO_TX");

		//�A�N�V�����̓o�^
		auto PtrAction = AddComponent<Action>();
		PtrAction->AddRotateBy(1.0f, Vec3(0,5,0));
		//���[�v����
		PtrAction->SetLooped(true);
		//�A�N�V�����J�n
		PtrAction->Run();
	}

	void GimmickObj::OnUpdate() {
	}

	void GimmickObj::OnCollisionEnter(shared_ptr<GameObject>&Other) {	
		auto play =Other->GetStage()->GetSharedGameObject<Player>(L"Player", true);
		auto UI = Other->GetStage()->GetSharedGameObject<UIDraw>(L"UI", true);
		if (play&&UI) {
			SetUpdateActive(false);
			SetDrawActive(false);
			UI->SetScore(100.0f);
		}	
	}

	void GimmickObj::OnCollisionExit(shared_ptr<GameObject>&Other) {
	}

//--------------------------------------------------------------------------------------
///	�Q�[�����N���A�n�_��ݒ肷��I�u�W�F�N�g�i����͂��邪�����ɂ���\��j
///���m�F�̂��߃I�u�W�F�N�g���������Ă���
//--------------------------------------------------------------------------------------

	StageClearObj::StageClearObj(const shared_ptr<Stage>&StagePtr,
		const Vec3 &Position,
		const Vec3 &Scale
	) :
		GameObject(StagePtr),
		m_Position(Position),
		m_Scele(Scale)
	{}
	StageClearObj::~StageClearObj() {

	}
	void StageClearObj::OnCreate() {
		auto ptrtrans = AddComponent<Transform>();
		ptrtrans->SetPosition(m_Position);
		ptrtrans->SetScale(m_Scele);
		//OBB�Փ�j�����t����
		auto ptrColl = AddComponent<CollisionObb>();;

		//auto gira = AddComponent<Gravity>();

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
		ptrDraw->SetTextureResource(L"Cl_TX");
		ptrDraw->SetDrawActive(false);
		//�����v�Z�{�b�N�X
		PsBoxParam param(ptrtrans->GetWorldMatrix(), 0.0f, true, PsMotionType::MotionTypeFixed);
		auto PsPtr = AddComponent<RigidbodyBox>(param);
		//�����I��Transform��ݒ肷��t���O�͖���
		PsPtr->SetAutoTransform(false);
	}
	void StageClearObj::OnUpdate() {

	}
	void StageClearObj::OnCollisionEnter(shared_ptr<GameObject>&Other) {
		auto play = Other->GetStage()->GetSharedObject(L"Player", true);
		auto ptrScene = App::GetApp()->GetScene<Scene>();
		if (play) {
			PostEvent(0.0f, GetThis<ObjectInterface>(), ptrScene, L"ToGmaeStage");
		}
	}

//--------------------------------------------------------------------------------------
///	�X�e�[�W�Z���N�g�p�I�u�W�F�N�g
//--------------------------------------------------------------------------------------

	StageSrectObj::StageSrectObj(const shared_ptr<Stage>&StagePtr,
		const Vec3 &Position,
		const Vec3 &Scale
	) :
		GameObject(StagePtr),
		m_Position(Position),
		m_Scele(Scale)
	{}
	StageSrectObj::~StageSrectObj() {

	}
	void StageSrectObj::OnCreate() {
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
		ptrDraw->SetTextureResource(L"Cl_TX");
		//auto drawcomp = AddComponent<PNTStaticModelDraw>();
		//Mat4x4 spanMat;
		//spanMat.affineTransformation(
		//	Vec3(0.5f),
		//	Vec3(90,0,0),
		//	Vec3(0),
		//	Vec3(0, -0.5f, 0)
		//);
		//drawcomp->SetMeshToTransformMatrix(spanMat);
		//drawcomp->SetMeshResource(L"Base");
		//drawcomp->SetTextureResource(L"UNKO_TX");
		SetAlphaActive(true);
	

	}
	void StageSrectObj::OnUpdate() {

	}
	void StageSrectObj::OnCollisionEnter(shared_ptr<GameObject>&Other) {
		auto play = Other->GetStage()->GetSharedGameObject<Player>(L"Player", true);
		auto ptrScene = App::GetApp()->GetScene<Scene>();

		if (Other->FindTag(L"Player")) {
			PostEvent(0.0f, GetThis<ObjectInterface>(), ptrScene, L"ToGameStage");
		}
		else {
			
		}

	}

	SkyObj::SkyObj(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Quat& Qt,
		const Vec3& Position
	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Qt(Qt),
		m_Position(Position)
	{}

	SkyObj::~SkyObj() {}
	//������
	void SkyObj::OnCreate() {

		auto ptrTrans = GetComponent<Transform>();
		//AddTag(L"Slope");

		ptrTrans->SetScale(m_Scale);
		ptrTrans->SetQuaternion(m_Qt);
		ptrTrans->SetPosition(m_Position);

		GetStage()->SetCollisionPerformanceActive(true);
		GetStage()->SetUpdatePerformanceActive(true);
		GetStage()->SetDrawPerformanceActive(true);

		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		//ptrDraw->SetFogEnabled(true);

		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		ptrDraw->SetOwnShadowActive(true);
		ptrDraw->SetTextureResource(L"SKY_TX");
	}
}
//end basecross

