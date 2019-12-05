#include "stdafx.h"
#include "Project.h"

namespace basecross {
	Enemy::Enemy(const shared_ptr<Stage>& StagePtr, const Vec3& StartPos, const Vec3& TagePos,const int& size) :
		GameObject(StagePtr),
		m_StrPos(StartPos),
		m_TagePos(TagePos),
		m_StateChangeSize(5.0f),
		m_Force(0),
		m_Velocity(0),
		size(size)
	{
	}
	Enemy::~Enemy() {}

	void Enemy::ApplyForce() {
		float elapsedTime = App::GetApp()->GetElapsedTime();
		m_Velocity += m_Force * elapsedTime;
		auto ptrTrans = GetComponent<Transform>();
		auto pos = ptrTrans->GetPosition();
		pos += (m_Velocity.normalize() * elapsedTime);
		ptrTrans->SetPosition(pos);
	}

	//�Q�[���X�e�[�W����v���C���[���Ƃ��Ă���
	shared_ptr<GameObject>  Enemy::GetTarget()const {
		return GetStage()->GetSharedObject(L"Player");
	}

	//������
	void Enemy::OnCreate() {
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetPosition(m_StrPos);
		ptrTrans->SetScale(0.25f, 0.25f, 0.25f);
		ptrTrans->SetRotation(0.0f, 0.0f, 0.0f);

		//���E�̏�����
		LookFlg::SetLook(false);
		//�I�u�W�F�N�g�̃O���[�v�𓾂�
		auto group = GetStage()->GetSharedObjectGroup(L"EnemyGroup");
		//�O���[�v�Ɏ������g��ǉ�
		group->IntoGroup(GetThis<Enemy>());
		//�����s��������
		auto ptrSep = GetBehavior<SeparationSteering>();
		ptrSep->SetGameObjectGroup(group);
		//�ǉ���s����t����
		auto ptrWall = GetBehavior<WallAvoidanceSteering>();
		vector<PLANE> planeVec = {
			{
				Vec3(20,0,0),
				Vec3(20,1.0,0),
				Vec3(20,0,-1.0),
			},
			{
				Vec3(0,0,-20),
				Vec3(0,1.0,-20),
				Vec3(-1.0,0,-20),
			},
			{
				Vec3(-20,0,0),
				Vec3(-20,1.0,0),
				Vec3(-20,0,1.0),
			},
			{
				Vec3(0,0,20),
				Vec3(0,1.0,20),
				Vec3(1.0,0,20),
			},
		};
		ptrWall->SetPlaneVec(planeVec);
		//��Q������s����t����
		vector<shared_ptr<GameObject>> spObjVec;
		GetStage()->GetUsedTagObjectVec(L"FixedSphere", spObjVec);
		vector<SPHERE> spVec;
		for (auto& v : spObjVec) {
			auto TransPtr = v->GetComponent<Transform>();
			SPHERE sp;
			sp.m_Center = TransPtr->GetPosition();
			sp.m_Radius = TransPtr->GetScale().x * 0.5f;
			spVec.push_back(sp);
		}
		auto ptrAvoidance = GetBehavior<ObstacleAvoidanceSteering>();
		ptrAvoidance->SetObstacleSphereVec(spVec);
		//�X�e�[�g�}�V���̍\�z
		m_StateMachine.reset(new StateMachine<Enemy>(GetThis<Enemy>()));
		//�ŏ��̃X�e�[�g��SeekEnemyFarState�ɐݒ�
		m_StateMachine->ChangeState(LookOfState::Instance());



		//CollisionSphere�Փ˔����t����
		auto ptrColl = AddComponent<CollisionSphere>();
		//�d�͂�����
		auto ptrGra = AddComponent<Gravity>();
		//�o�H�����t����
		auto ptrFollowPath = GetBehavior<FollowPathSteering>();
		list<Vec3> pathList = {
			Vec3(m_StrPos.x,0.125, m_StrPos.z),
			Vec3(m_StrPos.x,0.125,m_TagePos.z),
			Vec3(m_TagePos.x,0.125,m_TagePos.z),
			Vec3(m_TagePos.x,0.125,m_StrPos.z),
		};
		ptrFollowPath->SetPathList(pathList);
		ptrFollowPath->SetLooped(true);
		//�e������i�V���h�E�}�b�v��`�悷��j
		auto ptrShadow = AddComponent<Shadowmap>();
		//�e�̌`�i���b�V���j��ݒ�
		ptrShadow->SetMeshResource(L"DEFAULT_CUBE");

		//�`��R���|�[�l���g�̐ݒ�
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		//�`�悷�郁�b�V����ݒ�
		switch (size)
		{
		case 1:
			ptrDraw->SetMeshResource(L"enemy");
			ptrDraw->SetTextureResource(L"KUSA_TX");
			ptrDraw->SetFogEnabled(true);
			break;
		case 2:
			ptrDraw->SetMeshResource(L"liz");
			ptrDraw->SetFogEnabled(true);
		}

		//�`�悷��e�N�X�`����ݒ�


		//�v���C���[�̎��E�ɂȂ�I�u�W�F�N�g�����
		//auto enemyeye = GetStage()->AddGameObject<EnemyEye>(m_StrPos, GetThis<GameObject>());


	}

	//�X�V
	void Enemy::OnUpdate() {
		m_Force = Vec3(0);
		////���ʂ̃X�e�A�����O1
		auto ptrWall = GetBehavior<WallAvoidanceSteering>();
		m_Force += ptrWall->Execute(m_Force, GetVelocity());
		//�X�e�[�g�}�V����Update���s��
		//���̒��ŃX�e�[�g�̐؂�ւ����s����
		m_StateMachine->Update();
		
		//���ʂ̃X�e�A�����O2
		auto ptrSep = GetBehavior<SeparationSteering>();
		m_Force += ptrSep->Execute(m_Force);
		auto ptrAvoidance = GetBehavior<ObstacleAvoidanceSteering>();
		m_Force += ptrAvoidance->Execute(m_Force, GetVelocity());
		ApplyForce();
		auto ptrUtil = GetBehavior<UtilBehavior>();
		ptrUtil->RotToHead(1.0f);
	}


	//--------------------------------------------------------------------------------------
//	�v���C���[��T���Ă���Ƃ�
//--------------------------------------------------------------------------------------
	shared_ptr<LookOfState> LookOfState::Instance() {
		static shared_ptr<LookOfState> instance(new LookOfState);
		return instance;
	}
	void LookOfState::Enter(const shared_ptr<Enemy>& Obj) {
	}
	void LookOfState::Execute(const shared_ptr<Enemy>& Obj) {
		auto ptrFollowPath = Obj->GetBehavior<FollowPathSteering>();
		auto force = Obj->GetForce();
		auto ptrPlayerTrans = Obj->GetTarget()->GetComponent<Transform>();
		force += ptrFollowPath->Execute(force, Obj->GetVelocity());
		Obj->SetForce(force);
		float f = bsm::length(ptrPlayerTrans->GetPosition() - Obj->GetComponent<Transform>()->GetPosition());
		if (f < Obj->GetStateChangeSize()) {
			Obj->GetStateMachine()->ChangeState(LookOnState::Instance());
		}
		//if (Obj->LookFlg::GetLook() == true) {
		//	Obj->GetStateMachine()->ChangeState(LookOnState::Instance());
		//}
	}
	void LookOfState::Exit(const shared_ptr<Enemy>& Obj) {
	}

	//--------------------------------------------------------------------------------------
	//	�v���C���[�������Ă���Ƃ�
	//--------------------------------------------------------------------------------------
	shared_ptr<LookOnState> LookOnState::Instance() {
		static shared_ptr<LookOnState> instance(new LookOnState);
		return instance;
	}
	void LookOnState::Enter(const shared_ptr<Enemy>& Obj) {
	}
	void LookOnState::Execute(const shared_ptr<Enemy>& Obj) {
		auto ptrArrive = Obj->GetBehavior<SeekSteering>();
		auto ptrSep = Obj->GetBehavior<SeparationSteering>();
		auto force = Obj->GetForce();
		auto ptrPlayerTrans = Obj->GetTarget()->GetComponent<Transform>();
		force += ptrArrive->Execute(force, Obj->GetVelocity(), ptrPlayerTrans->GetPosition());
		Obj->SetForce(force);
		float f = bsm::length(ptrPlayerTrans->GetPosition() - Obj->GetComponent<Transform>()->GetPosition());
		if (f >= Obj->GetStateChangeSize()) {
			Obj->GetStateMachine()->ChangeState(LookOfState::Instance());
		}
	}
	void LookOnState::Exit(const shared_ptr<Enemy>& Obj) {
	}

	EnemyEye::EnemyEye(const shared_ptr<Stage>& StagePtr, const Vec3& StartPos, const shared_ptr<GameObject>& ParentPtr) :
		GameObject(StagePtr),
		m_StartPos(StartPos),
		m_ParentPtr(ParentPtr) {}

	EnemyEye::~EnemyEye() {}

	void EnemyEye::OnCreate() {
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(0.7f, 0.5, 1.5f);
		ptrTrans->SetParent(m_ParentPtr);

		AddTag(L"EnemyEye");

		//�R���W����������
		auto col = AddComponent<CollisionObb>();
		col->SetAfterCollision(AfterCollision::None);
		col->SetDrawActive(true);
		col->AddExcludeCollisionTag(L"Ground");

		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetFogEnabled(true);

		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		ptrDraw->SetOwnShadowActive(false);
		SetDrawActive(true);


		SetAlphaActive(false);

	}


	void EnemyEye::OnUpdate() {
		auto eyecomp = this->GetComponent<Transform>();
		eyecomp->SetPosition(0, 0, 0.7f);

		auto a = AddComponent<StringSprite>();
		a->SetText(L"");
		a->SetFontColor(bsm::Col4(0, 0, 0, 10));
		a->SetTextRect(Rect2D<float>(16., 16., 640., 480.));
		DebagMesse();
	}


	void EnemyEye::DebagMesse() {
		wstring mase(L"�f�o�b�N");
		mase += LookFlg::ToString();

		auto ptrstring = GetComponent<StringSprite>();
		ptrstring->SetText(mase);
	}


	void EnemyEye::OnCollisionEnter(shared_ptr<GameObject>& Other) {
		if (Other->FindTag(L"Player")) {
			LookFlg::SetLook(true);
		}
	}
}