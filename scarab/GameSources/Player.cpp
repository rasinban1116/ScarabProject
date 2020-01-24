/*!
@file Player.cpp
@brief �v���C���[�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	class Player : public GameObject;
	//	�p�r: �v���C���[
	//--------------------------------------------------------------------------------------
	//�\�z
	Player::Player(const shared_ptr<Stage>& StagePtr,
		const Vec3 &Position
		) :
		GameObject(StagePtr),
		m_Scale(0.5f),
		active(true),
		isGrand(true),
		m_PlayVelo(0, 0, 0),
		m_Speed(10.0f),
		m_pos(Position)

	{}



	Vec2 Player::GetInputState() const {
		Vec2 ret;
		//�R���g���[���̎擾
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		ret.x = 0.0f;
		ret.y = 0.0f;
		WORD wButtons = 0;
		if (cntlVec[0].bConnected) {
			ret.x = cntlVec[0].fThumbLX;
			ret.y = cntlVec[0].fThumbLY;
		}
		//�L�[�{�[�h�̎擾(�L�[�{�[�h�D��)
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
		if (KeyState.m_bPushKeyTbl['W']) {
			//�O
			ret.y = 1.0f;
		}
		else if (KeyState.m_bPushKeyTbl['A']) {
			//��
			ret.x = -1.0f;
		}
		else if (KeyState.m_bPushKeyTbl['S']) {
			//���
			ret.y = -1.0f;
		}
		else if (KeyState.m_bPushKeyTbl['D']) {
			//�E
			ret.x = 1.0f;
		}
		return ret;
	}

	void Player::RotToHead(const Vec3& Velocity, float LerpFact) {
		if (LerpFact <= 0.0f) {
			//��ԌW����0�ȉ��Ȃ牽�����Ȃ�
			return;
		}
		auto ptrTransform = GetComponent<Transform>();
		//��]�̍X�V
		if (Velocity.length() > 0.0f) {
			Vec3 temp = Velocity;
			temp.normalize();
			float toAngle = atan2(temp.x, temp.z);
			Quat qt;
			qt.rotationRollPitchYawFromVector(Vec3(0, toAngle, 0));
			qt.normalize();
			//���݂̉�]���擾
			Quat nowQt = ptrTransform->GetQuaternion();
			//���݂ƖڕW����
			if (LerpFact >= 1.0f) {
				nowQt = qt;
			}
			else {
				//�N�I�[�^�j�I���̕�ԏ���
				nowQt = XMQuaternionSlerp(nowQt, qt, LerpFact);
			}
			ptrTransform->SetQuaternion(nowQt);
		}
	}
	
	Vec3 Player::GetMoveVector()const {
		Vec3 angle(0, 0, 0);
		float RadXZ = 0.0f;
		//�R���g���[���̎擾
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		float fThumbLY = 0.0f;
		float fThumbLX = 0.0f;
		WORD wButtons = 0;
		if (cntlVec[0].bConnected) {
			fThumbLY = cntlVec[0].fThumbLY;
			fThumbLX = cntlVec[0].fThumbLX;
			wButtons = cntlVec[0].wButtons;
		}
		//�L�[�{�[�h�̎擾(�L�[�{�[�h�D��)
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
		if (KeyState.m_bPushKeyTbl['W']) {
			//�O
			fThumbLY = 1.0f;
		}
		else if (KeyState.m_bPushKeyTbl['A']) {
			//��
			fThumbLX = -1.0f;
			RadXZ += fThumbLX * App::GetApp()->GetElapsedTime() * m_Speed;
		}
		else if (KeyState.m_bPushKeyTbl['S']) {
			//���
			fThumbLY = -1.0f;
		}
		else if (KeyState.m_bPushKeyTbl['D']) {
			//�E
			fThumbLX = 1.0f;
			RadXZ += -fThumbLX * App::GetApp()->GetElapsedTime() * m_Speed;
		}
		
		if (fThumbLX != 0 || fThumbLY != 0) {
			float moveLength = 0;	//���������̃X�s�[�h
			auto ptrTransform = GetComponent<Transform>();
			auto ptrCamera = OnGetDrawCamera();
			//�i�s�����̌������v�Z
			auto front = ptrTransform->GetPosition() - ptrCamera->GetEye();
			front.y = 0;
			front.normalize();
			//�i�s������������̊p�x���Z�o
			float frontAngle = atan2(front.z, front.x);
			//�R���g���[���̌����v�Z
			float moveX = fThumbLX;
			float moveZ = fThumbLY;
			Vec2 moveVec(moveX, moveZ);
			float moveSize = moveVec.length();
			//�R���g���[���̌�������p�x���v�Z
			float cntlAngle = atan2(-moveX, moveZ);
			//�g�[�^���̊p�x���Z�o
			float totalAngle = frontAngle + cntlAngle;
			//�p�x����x�N�g�����쐬
			angle = Vec3(cos(totalAngle), 0, sin(totalAngle));
			//���K������
			angle.normalize();
			//�ړ��T�C�Y��ݒ�B
			angle *= moveSize;
			//Y���͕ω������Ȃ�
			angle.y = 0;
		}

		return angle;
	}



	//�v���C���[�̓���
	void Player::Move() {
		//�R���g���[���`�F�b�N���ē��͂�����΃R�}���h�Ăяo��
		auto vec = GetMoveVector();
		auto ptrPs = GetComponent<RigidbodySphere>();
		//m_PlayVelo = ptrPs->GetLinearVelocity();
		auto forces = GetComponent<Transform>();
		auto force = GetComponent<Rigidbody>();
		//x��z�̑��x���C��
		m_PlayVelo.x = vec.x * m_Speed;
		m_PlayVelo.z = vec.z * m_Speed;
		if (isGrand == false) {
			m_PlayVelo.y += -150.0f*App::GetApp()->GetElapsedTime();
		}
		//���x��ݒ�
		auto forwrd = forces->GetForword();
		ptrPs->SetLinearVelocity(m_PlayVelo);
			m_PlayVelo = Vec3(0, 0, 0);

			auto drawcomp = GetComponent<PNTBoneModelDraw>();
			auto time = App::GetApp()->GetElapsedTime();
			drawcomp->UpdateAnimation(time);
	}

	void Player::ChangeTrans() {
		//RigidbodySphere����Transform�ւ̃p�����[�^�̐ݒ�
		//�����I�ɐݒ�͂���Ȃ��ݒ�ɂȂ��Ă���̂Ŏ����ōs��
		auto ptrPs = GetComponent<RigidbodySphere>();
		auto ptrTrans = GetComponent<Transform>();
		//�ʒu���͂��̂܂ܐݒ�
		ptrTrans->SetPosition(ptrPs->GetPosition());
		//��]�̌v�Z
		Vec3 angle = GetMoveVector();
		if (angle.length() > 0.0f) {
			//��ԏ������s����]�B
			RotToHead(angle, 0.1f);
		}
	}

	//������
	void Player::OnCreate() {
		//�����ʒu�Ȃǂ̐ݒ�
		auto ptrTrans = GetComponent<Transform>();
		//�����ʒu�Ȃǂ̐ݒ�
		auto ptr = AddComponent<Transform>();
		ptr->SetScale(0.7f, 0.7f, 0.7f);	//���a25�Z���`�̋���
		ptr->SetRotation(-45.0f, 0.0f, 0.0f);
		ptr->SetPosition(m_pos);

		//CollisionSphere�Փ˔����t����
		auto ptrColl = AddComponent<CollisionSphere>();
		ptrColl->SetDrawActive(true);
		//�e�p�t�H�[�}���X�𓾂�
		GetStage()->SetCollisionPerformanceActive(true);
		GetStage()->SetUpdatePerformanceActive(true);
		GetStage()->SetDrawPerformanceActive(true);
		//�d�͂�����
		auto ptrGra = AddComponent<Gravity>();
		//WorldMatrix�����Ƃ�RigidbodySphere�̃p�����[�^���쐬
		PsSphereParam param(ptrTrans->GetWorldMatrix(), 1.0f, false, PsMotionType::MotionTypeActive);
		//RigidbodySphere�R���|�[�l���g��ǉ�
		auto psPtr = AddComponent<RigidbodySphere>(param);
		//�����I��Transform��ݒ肷��t���O�͖���
		psPtr->SetAutoTransform(false);
		//�����������
		auto ptrString = AddComponent<StringSprite>();
		ptrString->SetText(L"");
		ptrString->SetTextRect(Rect2D<float>(16.0f, 16.0f, 640.0f, 480.0f));
		//�e������i�V���h�E�}�b�v��`�悷��j
		auto ptrShadow = AddComponent<Shadowmap>();
		//�e�̌`�i���b�V���j��ݒ�
		ptrShadow->SetMeshResource(L"DEFAULT_SPHERE");
		//�`��R���|�[�l���g�̐ݒ�
		SetAlphaActive(true);
		AddTag(L"Player");
		//��������
		SetAlphaActive(true);
		auto drawcomp = AddComponent<PNTBoneModelDraw>();
		Mat4x4 spanMat;
		spanMat.affineTransformation(
			Vec3(0.5f),
			Vec3(0,0,0),
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
			//MyCamera�ł���
			//MyCamera�ɒ��ڂ���I�u�W�F�N�g�i�v���C���[�j�̐ݒ�
			ptrMyCamera->SetTargetObject(GetThis<GameObject>());
			ptrMyCamera->SetTargetToAt(Vec3(0, 0.25f, 0));
		}
	}


	//�X�V
	void Player::OnUpdate() {
		m_InputHandler.PushHandle(GetThis<Player>());
		auto ptrGameStage = dynamic_pointer_cast<GameStage>(GetStage());
		if (this->GetStage() == ptrGameStage) {
			if (ptrGameStage->GetCameraSelect() == CameraSelect::openingCamera) {
				return;
			}
		}
			Move();
	}

	//��X�V
	void Player::OnUpdate2() {
		ChangeTrans();
		//������̕\��
		//DrawStrings();
	}

	void Player::OnPushA()
	{
	}

	void Player::OnPushB()
	{
	}

	//�R���W�����������ɓ����������̏���
	void Player::OnCollisionEnter(shared_ptr<GameObject>& Other) {	
		if (Other->FindTag(L"Enemy")) {
			auto ptrScene = App::GetApp()->GetScene<Scene>();
			PostEvent(0.0f, GetThis<ObjectInterface>(), ptrScene, L"ToGameOverStage");
		}
		isGrand = true;
	}

	//�R���W�������������痣�ꂽ���̏���
	void Player::OnCollisionExit(shared_ptr<GameObject>& Other) {
		isGrand = false;
	}

	//�R���W�����������ɓ������Ă��鎞�̏���
	void Player::OnCollisionExcute(shared_ptr<GameObject>&Other) {
		isGrand = true;
	}
	

	//������̕\��
	void Player::DrawStrings() {

		//������\��
		wstring strMess(L"B�{�^���ōēǂݍ���\n");
		//�I�u�W�F�N�g��
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
		//�����������
		auto ptrString = GetComponent<StringSprite>();
		ptrString->SetText(str);
	}

//--------------------------------------------------------------------------------------
//	����
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

	
		//OBB�Փ�j�����t����
		auto ptrColl = AddComponent<CollisionSphere>();
		ptrColl->SetDrawActive(true);

		//ptrColl->SetFixed(true);
		//�e�p�t�H�[�}���X�𓾂�
		GetStage()->SetCollisionPerformanceActive(true);
		GetStage()->SetUpdatePerformanceActive(true);
		GetStage()->SetDrawPerformanceActive(true);

		//�e������
		auto ShadowPtr = AddComponent<Shadowmap>();
		ShadowPtr->SetMeshResource(L"DEFAULT_SPHERE");

		auto PtrDraw = AddComponent<BcPNTStaticDraw>();
		PtrDraw->SetMeshResource(L"DEFAULT_SPHERE");
		PtrDraw->SetDrawActive(true);
		PtrDraw->SetTextureResource(L"POOP_TX");

		//WorldMatrix�����Ƃ�RigidbodySphere�̃p�����[�^���쐬
		PsSphereParam param(ptrTrans->GetWorldMatrix(), 1.0f, false, PsMotionType::MotionTypeActive);
		//Rigidbody������
		auto  ptrRigid = AddComponent<RigidbodySphere>(param);
		//ptrRigid->SetAutoTransform(false);
		ptrRigid->SetAutoGravity(true);

		auto ptrCamera = dynamic_pointer_cast<MyCamera>(OnGetDrawCamera());
		auto stage = GetStage();
		auto Plyaer = stage->GetSharedGameObject<Player>(L"Player", false);
		if (ptrCamera || !Plyaer) {
			//MyCamera�ł���
			//MyCamera�ɒ��ڂ���I�u�W�F�N�g�i�v���C���[�j�̐ݒ�
			ptrCamera->SetTargetObject(Plyaer);
			ptrCamera->SetTargetToAt(Vec3(0, 0.5f, 0));
		}
		AddTag(L"UnkoBoll");

	}
	void UnkoBoll::OnUpdate() {
		holdon();
	}
	void UnkoBoll::OnUpdate2() {

	}
	
	void UnkoBoll::holdon() {
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
		auto translation = PsUnko->GetLinearVelocity()*Time;
		auto distance = translation.length();
		auto scaleXYZ = thisScale;
		auto Comparsion = DirectX::XMMax(scaleXYZ.x,scaleXYZ.y);
		auto Max = DirectX::XMMax(Comparsion,scaleXYZ.z);
		auto angle = distance / (thiscol->GetMakedRadius() * Max);
		auto axis = XMVector3Cross(Vec3(0, 1, 0), translation);
		axis = XMVector3Normalize(axis);
		auto DeltaRotation = XMQuaternionRotationAxis(axis, angle);
		Vec3 Pos = Vec3(DeltaRotation * PsUnko->GetLinearVelocity());
		PsUnko->SetLinearVelocity(Pos);

		Pos = Vec3(0);
		Pos = Vec3(ptrfor.x + ptrPos.x, (ptrfor.y + ptrPos.y), ptrfor.z + ptrPos.z);
		float maxlenge = ptrTrans->GetPosition().y + 2;
		PsUnko->MovePosition(Pos,0.01f);
		//PsUnko->SetPosition(Pos);
		if(Pos.x >= maxlenge||Pos.y >= maxlenge|| Pos.z >= maxlenge) {
			Pos.y = maxlenge;
		}
		Vec3 MaxScale = Vec3(3);
		if (thisScale.x > MaxScale.x || thisScale.y > MaxScale.y || thisScale.z > MaxScale.z) {
			thisScale = MaxScale;
		}
		
	}

	void UnkoBoll::Move() {

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
		}
		if (Other->FindTag(L"Player")) {

		}

	}
	void UnkoBoll::OnCollisionExcute(shared_ptr<GameObject>& Other){
	/*	 if (Other->FindTag(L"Slope")) {
			active = false;
		}*/
	}
	void UnkoBoll::OnCollisionExit(shared_ptr<GameObject>& Other) {
		active = true;
	}



}
//end basecross



