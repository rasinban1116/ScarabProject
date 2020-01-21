/*!
@file Player.cpp
@brief プレイヤーなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	class Player : public GameObject;
	//	用途: プレイヤー
	//--------------------------------------------------------------------------------------
	//構築
	Player::Player(const shared_ptr<Stage>& StagePtr,
		const Vec3 &Position
		) :
		GameObject(StagePtr),
		m_Scale(0.5f),
		active(true),
		isGrand(true),
		m_PlayVelo(0, 0, 0),
		m_Speed(50.0f),
		m_pos(Position)

	{}



	Vec2 Player::GetInputState() const {
		Vec2 ret;
		//コントローラの取得
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		ret.x = 0.0f;
		ret.y = 0.0f;
		WORD wButtons = 0;
		if (cntlVec[0].bConnected) {
			ret.x = cntlVec[0].fThumbLX;
			ret.y = cntlVec[0].fThumbLY;
		}
		//キーボードの取得(キーボード優先)
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
		if (KeyState.m_bPushKeyTbl['W']) {
			//前
			ret.y = 1.0f;
		}
		else if (KeyState.m_bPushKeyTbl['A']) {
			//左
			ret.x = -1.0f;
		}
		else if (KeyState.m_bPushKeyTbl['S']) {
			//後ろ
			ret.y = -1.0f;
		}
		else if (KeyState.m_bPushKeyTbl['D']) {
			//右
			ret.x = 1.0f;
		}
		return ret;
	}

	void Player::RotToHead(const Vec3& Velocity, float LerpFact) {
		if (LerpFact <= 0.0f) {
			//補間係数が0以下なら何もしない
			return;
		}
		auto ptrTransform = GetComponent<Transform>();
		//回転の更新
		if (Velocity.length() > 0.0f) {
			Vec3 temp = Velocity;
			temp.normalize();
			float toAngle = atan2(temp.x, temp.z);
			Quat qt;
			qt.rotationRollPitchYawFromVector(Vec3(0, toAngle, 0));
			qt.normalize();
			//現在の回転を取得
			Quat nowQt = ptrTransform->GetQuaternion();
			//現在と目標を補間
			if (LerpFact >= 1.0f) {
				nowQt = qt;
			}
			else {
				//クオータニオンの補間処理
				nowQt = XMQuaternionSlerp(nowQt, qt, LerpFact);
			}
			ptrTransform->SetQuaternion(nowQt);
		}
	}
	
	Vec3 Player::GetMoveVector()const {
		Vec3 angle(0, 0, 0);
		float RadXZ = 0.0f;
		//コントローラの取得
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		float fThumbLY = 0.0f;
		float fThumbLX = 0.0f;
		WORD wButtons = 0;
		if (cntlVec[0].bConnected) {
			fThumbLY = cntlVec[0].fThumbLY;
			fThumbLX = cntlVec[0].fThumbLX;
			wButtons = cntlVec[0].wButtons;
		}
		//キーボードの取得(キーボード優先)
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
		if (KeyState.m_bPushKeyTbl['W']) {
			//前
			fThumbLY = 1.0f;
		}
		else if (KeyState.m_bPushKeyTbl['A']) {
			//左
			fThumbLX = -1.0f;
			RadXZ += fThumbLX * App::GetApp()->GetElapsedTime() * m_Speed;
		}
		else if (KeyState.m_bPushKeyTbl['S']) {
			//後ろ
			fThumbLY = -1.0f;
		}
		else if (KeyState.m_bPushKeyTbl['D']) {
			//右
			fThumbLX = 1.0f;
			RadXZ += -fThumbLX * App::GetApp()->GetElapsedTime() * m_Speed;
		}
		
		if (fThumbLX != 0 || fThumbLY != 0) {
			float moveLength = 0;	//動いた時のスピード
			auto ptrTransform = GetComponent<Transform>();
			auto ptrCamera = OnGetDrawCamera();
			//進行方向の向きを計算
			auto front = ptrTransform->GetPosition() - ptrCamera->GetEye();
			front.y = 0;
			front.normalize();
			//進行方向向きからの角度を算出
			float frontAngle = atan2(front.z, front.x);
			//コントローラの向き計算
			float moveX = fThumbLX;
			float moveZ = fThumbLY;
			Vec2 moveVec(moveX, moveZ);
			float moveSize = moveVec.length();
			//コントローラの向きから角度を計算
			float cntlAngle = atan2(-moveX, moveZ);
			//トータルの角度を算出
			float totalAngle = frontAngle + cntlAngle;
			//角度からベクトルを作成
			angle = Vec3(cos(totalAngle), 0, sin(totalAngle));
			//正規化する
			angle.normalize();
			//移動サイズを設定。
			angle *= moveSize;
			//Y軸は変化させない
			angle.y = 0;
		}

		return angle;
	}



	//プレイヤーの動き
	void Player::Move() {
		//コントローラチェックして入力があればコマンド呼び出し
		auto vec = GetMoveVector();
		auto ptrPs = GetComponent<RigidbodySphere>();
		//m_PlayVelo = ptrPs->GetLinearVelocity();
		auto forces = GetComponent<Transform>();
		auto force = GetComponent<Rigidbody>();
		//xとzの速度を修正
		m_PlayVelo.x = vec.x * m_Speed;
		m_PlayVelo.z = vec.z * m_Speed;
		if (isGrand == false) {
			m_PlayVelo.y += -150.0f*App::GetApp()->GetElapsedTime();
		}
		//速度を設定
		auto forwrd = forces->GetForword();
		ptrPs->SetLinearVelocity(m_PlayVelo);
			m_PlayVelo = Vec3(0, 0, 0);

			auto drawcomp = GetComponent<PNTBoneModelDraw>();
			auto time = App::GetApp()->GetElapsedTime();
			drawcomp->UpdateAnimation(time);
	}

	void Player::ChangeTrans() {
		//RigidbodySphereからTransformへのパラメータの設定
		//自動的に設定はされない設定になっているので自分で行う
		auto ptrPs = GetComponent<RigidbodySphere>();
		auto ptrTrans = GetComponent<Transform>();
		//位置情報はそのまま設定
		ptrTrans->SetPosition(ptrPs->GetPosition());
		//回転の計算
		Vec3 angle = GetMoveVector();
		if (angle.length() > 0.0f) {
			//補間処理を行う回転。
			RotToHead(angle, 0.1f);
		}
	}

	//初期化
	void Player::OnCreate() {
		//初期位置などの設定
		auto ptrTrans = GetComponent<Transform>();
		//初期位置などの設定
		auto ptr = AddComponent<Transform>();
		ptr->SetScale(0.5f, 0.5f, 0.5f);	//直径25センチの球体
		ptr->SetRotation(-45.0f, 0.0f, 0.0f);
		ptr->SetPosition(m_pos);

		//CollisionSphere衝突判定を付ける
		auto ptrColl = AddComponent<CollisionSphere>();
		//ptrColl->SetDrawActive(true);
		//各パフォーマンスを得る
		GetStage()->SetCollisionPerformanceActive(true);
		GetStage()->SetUpdatePerformanceActive(true);
		GetStage()->SetDrawPerformanceActive(true);
		//重力をつける
		auto ptrGra = AddComponent<Gravity>();
		//WorldMatrixをもとにRigidbodySphereのパラメータを作成
		PsSphereParam param(ptrTrans->GetWorldMatrix(), 1.0f, false, PsMotionType::MotionTypeActive);
		//RigidbodySphereコンポーネントを追加
		auto psPtr = AddComponent<RigidbodySphere>(param);
		//自動的にTransformを設定するフラグは無し
		psPtr->SetAutoTransform(false);
		//文字列をつける
		auto ptrString = AddComponent<StringSprite>();
		ptrString->SetText(L"");
		ptrString->SetTextRect(Rect2D<float>(16.0f, 16.0f, 640.0f, 480.0f));
		//影をつける（シャドウマップを描画する）
		auto ptrShadow = AddComponent<Shadowmap>();
		//影の形（メッシュ）を設定
		ptrShadow->SetMeshResource(L"DEFAULT_SPHERE");
		//描画コンポーネントの設定
		SetAlphaActive(true);
		AddTag(L"Player");
		//透明処理
		SetAlphaActive(true);
		auto drawcomp = AddComponent<PNTBoneModelDraw>();
		Mat4x4 spanMat;
		spanMat.affineTransformation(
			Vec3(0.5f),
			Vec3(0),
			Vec3(0),
			Vec3(0,-0.5f,0)
		);
		drawcomp->SetMeshToTransformMatrix(spanMat);
		drawcomp->SetMultiMeshResource(L"scrab");
		drawcomp->SetTextureResource(L"KUSA_TX");
		drawcomp->AddAnimation(L"scrab", 0, 60, true, 30);
		drawcomp->ChangeCurrentAnimation(L"scrab", 0);
		



		auto ptrMyCamera = dynamic_pointer_cast<MyCamera>(OnGetDrawCamera());
		if (ptrMyCamera) {
			//MyCameraである
			//MyCameraに注目するオブジェクト（プレイヤー）の設定
			ptrMyCamera->SetTargetObject(GetThis<GameObject>());
			ptrMyCamera->SetTargetToAt(Vec3(0, 0.25f, 0));
		}
	}


	//更新
	void Player::OnUpdate() {
		m_InputHandler.PushHandle(GetThis<Player>());
		auto ptrGameStage = dynamic_pointer_cast<GameStage>(GetStage());
		if (this->GetStage() == ptrGameStage) {
			if (ptrGameStage->GetCameraSelect() == CameraSelect::openingCamera) {
				return;
			}
		}

		if (active) {
			Move();
		}

	}

	//後更新
	void Player::OnUpdate2() {
		ChangeTrans();
		//文字列の表示
		DrawStrings();
	}

	//Aボタンハンドラ
	void  Player::OnPushA() {
		active = false;	
	}


	//Bボタンハンドラ
	void  Player::OnPushB() {
		active = true;	
	}

	


	//コリジョンが何かに当たった時の処理
	void Player::OnCollisionEnter(shared_ptr<GameObject>& Other) {	
		if (Other->FindTag(L"Enemy")) {
			auto ptrScene = App::GetApp()->GetScene<Scene>();
			PostEvent(0.0f, GetThis<ObjectInterface>(), ptrScene, L"ToGameOverStage");
		}
		isGrand = true;
	}

	//コリジョンが何かから離れた時の処理
	void Player::OnCollisionExit(shared_ptr<GameObject>& Other) {
		isGrand = false;
	}

	//コリジョンが何かに当たっている時の処理
	void Player::OnCollisionExcute(shared_ptr<GameObject>&Other) {
		isGrand = true;
	}
	

	//文字列の表示
	void Player::DrawStrings() {

		//文字列表示
		wstring strMess(L"Bボタンで再読み込み\n");
		//オブジェクト数
		auto ObjCount = GetStage()->GetGameObjectVec().size();
		wstring  strObjCount(L"OBJ_COUNT: ");
		strObjCount += Util::SizeTToWStr(ObjCount);
		auto bodyCount = GetStage()->GetBasePhysics().GetNumBodies();
		strObjCount += L", BODY_COUNT: ";
		strObjCount += Util::SizeTToWStr(bodyCount);
		strObjCount += L"\n";
		auto fps = App::GetApp()->GetStepTimer().GetFramesPerSecond();
		wstring strFps(L"FPS: ");
		strFps += Util::UintToWStr(fps);
		strFps += L"\nElapsedTime: ";
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		strFps += Util::FloatToWStr(ElapsedTime);
		strFps += L"\n";

		auto pos = GetComponent<Transform>()->GetPosition();
		wstring strPos(L"Position:\t");
		strPos += L"X=" + Util::FloatToWStr(pos.x, 6, Util::FloatModify::Fixed) + L",\t";
		strPos += L"Y=" + Util::FloatToWStr(pos.y, 6, Util::FloatModify::Fixed) + L",\t";
		strPos += L"Z=" + Util::FloatToWStr(pos.z, 6, Util::FloatModify::Fixed) + L"\n";
		
		wstring boolact(L"isGrand");
		boolact +=  Util::FloatToWStr(isGrand);

		wstring str = strMess + strObjCount + strFps + strPos + boolact;
		//文字列をつける
		auto ptrString = GetComponent<StringSprite>();
		ptrString->SetText(str);
	}

//--------------------------------------------------------------------------------------
//	糞玉
//--------------------------------------------------------------------------------------
	UnkoBoll::UnkoBoll(const shared_ptr<Stage>&StagePtr,
		const Vec3 &Position,
		const Vec3 &Scale,
		const Vec3 &Rot,
		const Vec3 &Velocity
	):
		Player(StagePtr,Position),
		UnkoPos(Position),
		UnkoScale(Scale),
		UnkoRot(Rot),
		UnkoVelo(Velocity),
		active(true)
	{
	}


	void UnkoBoll::OnCreate() {
		auto ptrTrans = AddComponent<Transform>();

		ptrTrans->SetPosition(UnkoPos);
		ptrTrans->SetRotation(UnkoRot);
		ptrTrans->SetScale(UnkoScale);

		//OBB衝突j判定を付ける
		auto ptrColl = AddComponent<CollisionSphere>();

		ptrColl->SetDrawActive(true);

		//ptrColl->SetFixed(true);
		//各パフォーマンスを得る
		GetStage()->SetCollisionPerformanceActive(true);
		GetStage()->SetUpdatePerformanceActive(true);
		GetStage()->SetDrawPerformanceActive(true);

		//影をつける
		auto ShadowPtr = AddComponent<Shadowmap>();
		ShadowPtr->SetMeshResource(L"DEFAULT_SPHERE");

		auto PtrDraw = AddComponent<BcPNTStaticDraw>();
		PtrDraw->SetMeshResource(L"DEFAULT_SPHERE");
		PtrDraw->SetDrawActive(true);
		PtrDraw->SetTextureResource(L"POOP_TX");

		//WorldMatrixをもとにRigidbodySphereのパラメータを作成
		PsSphereParam param(ptrTrans->GetWorldMatrix(), 1.0f, false, PsMotionType::MotionTypeActive);
		//Rigidbodyをつける
		auto  ptrRigid = AddComponent<RigidbodySphere>(param);
		ptrRigid->SetAutoTransform(false);
		ptrRigid->SetAutoGravity(true);

		auto ptrCamera = dynamic_pointer_cast<MyCamera>(OnGetDrawCamera());
		auto stage = GetStage();
		auto Plyaer = stage->GetSharedGameObject<Player>(L"Player", false);
		if (ptrCamera || !Plyaer) {
			//MyCameraである
			//MyCameraに注目するオブジェクト（プレイヤー）の設定
			ptrCamera->SetTargetObject(Plyaer);
			ptrCamera->SetTargetToAt(Vec3(0, 0.5f, 0));
		}

	}
	void UnkoBoll::OnUpdate() {
		if (active == true) {
			//Move();
		}
	}
	void UnkoBoll::OnUpdate2() {

	}
	
	Vec3 UnkoBoll::holdon() {
		auto Time = App::GetApp()->GetElapsedTime();
		auto thistrans = GetComponent<Transform>();
		auto thiscol = GetComponent<CollisionSphere>();
		
		auto Plyaer = GetStage()->GetSharedGameObject<Player>(L"Player", false);
		auto ptrTrans = Plyaer->GetComponent<Transform>();
		auto PsUnko = this->GetComponent<RigidbodySphere>();

		auto ptrfor = ptrTrans->GetForword();
		auto ptrPos = ptrTrans->GetPosition();
		auto ptrScale = ptrTrans->GetScale();
		auto ptrrot = ptrTrans->GetRotation();

		auto thispos = thistrans->GetPosition().y;
		auto thisScale = thistrans->GetScale();
		auto thisrot = thistrans->GetRotation();
		
		Vec3 Rot;
		//var translation = this.rigidbody.velocity * Time.deltaTime; // 位置の変化量
		//var distance = translation.magnitude; // 移動した距離
		//var scaleXYZ = transform.lossyScale; // ワールド空間でのスケール推定値
		//var scale = Mathf.Max(scaleXYZ.x, scaleXYZ.y, scaleXYZ.z); // 各軸のうち最大のスケール
		//var angle = distance / (this.sphereCollider.radius * scale); // 球が回転するべき量
		//var axis = Vector3.Cross(Vector3.up, translation).normalized; // 球が回転するべき軸
		//var deltaRotation = Quaternion.AngleAxis(angle * Mathf.Rad2Deg, axis); // 現在の回転に加えるべき回転

		//// 現在の回転からさらにdeltaRotationだけ回転させる
		//this.rigidbody.MoveRotation(deltaRotation * this.rigidbody.rotation);
	/*	auto translation = PsUnko->GetAngularVelocity()*Time;
		auto distance = translation.length();
		auto scaleXYZ = thisScale;
		auto angle = distance / (thiscol->GetMakedRadius * scaleXYZ);
		auto axis = Vec3(0, 1, 0) * translation;
		auto DeltaRotation = XMQuaternionRotationAxis(axis, angle);*/


		Vec3 Pos;
		//Pos = Vec3(DeltaRotation.)
	//	PsUnko->SetAngularVelocity(DeltaRotation);
		
		Pos = Vec3(ptrfor.x + ptrPos.x, (ptrfor.y + ptrPos.y), ptrfor.z + ptrPos.z);
		float maxlenge = ptrTrans->GetPosition().y + 2;

		//thistrans->SetRotation()
		if (Pos.y >= maxlenge) {
			Pos.y = maxlenge;
		}
		return Pos;
	}

		void UnkoBoll::Move() {
		auto Pos = holdon();
		auto PsUnko = this->GetComponent<RigidbodySphere>();
		//PsUnko->SetAngularVelocity(Pos);
		PsUnko->SetPosition(Pos);
	}

	float UnkoBoll::ScaleUp() {
		float upscale;
		auto score = UIDraw::GetScore();
		upscale = score / 1000.0f;
		return upscale;
	}

	void UnkoBoll::OnCollisionEnter(shared_ptr<GameObject>& Other){
		auto UnCoin = Other->GetStage()->GetSharedObjectGroup(L"CoinGrope");
		auto thistrans = GetComponent<Transform>();
		if (Other->FindTag(L"UnCoin")){ 
			ScaleUp();
			auto scale = thistrans->GetScale();
			scale = scale + UnkoBoll::ScaleUp();
			thistrans->SetScale(scale);
		}
		if (Other->FindTag(L"Player")) {

		}

	}
	void UnkoBoll::OnCollisionExcute(shared_ptr<GameObject>& Other){
		 if (Other->FindTag(L"Slope")) {
			active = false;
		}
	}
	void UnkoBoll::OnCollisionExit(shared_ptr<GameObject>& Other) {
		active = true;
	}



}
//end basecross



