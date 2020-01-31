#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	敵本体
	//--------------------------------------------------------------------------------------
	Enemy::Enemy(const shared_ptr<Stage>& StagePtr, const Vec3& StartPos, const Vec3& TagePos,const int& size, 
		const wstring ptrtex, wstring ptrmodel) :
		GameObject(StagePtr),
		m_StrPos(StartPos),
		m_TagePos(TagePos),
		m_StateChangeSize(5.0f),
		m_Force(0),
		m_Velocity(0),
		size(size),
		tex(ptrtex),
		model(ptrmodel)
	{
	}
	Enemy::~Enemy() {}

	void Enemy::ApplyForce() {
		float elapsedTime = App::GetApp()->GetElapsedTime();
		m_Velocity += m_Force * elapsedTime;
		auto ptrTrans = GetComponent<Transform>();
		auto pos = ptrTrans->GetPosition();
		pos += (m_Velocity.normalize() * elapsedTime) * 3.f;
		ptrTrans->SetPosition(pos);
	}

	//ゲームステージからプレイヤーをとってくる
	shared_ptr<GameObject>  Enemy::GetTarget()const {
		return GetStage()->GetSharedObject(L"Player");
	}

	//初期化
	void Enemy::OnCreate() {
		//視界の初期化
		m_lookflg = false;
		m_atkflg = false;

		AddTag(L"Enemy");

		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetPosition(m_StrPos);
		Vec3 ptrSca;
		float modelSize;
		if (model == L"Enemy") {
			ptrSca = Vec3(0.8f, 0.8f, 1.0f);
			modelSize = 0.35f;
		}
		if (model == L"Lizad") {
			ptrSca = Vec3(1.f, 1.f, 2.5f);
			modelSize = 0.3f;
		}
		ptrTrans->SetScale(ptrSca);
		ptrTrans->SetRotation(0.0f, 0.0f, 0.0f);


		//オブジェクトのグループを得る
		auto group = GetStage()->GetSharedObjectGroup(L"EnemyGroup");
		//グループに自分自身を追加
		group->IntoGroup(GetThis<Enemy>());
		//分離行動をつける
		auto ptrSep = GetBehavior<SeparationSteering>();
		ptrSep->SetGameObjectGroup(group);
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
		m_StateMachine->ChangeState(LookOfState::Instance());


		//CollisionSphere衝突判定を付ける
		auto ptrColl = AddComponent<CollisionObb>();
		
		ptrColl->SetDrawActive(false);
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
		auto ptrDraw = AddComponent<PNTBoneModelDraw>();
		Mat4x4 spanMat;
		spanMat.affineTransformation(
			Vec3(Vec3(1.0f) / ptrSca  * modelSize),
			Vec3(0, 0, 0),
			Vec3(0, 3.0f, 0),
			Vec3(0, -0.5f, 0)
		);

		//描画するメッシュを設定
		switch (size)
		{
		case 1:
			ptrDraw->SetMeshResource(model);
			ptrDraw->SetTextureResource(tex);
			ptrDraw->AddAnimation(model,0,60,true,30);
			ptrDraw->ChangeCurrentAnimation(model,0);
			ptrDraw->SetMeshToTransformMatrix(spanMat);
			break;
		case 2:

			ptrDraw->SetMultiMeshResource(L"scrab");
			ptrDraw->SetTextureResource(L"Lizad_TX");
			ptrDraw->AddAnimation(L"Lizad", 0, 60, true, 30);
			ptrDraw->ChangeCurrentAnimation(L"Lizad", 0);
			break;
		}

		//◤◢◤◢◤◢◤プレイヤーの視界になるオブジェクトを作る◢◤◢◤◢◤ ◢
		auto enemyeye = GetStage()->AddGameObject<EnemyEye>(m_StrPos, GetThis<GameObject>());
	}

	//更新
	void Enemy::OnUpdate() {
		m_Force = Vec3(0);
		////共通のステアリング1
		auto ptrWall = GetBehavior<WallAvoidanceSteering>();
		m_Force += ptrWall->Execute(m_Force, GetVelocity());
		//ステートマシンのUpdateを行う
		//この中でステートの切り替えが行われる
		m_StateMachine->Update();

		if (m_atkflg == false) {
			//共通のステアリング2
			auto ptrSep = GetBehavior<SeparationSteering>();
			m_Force += ptrSep->Execute(m_Force);
			auto ptrAvoidance = GetBehavior<ObstacleAvoidanceSteering>();

			m_Force += ptrAvoidance->Execute(m_Force, GetVelocity());
			ApplyForce();
			auto ptrUtil = GetBehavior<UtilBehavior>();
			ptrUtil->RotToHead(1.0f);

			auto ptrDraw = GetComponent<PNTBoneModelDraw>();
			auto unko = App::GetApp()->GetElapsedTime();
			ptrDraw->UpdateAnimation(unko);
		}
	}

	void Enemy::OnCollisionEnter(shared_ptr<GameObject>& Other) {
		if (Other->FindTag(L"Player")) {
			m_atkflg = true;
		}
		if (Other->FindTag(L"UnkoBoll")) {
			m_atkflg = true;
		}
	}


	//--------------------------------------------------------------------------------------
	//	プレイヤーを探しているとき
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

		//m_lookflgがtrueになった時ステートマシーンを切り替える
		if (Obj->GetLook() == true) {
			Obj->GetStateMachine()->ChangeState(LookOnState::Instance());
		}
	}
	void LookOfState::Exit(const shared_ptr<Enemy>& Obj) {
	}

	//--------------------------------------------------------------------------------------
	//	プレイヤーを見つけているとき
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

		//自分とプレイヤーの距離が一定以上になった時ステートマシーンを切り替える
		if (f >= Obj->GetStateChangeSize() * 1.5f) {
			Obj->GetStateMachine()->ChangeState(LookOfState::Instance());
		}
		if (Obj->GetAtkFkg() == true) {
			Obj->GetStateMachine()->ChangeState(AtkAfterState::Instance());
		}
	}
	void LookOnState::Exit(const shared_ptr<Enemy>& Obj) {
		//切り替わるときにm_lookflgをfalseにしておく
		Obj->SetLook(false);
	}

	//--------------------------------------------------------------------------------------
	//	何もしないとき
	//--------------------------------------------------------------------------------------
	shared_ptr<AtkAfterState> AtkAfterState::Instance() {
		static shared_ptr<AtkAfterState> instance(new AtkAfterState);
		return instance;
	}
	void AtkAfterState::Enter(const shared_ptr<Enemy>& Obj) {
		time = 0;
	}
	void AtkAfterState::Execute(const shared_ptr<Enemy>& Obj) {

		auto etime = App::GetApp()->GetElapsedTime();
		time += etime;
		if (time > 5.0f) {
			Obj->GetStateMachine()->ChangeState(LookOfState::Instance());
		}
	}
	void AtkAfterState::Exit(const shared_ptr<Enemy>& Obj) {
		time = 0;
		Obj->SetAtkFlg(false);
	}

	//--------------------------------------------------------------------------------------
	//	エネミーの視界
	//--------------------------------------------------------------------------------------
	EnemyEye::EnemyEye(const shared_ptr<Stage>& StagePtr, const Vec3& StartPos, const shared_ptr<GameObject>& ParentPtr) :
		GameObject(StagePtr),
		m_StartPos(StartPos),
		m_ParentPtr(ParentPtr) {}

	EnemyEye::~EnemyEye() {}

	void EnemyEye::OnCreate() {
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(1.5f, 0.5, 5.0f);
		ptrTrans->SetParent(m_ParentPtr);

		AddTag(L"EnemyEye");

		//コリジョンをつける
		auto col = AddComponent<CollisionObb>();
		col->SetAfterCollision(AfterCollision::None);
		col->AddExcludeCollisionTag(L"Ground");
		col->SetDrawActive(false);

		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetFogEnabled(true);

		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		ptrDraw->SetOwnShadowActive(false);
		ptrDraw->SetDrawActive(false);
		SetAlphaActive(false);
	}


	void EnemyEye::OnUpdate() {
		auto eyecomp = this->GetComponent<Transform>();
		eyecomp->SetPosition(0, 0, 2.5f);
	}

	void EnemyEye::OnCollisionEnter(shared_ptr<GameObject>& Other) {
		if (Other->FindTag(L"Player")) {
			auto parentEnemy = dynamic_pointer_cast<Enemy>(GetComponent<Transform>()->GetParent());
			if (parentEnemy) {
				parentEnemy->SetLook(true);
			}
		}
	}
}