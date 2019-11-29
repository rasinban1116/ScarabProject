/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{

	//--------------------------------------------------------------------------------------
	//	配置されるオブジェクトの親
	//--------------------------------------------------------------------------------------
//構築と破棄
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

	//初期化
	void Enemy::OnCreate() {
		//オブジェクトのグループを得る
		auto group = GetStage()->GetSharedObjectGroup(L"Enemy_LowGroup");
		//グループに自分自身を追加
		group->IntoGroup(GetThis<Enemy>());
		//分離行動をつける
		auto ptrSep = GetBehavior<SeparationSteering>();
		ptrSep->SetGameObjectGroup(group);
		//壁回避行動を付ける
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
		//障害物回避行動を付ける
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
		//ステートマシンの構築
		m_StateMachine.reset(new StateMachine<Enemy>(GetThis<Enemy>()));
		//最初のステートをSeekEnemyFarStateに設定
		m_StateMachine->ChangeState(EnemyFarState::Instance());

	}

	//更新
	void Enemy::OnUpdate() {
		m_Force = Vec3(0);
		//共通のステアリング1
		auto ptrWall = GetBehavior<WallAvoidanceSteering>();
		m_Force += ptrWall->Execute(m_Force, GetVelocity());
		//ステートマシンのUpdateを行う
		//この中でステートの切り替えが行われる
		m_StateMachine->Update();
		//共通のステアリング2
		auto ptrSep = GetBehavior<SeparationSteering>();
		m_Force += ptrSep->Execute(m_Force);
		auto ptrAvoidance = GetBehavior<ObstacleAvoidanceSteering>();
		m_Force += ptrAvoidance->Execute(m_Force, GetVelocity());
		ApplyForce();
		auto ptrUtil = GetBehavior<UtilBehavior>();
		ptrUtil->RotToHead(1.0f);
	}



	//--------------------------------------------------------------------------------------
	//	プレイヤーから遠いときの移動
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
	//	プレイヤーから近いときの移動
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
	//	パスを巡回する配置オブジェクト
	//--------------------------------------------------------------------------------------
	//構築と破棄
	FollowPathObject::FollowPathObject(const shared_ptr<Stage>& StagePtr, const Vec3& StartPos, const Vec3&TagePos) :
		Enemy(StagePtr, StartPos),
		m_TagePos(TagePos)
	{
	}
	FollowPathObject::~FollowPathObject() {}
	//初期化
	void FollowPathObject::OnCreate() {
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetPosition(GetStartPos());
		ptrTrans->SetScale(0.25f, 0.25f, 0.25f);
		ptrTrans->SetRotation(0.0f, 0.0f, 0.0f);
		m_StrPos = GetStartPos();
		AddTag(L"FollowPathObject");
		LookOn::SetLook(false);
		//オブジェクトのグループを得る
		auto group = GetStage()->GetSharedObjectGroup(L"Enemy_LowGroup");
		//グループに自分自身を追加
		group->IntoGroup(GetThis<Enemy>());
		//CollisionSphere衝突判定を付ける
		auto ptrColl = AddComponent<CollisionSphere>();
		//重力をつける
		auto ptrGra = AddComponent<Gravity>();
		//経路巡回を付ける
		auto ptrFollowPath = GetBehavior<FollowPathSteering>();
		list<Vec3> pathList = {
			Vec3(m_StrPos.x,0.125, m_StrPos.z),
			Vec3(m_StrPos.x,0.125,m_TagePos.z),
			Vec3(m_TagePos.x,0.125,m_TagePos.z),
			Vec3(m_TagePos.x,0.125,m_StrPos.z),
		};
		ptrFollowPath->SetPathList(pathList);
		ptrFollowPath->SetLooped(true);
		//影をつける（シャドウマップを描画する）
		auto ptrShadow = AddComponent<Shadowmap>();
		//影の形（メッシュ）を設定
		ptrShadow->SetMeshResource(L"DEFAULT_CUBE");

		//描画コンポーネントの設定
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		//描画するメッシュを設定
		ptrDraw->SetMeshResource(L"DEFAULT_SPHERE");
		ptrDraw->SetFogEnabled(true);
		//描画するテクスチャを設定
		//ptrDraw->SetTextureResource(L"CHECKER_TX");
		//親クラスのOnCreateを呼ぶ
		Enemy::OnCreate();

		auto enemyeye = GetStage()->AddGameObject<EnemyEye>(GetPos(), GetRot(),GetThis<GameObject>());

		auto a = AddComponent<StringSprite>();
		a->SetText(L"");
		a->SetTextRect(Rect2D<float>(16.,16.,640.,480.));
	}

	//操作
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
		
		wstring mase(L"デバック");
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

		//コリジョンをつける
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
					//HitTestで衝突判定
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
