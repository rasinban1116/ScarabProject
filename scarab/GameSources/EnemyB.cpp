/*!
@file Character.cpp
@brief �L�����N�^�[�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{

	//--------------------------------------------------------------------------------------
	//	�z�u�����I�u�W�F�N�g�̐e
	//--------------------------------------------------------------------------------------
//�\�z�Ɣj��
	Enemy::Enemy(const shared_ptr<Stage>& StagePtr, const Vec3& StartPos) :
		GameObject(StagePtr),
		m_StartPos(StartPos),
		m_StateChangeSize(5.0f),
		m_Force(0),
		m_Velocity(0)
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

	shared_ptr<GameObject>  Enemy::GetTarget()const {
		return GetStage()->GetSharedObject(L"Player");
	}

	//������
	void Enemy::OnCreate() {
		//�I�u�W�F�N�g�̃O���[�v�𓾂�
		auto group = GetStage()->GetSharedObjectGroup(L"Enemy_LowGroup");
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
		m_StateMachine->ChangeState(EnemyFarState::Instance());

	}

	//�X�V
	void Enemy::OnUpdate() {
		m_Force = Vec3(0);
		//���ʂ̃X�e�A�����O1
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
	//	�v���C���[���牓���Ƃ��̈ړ�
	//--------------------------------------------------------------------------------------
	shared_ptr<EnemyFarState> EnemyFarState::Instance() {
		static shared_ptr<EnemyFarState> instance(new EnemyFarState);
		return instance;
	}
	void EnemyFarState::Enter(const shared_ptr<Enemy>& Obj) {
	}
	void EnemyFarState::Execute(const shared_ptr<Enemy>& Obj) {
		Obj->FarBehavior();
	}

	void EnemyFarState::Exit(const shared_ptr<Enemy>& Obj) {
	}

	//--------------------------------------------------------------------------------------
	//	�v���C���[����߂��Ƃ��̈ړ�
	//--------------------------------------------------------------------------------------
	shared_ptr<EnemyNearState> EnemyNearState::Instance() {
		static shared_ptr<EnemyNearState> instance(new EnemyNearState);
		return instance;
	}
	void EnemyNearState::Enter(const shared_ptr<Enemy>& Obj) {
	}
	void EnemyNearState::Execute(const shared_ptr<Enemy>& Obj) {
		Obj->NearBehavior();
	}
	void EnemyNearState::Exit(const shared_ptr<Enemy>& Obj) {
	}


	//--------------------------------------------------------------------------------------
	//	�p�X�����񂷂�z�u�I�u�W�F�N�g
	//--------------------------------------------------------------------------------------
	//�\�z�Ɣj��
	FollowPathObject::FollowPathObject(const shared_ptr<Stage>& StagePtr, const Vec3& StartPos, const Vec3&TagePos) :
		Enemy(StagePtr, StartPos),
		m_TagePos(TagePos)
	{
	}
	FollowPathObject::~FollowPathObject() {}
	//������
	void FollowPathObject::OnCreate() {
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetPosition(GetStartPos());
		ptrTrans->SetScale(0.25f, 0.25f, 0.25f);
		ptrTrans->SetRotation(0.0f, 0.0f, 0.0f);
		m_StrPos = GetStartPos();
		AddTag(L"FollowPathObject");
		LookOn::SetLook(false);
		//�I�u�W�F�N�g�̃O���[�v�𓾂�
		auto group = GetStage()->GetSharedObjectGroup(L"Enemy_LowGroup");
		//�O���[�v�Ɏ������g��ǉ�
		group->IntoGroup(GetThis<Enemy>());
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
		ptrDraw->SetMeshResource(L"DEFAULT_SPHERE");
		ptrDraw->SetFogEnabled(true);
		//�`�悷��e�N�X�`����ݒ�
		//ptrDraw->SetTextureResource(L"CHECKER_TX");
		//�e�N���X��OnCreate���Ă�
		Enemy::OnCreate();

		auto enemyeye = GetStage()->AddGameObject<EnemyEye>(GetPos(), GetRot(),GetThis<GameObject>());

		auto a = AddComponent<StringSprite>();
		a->SetText(L"");
		a->SetTextRect(Rect2D<float>(16.,16.,640.,480.));
	}

	//����
	void FollowPathObject::NearBehavior() {
		auto ptrArrive = GetBehavior<ArriveSteering>();
		auto ptrTrans = GetComponent<Transform>();
		auto ptrPlayerTrans = GetTarget()->GetComponent<Transform>();
		auto force = GetForce();
		force += ptrArrive->Execute(force, GetVelocity(), ptrPlayerTrans->GetPosition());
		SetForce(force);
		float f = bsm::length(ptrPlayerTrans->GetPosition() - ptrTrans->GetPosition());
		if (f > GetStateChangeSize()) {
			GetStateMachine()->ChangeState(EnemyFarState::Instance());
		}

	}
	
	void FollowPathObject::FarBehavior() {
		auto ptrFollowPath = GetBehavior<FollowPathSteering>();
		auto ptrTrans = GetComponent<Transform>();
		auto ptrPlayerTrans = GetTarget()->GetComponent<Transform>();
		auto force = GetForce();
		force += ptrFollowPath->Execute(force, GetVelocity());
		SetForce(force);
		float f = bsm::length(ptrPlayerTrans->GetPosition() - ptrTrans->GetPosition());
		//if (f <= GetStateChangeSize()) {
		//	GetStateMachine()->ChangeState(EnemyNearState::Instance());
		//}
		if (LookOn::GetLook() == true) {
			GetStateMachine()->ChangeState(EnemyNearState::Instance());
		}
	}

	void FollowPathObject::DebagMesse() {
		
		wstring mase(L"�f�o�b�N");
		mase += LookOn::ToString();

		auto ptrstring = GetComponent<StringSprite>();
		ptrstring->SetText(mase);
	}

	void FollowPathObject::OnUpdate2() {
		DebagMesse();
	}

	EnemyEye::EnemyEye(const shared_ptr<Stage>& StagePtr, const Vec3& StartPos, const Vec3& Rot, const shared_ptr<GameObject>& ParentPtr) :
		GameObject(StagePtr),m_StartPos(StartPos),m_Rot(Rot),m_ParentPtr(ParentPtr){}

	EnemyEye::~EnemyEye(){}

	void EnemyEye::OnCreate() {
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(0.7f, 0.5, 1.5f);
		ptrTrans->SetParent(m_ParentPtr);

		AddTag(L"EnemyEye");

		//�R���W����������
		auto col = AddComponent<CollisionObb>();
		//col->SetAfterCollision(AfterCollision::None);
		//col->SetDrawActive(true);

		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetFogEnabled(true);

		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		ptrDraw->SetOwnShadowActive(false);
		SetDrawActive(true);


		SetAlphaActive(false);

	}

	void EnemyEye::OnCollisionEnter(shared_ptr<GameObject>& Other) {
		auto objvec = GetStage()->GetGameObjectVec();
		for (auto& v : objvec) {
			auto ptrPlayer = dynamic_pointer_cast<Player>(v);
			if (ptrPlayer) {
				auto colSphere = ptrPlayer->GetComponent<CollisionSphere>(false);
				if (colSphere) {
					Vec3 ret;
					auto colSphere = ptrPlayer->GetComponent<CollisionSphere>()->GetSphere();
					auto colObb = GetComponent<CollisionObb>()->GetObb();
					//HitTest�ŏՓ˔���
					if (HitTest::SPHERE_OBB(colSphere, colObb, ret)) {
						LookOn::SetLook(true);
					}
				}
			}
		}
	}

	void EnemyEye::OnUpdate() {
			auto eyecomp = this->GetComponent<Transform>();
			eyecomp->SetPosition(0,0,0.8f);
	}
}
//end basecross
