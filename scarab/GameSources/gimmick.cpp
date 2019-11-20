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
	UIDraw::UIDraw(const shared_ptr<Stage>&Stageptr) :
		GameObject(Stageptr)
	{
	}

	void UIDraw::OnCreate(){
		//�����������
		auto ptrString = AddComponent<StringSprite>();
		ptrString->SetText(L"");
		ptrString->SetTextRect(Rect2D<float>(16.0f, 16.0f, 640.0f, 480.0f));
	}

	void UIDraw::OnUpdate() {

	}

	void UIDraw::OnUpdate2() {

	}

	void UIDraw::ScoreDraw() {
		float score=1;
		auto Coin = GetComponent<GimmickObj>();
		wstring Scoreptr(L"Position:\t");
		Scoreptr += L"X=" + Util::FloatToWStr(score, 3, Util::FloatModify::Fixed) + L",\t";

		wstring str = Scoreptr;
		//�����������
		auto ptrString = GetComponent<StringSprite>();
		ptrString->SetText(str);
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

	GimmickObj::~GimmickObj() {}
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
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		ptrDraw->SetOwnShadowActive(true);
		ptrDraw->SetTextureResource(L"H_TX");

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
		auto play = Other->GetStage()->GetSharedObject(L"Player", true);
		if (play) {
			Score += 100.0f;
		}	
	}
	float GimmickObj::GetScore() {
		return Score;
	}


}
//end basecross

