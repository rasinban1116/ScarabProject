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

	//ゲームステージからプレイヤーをとってくる
	shared_ptr<GameObject>  Enemy::GetTarget()const {
		return GetStage()->GetSharedObject(L"Player");
	}

	//初期化
	void Enemy::OnCreate() {
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetPosition(m_StrPos);
		ptrTrans->SetScale(0.25f, 0.25f, 0.25f);
		ptrTrans->SetRotation(0.0f, 0.0f, 0.0f);

		//視界の初期化
		LookFlg::SetLook(false);
		//オブジェクトのグループを得る
		auto group = GetStage()->GetSharedObjectGroup(L"EnemyGroup");
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
		m_StateMachine->ChangeState(LookOfState::Instance());



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

		//描画するテクスチャを設定


		//プレイヤーの視界になるオブジェクトを作る
		//auto enemyeye = GetStage()->AddGameObject<EnemyEye>(m_StrPos, GetThis<GameObject>());


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

		//コリジョンをつける
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
		wstring mase(L"デバック");
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